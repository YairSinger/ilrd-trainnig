//Project: GenericFactory
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Yuval;
//Date: 21.02.2024
//Status: Approved

package il.co.ilrd.threadPool;

import il.co.ilrd.waitablePQ.WaitablePQCV;

import java.util.Objects;
import java.util.concurrent.*;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ThreadPool implements Executor {
    /* fields */
    private final WaitablePQCV<Task<?>> taskQueue = new WaitablePQCV<>();

    private AtomicInteger numThreads;
    private boolean isPaused = false;
    static final private int MAX_PRIORITY = 11;
    private  final Semaphore pauseSemaphore = new Semaphore(0);
    private final Semaphore shutdownSemaphore = new Semaphore(0);
    private boolean isInShutdown = false;


    /* constructor */
    public ThreadPool() {
        this(Runtime.getRuntime().availableProcessors() * 2); // additional for some delayes in cpu bound task
    }
    public ThreadPool(int numThreads) {
        if (numThreads < 1 ){
            throw new IllegalArgumentException("less than one thread");
        }
        initWorkers(numThreads);
        this.numThreads = new AtomicInteger(numThreads);
    }
    public Future<Void> submit(Runnable task, Priority p){
        Callable<Void> callable = Executors.callable(task, null);
        return submit(callable, p);
    }
    public <T> Future<T> submit(Runnable task, Priority p, T value){
        Callable<T> callable = Executors.callable(task, value);
        return submit(callable, p);
    }
    public <T> Future<T> submit(Callable<T> task)  {
        return submit(task, Priority.MID);
    }
    public <T> Future<T> submit(Callable<T> task, Priority p)  {
        if (isInShutdown) {
            throw new UnsupportedOperationException("cant submit in shutdown");
        }
        int priority = p.getValue();
        Task<T> newTask = new Task<>(priority, Objects.requireNonNull(task));
        try {
            taskQueue.enqueue(newTask);
        } catch (InterruptedException e) {
            throw new RuntimeException(e + "enqueue failed");
        }
        return newTask.getTaskFuture();
    }


    @Override
    public void execute(Runnable command) {
            submit(command, Priority.MID, null);
    }
    public void setNumOfThreads(int newNumOfThreads) {
        if (numThreads.get() < newNumOfThreads) {
            int delta = newNumOfThreads - numThreads.get();
            initWorkers((delta));
            numThreads.addAndGet(delta);
        } else {
            int numToRemove = numThreads.get() - newNumOfThreads;
            for (int i = 0; i < numToRemove; i++) {
                Task<Object> threadTerminator = new Task<>(MAX_PRIORITY, () -> {((Worker) Thread.currentThread()).isRunning = false;
                                                                            numThreads.decrementAndGet(); return null;});
                try {
                    taskQueue.enqueue(threadTerminator);
                } catch (InterruptedException e) {
                   throw new RuntimeException(e);
                }
            }

        }
    }
    public void pause() {
        if(isPaused == false) {
            isPaused = true;
            for (int i = 0; i < numThreads.get(); i++) {
                Task<Object> newTask = new Task<>(MAX_PRIORITY, () -> {
                    pauseSemaphore.acquire();
                    return null;
                });

                try {
                    taskQueue.enqueue(newTask);
                } catch (InterruptedException ignored) {

                }
            }
        }
    }
    public void resume() {
            pauseSemaphore.release(numThreads.get());
            isPaused = false;
    }
    public void shutdown() {
        if(isInShutdown){
            return;
        }
        isInShutdown = true;
        for (int i = 0; i < numThreads.get(); i++) {
            Task<Object> terminateTask = new Task<>(MAX_PRIORITY, () -> {
                ((Worker) Thread.currentThread()).isRunning = false;
                shutdownSemaphore.release();
                return null;
            });

            try {
                taskQueue.enqueue(terminateTask);
            } catch (InterruptedException ignored) {

            }
        }
    }
    public void awaitTermination() {
        awaitTermination(Long.MAX_VALUE, TimeUnit.DAYS);
    }   // Blocking
    public void awaitTermination(long timeout, TimeUnit unit) {
        try {
            for (int i = 0; i < numThreads.get(); i++) {
                shutdownSemaphore.tryAcquire(1, timeout, unit);
            }

        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    } // Blocking
    private void initWorkers(int numOfThreads) {
        for (int i = 0; i < numOfThreads; i++) {
            Thread worker = new Worker();
            worker.start();
        }
    }
    private class Worker extends Thread {
        private boolean isRunning = true;


        @Override
        public void run() {
            Task<?> task = null;
            while (isRunning) {
                try {
                    task = taskQueue.dequeue();

                } catch (InterruptedException ignored) {

                }
                try {
                    if (task != null){
                        task.run();
                    }
                } catch (Exception ignored) {

                }
            }

        }
    }
    private  static class Task<V> implements Runnable, Comparable<Task<V>> {

        private  final int priority;

        public TaskFuture<V> getTaskFuture() {
            return taskFuture;
        }

        private final Callable<V> callable;
        private final TaskFuture<V> taskFuture;
        private final Lock taskLock = new ReentrantLock();
        private final Condition cond_variable = taskLock.newCondition();
        private Thread runnerThread;

        public Task(int priority, Callable<V> callable) {
            this.priority = priority;
            this.callable = Objects.requireNonNull(callable);
            taskFuture = new TaskFuture<>();
        }

        @Override
        public int compareTo(Task<V> vTask) {
            return this.priority - vTask.priority;
        }

        @Override
        public void run() {

            if(!isTaskReadyToRun()){
                return;
            }
            try {
                taskFuture.result = callable.call();
                taskLock.lock();
            } catch (InterruptedException e) { // thrown when task is cancelled ///change to internal Exception
                throw new RuntimeException(e);
            } catch (Exception e) {
                taskFuture.exception = e;
            } finally {
                runnerThread = null;
                cond_variable.signalAll();
                taskFuture.state = State.DONE;
                taskLock.unlock();
            }
        }

        private boolean isTaskReadyToRun(){
            taskLock.lock();
            try {
                if (taskFuture.state == State.CANCELLED) {
                    return false;
                } else {
                    runnerThread = Thread.currentThread();
                    taskFuture.state = State.RUNNING;
                    return true;
                }
            } finally {
                taskLock.unlock();
            }
        }

        public class TaskFuture<V> implements Future<V> {
            private V result;
            private Exception exception;
            private volatile State state = State.READY;

            @Override
            public boolean cancel(boolean b) {
                if (state == State.DONE || state == State.CANCELLED) {
                    return false;
                }

                taskLock.lock();
                try {
                    if (state == State.READY) {
                        state = State.CANCELLED;
                        return true;
                    }
                    if ( b && state == State.RUNNING) {
                        runnerThread.interrupt();
                        state = State.CANCELLED;
                        return true;
                    }
                } finally {
                    taskLock.unlock();
                }
                return false;
            }

            @Override
            public boolean isCancelled() {
                return state == State.CANCELLED;
            }

            @Override
            public boolean isDone() {
                return state == State.DONE || state == State.CANCELLED;
            }

            @Override
            public V get() throws InterruptedException, ExecutionException {
                try {
                    return get(Long.MAX_VALUE, TimeUnit.DAYS);
                } catch (TimeoutException e) {
                    throw new RuntimeException(e);
                }
            }

            @Override
            public V get(long l, TimeUnit timeUnit) throws InterruptedException, ExecutionException, TimeoutException {
                taskLock.lock();
                try {
                    while (!isDone()) {
                        if (!cond_variable.await(l, timeUnit)) {
                            return null;
                        }
                    }
                    if (exception != null) {
                        throw new RuntimeException(exception);
                    }
                } finally {
                    taskLock.unlock();
                }
                return result;
            }
        }

    }
    private enum State{
        READY,
        RUNNING,
        CANCELLED,
        DONE
    }

}




