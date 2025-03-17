package il.co.ilrd.threadPool;

import il.co.ilrd.multiThreadedCountingSort.DictionaryCharBuffer;
import il.co.ilrd.multiThreadedCountingSort.MultiTimesCountingSort;
import il.co.ilrd.multiThreadedCountingSort.SingleThreadCountingSort;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.TestMethodOrder;

import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.*;

import static org.junit.Assert.*;


@TestMethodOrder(MethodOrderer.MethodName.class)
public class ThreadPoolTest {

    public static ThreadPool threadPool;
    public static int staticThreadPoolNumOfThreads = 0;

    @BeforeClass
    public static void createPool() {
        staticThreadPoolNumOfThreads = 8;
        threadPool = new ThreadPool(staticThreadPoolNumOfThreads);
    }

    @Test
    @DisplayName("basic")
    public void a_singleThreadAllSubmitsMethods() throws InterruptedException, ExecutionException {

        ThreadPool singleThreadPool = new ThreadPool(1);
        long startTime, elapsedTime;
        startTime = System.currentTimeMillis();
        Future<DictionaryCharBuffer> dictFuture = singleThreadPool.submit(CreateCallRunAbles.getDictionarySortCallable());
        Future<DictionaryCharBuffer> dictFuture2 = singleThreadPool.submit(CreateCallRunAbles.getDictionarySortCallable(), Priority.LOW);
        Future<Void> counter = singleThreadPool.submit(CreateCallRunAbles.getMaxInteger(), Priority.LOW);
        Future<Integer> counter2 = singleThreadPool.submit(CreateCallRunAbles.getMaxInteger(), Priority.LOW, new Integer(5));
        singleThreadPool.execute(CreateCallRunAbles.getMaxIntegerPrint());

        DictionaryCharBuffer result = dictFuture.get();
        elapsedTime = System.currentTimeMillis() - startTime;
        System.out.println("time to execute first " + elapsedTime);

        DictionaryCharBuffer result2 = dictFuture2.get();
        elapsedTime = System.currentTimeMillis() - startTime;
        System.out.println("time to execute sec " + elapsedTime);


        Void countRes = counter.get();
        elapsedTime = System.currentTimeMillis() - startTime;
        System.out.println("time to execute third " + elapsedTime);

        Integer count2Res = counter2.get();
        elapsedTime = System.currentTimeMillis() - startTime;
        System.out.println("time to execute forth " + elapsedTime);

    }

    @Test
    public void aa_defaultCtor() throws InterruptedException, ExecutionException {
        int baseNumOfThreads = Thread.activeCount();
        ThreadPool defaultPool = new ThreadPool();
        Thread.sleep(1000);
        int numOfCreatedThreads = Thread.activeCount() - baseNumOfThreads;
        Future<String> result;
        String threadsName;
        int numOfThreads;
        Set<String> threadsIds1 = new HashSet<>();

        for (int i = 0; i < 100_000; i++) {
            threadsName = (defaultPool.submit(() -> Thread.currentThread().getName(), Priority.MID)).get();
            threadsIds1.add(threadsName);
        }
        assertEquals(Runtime.getRuntime().availableProcessors(), numOfCreatedThreads);
    }

    @Test
    public void b_testPriority() throws InterruptedException, ExecutionException {
        long startTime, elapsedTime;
        startTime = System.currentTimeMillis();
        Future<Integer> counter = threadPool.submit(CreateCallRunAbles.getMaxInteger(), Priority.LOW, new Integer(1));
        Future<Integer> counter2 = threadPool.submit(CreateCallRunAbles.getMaxInteger(), Priority.LOW, new Integer(5));
        Future<Integer> counter3 = threadPool.submit(CreateCallRunAbles.getMaxInteger(), Priority.MID, new Integer(5));
        Future<Integer> counter4 = threadPool.submit(CreateCallRunAbles.getMaxInteger(), Priority.HIGH, new Integer(5));

        Integer count2Res = counter4.get();
        elapsedTime = System.currentTimeMillis() - startTime;
        System.out.println("highest priority time " + elapsedTime);

        Integer count2Res2 = counter3.get();
        elapsedTime = System.currentTimeMillis() - startTime;
        System.out.println("mid priority time " + elapsedTime);

        count2Res2 = counter2.get();
        elapsedTime = System.currentTimeMillis() - startTime;
        System.out.println("low priority time " + elapsedTime);


    }

    @Test
    public void c_FutureBasicTest() throws InterruptedException, ExecutionException, TimeoutException {
        //get(), get(timeout), isDone(), isCanceled()
        long startTime, timeToExcute, timeOut;
        startTime = System.currentTimeMillis();
        Future<Integer> counter = threadPool.submit(CreateCallRunAbles.getMaxInteger(), Priority.LOW, new Integer(1));

        assertFalse(counter.isDone());
        assertFalse(counter.isCancelled());
        Integer count2Res = counter.get();
        timeToExcute = System.currentTimeMillis() - startTime;
        assertTrue(counter.isDone());
        assertFalse(counter.isCancelled());

        timeOut = 20;
        startTime = System.currentTimeMillis();
        counter = threadPool.submit(CreateCallRunAbles.getMaxInteger(), Priority.LOW, new Integer(1));
        Future<Integer> finalCounter = counter;
        // Exception exception = assertThrows(TimeoutException.class,()-> finalCounter.get(, TimeUnit.MILLISECONDS)) ;
        count2Res = counter.get(timeOut, TimeUnit.MILLISECONDS);
        assertTrue(System.currentTimeMillis() - startTime < timeToExcute);
        assertFalse(counter.isDone());
        count2Res = counter.get();
        assertEquals(1, count2Res.intValue());

    }

    @Test
    public void d_testCancel() throws InterruptedException, ExecutionException, TimeoutException {

        Void res;
        int numOfTasks = 100;
        Future<Void> [] futures = new Future[numOfTasks];
        Semaphore sem = new Semaphore(0);
        int canceledCounter = 0;
        for (int i = 0; i < numOfTasks; i++) {

            futures[i] = threadPool.submit(()->{
                try {
                    Thread.sleep(300);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                sem.release();
                return null;
            }, Priority.MID);
        }
        for (int i = numOfTasks - 1; i >= 0; i--) {
           if(futures[i].cancel(false)){
               ++canceledCounter;
           }
        };
        for (int i = 0; i < numOfTasks; i++) {
            futures[i].get();
        }
        int numOfRemovedTaskFromQueue = sem.availablePermits();
        assertEquals(canceledCounter,  numOfTasks - numOfRemovedTaskFromQueue);
        sem.acquire(numOfTasks - canceledCounter);
        int canceledWithInterrupt = 0;
        for (int i = 0; i < numOfTasks; i++) {

            futures[i] = threadPool.submit(()->{
                try {
                    Thread.sleep(300);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                sem.release();
                return null;
            }, Priority.MID);
        }
        for (int i = numOfTasks - 1; i >= 0; i--) {
            if(futures[i].cancel(true)){
                ++canceledWithInterrupt;
            }
        };
        int numOfInterrupted = 0;
        for (int i = 0; i < numOfTasks; i++) {
            try {
                futures[i].get();
            } catch (RuntimeException e) {
                ++numOfInterrupted;
            }
        }

        System.out.println("num of interrupted: " + numOfInterrupted);
        assertTrue(canceledWithInterrupt > canceledCounter);
        System.out.println("canceled tasks: " +canceledWithInterrupt + " with interrupt, " + canceledCounter + " without interrupt");


    }


    public int numOfThreads() throws InterruptedException, ExecutionException {
        Future<String> result;
        String threadsName;
        int numOfThreads;
        Set<String> threadsIds = new HashSet<>();

        for (int i = 0; i < 100_000; i++) {
            threadsName = (threadPool.submit(() -> Thread.currentThread().getName(), Priority.MID)).get();
            threadsIds.add(threadsName);
        }
        numOfThreads = threadsIds.size();
        threadsIds.clear();
        return numOfThreads;
    }

    @Test
    public void e_numOfThreadsIncrease() throws InterruptedException, ExecutionException {

        Future<String> result;
        String threadsName;
        int numOfThreads;
        Set<String> threadsIds1 = new HashSet<>();
        Set<String> threadsIds2 = new HashSet<>();
        Set<String> threadsIds3 = new HashSet<>();

        for (int i = 0; i < 100_000; i++) {
            threadsName = (threadPool.submit(() -> Thread.currentThread().getName(), Priority.MID)).get();
            threadsIds1.add(threadsName);
        }
        System.out.println("size before change : " + threadsIds1.size());

        threadPool.setNumOfThreads(16);
        for (int i = 0; i < 100_000; i++) {
            threadsName = (threadPool.submit(() -> Thread.currentThread().getName(), Priority.MID)).get();
            threadsIds2.add(threadsName);
        }
        System.out.println("size after increase : " + threadsIds2.size());


        threadPool.setNumOfThreads(4);
        for (int i = 0; i < 100_000; i++) {
            threadsName = (threadPool.submit(() -> Thread.currentThread().getName(), Priority.MID)).get();
            threadsIds3.add(threadsName);
        }
        System.out.println("size after decrease : " + threadsIds3.size());
    }

    @Test
    public void f_pauseResume() throws InterruptedException {
        Semaphore sem = new Semaphore(0);
        int numOfTasks = 500;
        for (int i = 0; i < numOfTasks; i++) {
            int finalI = i;
            threadPool.submit(() -> {
                long counter = 0;
                for (long j = 0; j < 200000000; j++) {
                    ++counter;
                }
                sem.release();
                return null;
            }, Priority.MID);
        }

        threadPool.pause();
        Thread.sleep(3000);
        //assertEquals(sem.availablePermits(), numOfTasks);

        assertTrue(sem.availablePermits() < numOfTasks);

        System.out.println("thread pool paused");
        System.out.println(" before pause finished :" + sem.availablePermits() + " tasks out of : " + numOfTasks);
        threadPool.resume();
        Thread.sleep(7000);
        assertEquals(numOfTasks, sem.availablePermits());
        System.out.println(" after pause finished :" + sem.availablePermits() + " tasks out of : " + numOfTasks);
        sem.acquire(numOfTasks);

        for (int i = 0; i < numOfTasks; i++) {
            int finalI = i;
            threadPool.submit(() -> {
                long counter = 0;
                for (long j = 0; j < 200000000; j++) {
                    ++counter;
                }
                sem.release();
                return null;
            }, Priority.HIGH);
        }
        threadPool.pause();
        Thread.sleep(3000);
        int additionTasks = 200;
        for (int i = 0; i < additionTasks; i++) {
            int finalI = i;
            threadPool.submit(() -> {
                long counter = 0;
                for (long j = 0; j < 200000000; j++) {
                    ++counter;
                }
                sem.release();
                return null;
            }, Priority.HIGH);
        }

        threadPool.resume();
        Thread.sleep(15000);
        assertEquals(numOfTasks + additionTasks, sem.availablePermits());
        System.out.println("passed adding tasks while paused");

    }

    @Test
    public void g_shutDownBasic() throws InterruptedException {
        ThreadPool threadPool1 = new ThreadPool(staticThreadPoolNumOfThreads);
        int baseNumOfThreads = Thread.activeCount()  - staticThreadPoolNumOfThreads;
        threadPool1.shutdown();
        Thread.sleep(100);
        assertEquals(0, Thread.activeCount() - baseNumOfThreads);

        boolean throwedException = false;


        try {
            threadPool1.submit(CreateCallRunAbles.getMaxInteger(), Priority.LOW, new Integer(5));
        } catch (UnsupportedOperationException e) {
            throwedException = true;
        }
        assertTrue(throwedException);
        System.out.println("submit after shutdown throws UnsupportedOperationException");
        threadPool1 = new ThreadPool();

        Semaphore sem = new Semaphore(0);
        int numOfTasks = 500;
        for (int i = 0; i < numOfTasks; i++) {
            int finalI = i;
            threadPool1.submit(() -> {
                long counter = 0;
                for (long j = 0; j < 200000000; j++) {
                    ++counter;
                }
                sem.release();
                return null;
            }, Priority.MID);
        }
        threadPool1.shutdown();
        Thread.sleep(8000);
        assertEquals(numOfTasks, sem.availablePermits());
        System.out.println("all tasks completed after shutdown");
        threadPool1 = new ThreadPool();
        Thread.sleep(200);
        throwedException = false;
        threadPool1.shutdown();
        try {
            threadPool1.submit(CreateCallRunAbles.getMaxInteger(), Priority.LOW, new Integer(5));
        } catch (UnsupportedOperationException e) {
            throwedException = true;
        }
        assertTrue(throwedException);
        System.out.println("submit right after shutdown throws UnsupportedOperationException");


    }

    @Test
    public void h_shutDownAwaitTermination() throws InterruptedException {
       ThreadPool threadPool1 = new ThreadPool();

        Semaphore sem = new Semaphore(0);
        int numOfTasks = 500;
        for (int i = 0; i < numOfTasks; i++) {
            int finalI = i;
            threadPool1.submit(() -> {
                long counter = 0;
                for (long j = 0; j < 200000000; j++) {
                    ++counter;
                }
                sem.release();
                return null;
            }, Priority.MID);
        }
        threadPool1.shutdown();
       threadPool1.awaitTermination();
        assertEquals(numOfTasks, sem.availablePermits());
        System.out.println("all tasks completed after shutdown awaitTermination");
    }

    @Test
    public void countingSortsThreadPoolVsMultiThreadedSort() throws InterruptedException, ExecutionException {
        int numOfSorts = 10000;
        char[] dictionary= new DictionaryCharBuffer().getDictionaryChars();
        ThreadPool threadPool1 = new ThreadPool(8);
        long startTime, endTime;
        startTime = System.currentTimeMillis();
        Future<char[]> future = null;
        for (int i = 0; i < numOfSorts; i++) {
         future = threadPool1.submit(()-> new SingleThreadCountingSort().countingSort(dictionary),Priority.MID);
        }
//        threadPool1.shutdown();
//        threadPool1.awaitTermination();
        future.get();
        endTime = System.currentTimeMillis() - startTime;
        System.out.println("ThreadPoolTime: " + numOfSorts + " dictionaries at: " + endTime);

        MultiTimesCountingSort multiTimesCountingSort = new MultiTimesCountingSort(Runtime.getRuntime().availableProcessors(), numOfSorts);
        startTime = System.currentTimeMillis();
        multiTimesCountingSort.Sort(dictionary);
        endTime = System.currentTimeMillis() - startTime;
        System.out.println("multiThreadClassTime: " + numOfSorts + " dictionaries at: " + endTime);

    }


}
