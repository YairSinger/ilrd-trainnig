package il.co.ilrd.concurrency;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.locks.ReentrantLock;

public class Ex2 {
    public long counter = 0;
    public ReentrantLock lock = new ReentrantLock();
    public AtomicLong atomicCounter = new AtomicLong(0);

    Ex2() {
    }

    public synchronized void increaseCounter() {
        counter += 1;
    }
    public void increaseCounterSyncBlock() {
        synchronized(this){
            counter += 1;
        }
    }
    public void increaseCounterReentrantLock() {
        lock.lock();
        try {
            counter += 1;
        } finally {
            lock.unlock();
        }

    }

    public long getCounter() {
        return counter;
    }
}

class CountCounters{
    private static String[] testsNames = {"Default","synchronized method", "synchronized block", "Atomic", "Reentrant lock"};
    static ReentrantLock lock;
    public static void main(String[] args) throws InterruptedException {
        defaultCounterIncreasment();
        syncMethodCounterIncreasment();
        syncBlockCounterIncreasment();
        atomicCounterIncreasment();
        ReentrantLockCounterIncreasment();

    }
    public static void defaultCounterIncreasment() throws InterruptedException {
        Ex2 ex2 = new Ex2();
        List<Thread> threads = new ArrayList<Thread>();

        for (int i = 0; i < 2; i++) {
            threads.add(new Thread(new Runnable() {

                @Override
                public void run() {
                    for (int i = 0; i < 10000000; i++) {
                        ex2.counter += 1;
                    }
                }
            }));
        }
         Long startTime = System.nanoTime();
        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            thread.join();
        }
        Long elapsedTime = System.nanoTime() - startTime;
        System.err.println(CountCounters.testsNames[0] +  " Counter result is: " + ex2.counter);
        System.err.println(CountCounters.testsNames[0] + "Total exec time: "
                + elapsedTime/1000000 + " [millis]");
    }

    public static void syncMethodCounterIncreasment() throws InterruptedException {
        Ex2 ex2 = new Ex2();
        List<Thread> threads = new ArrayList<Thread>();

        for (int i = 0; i < 2; i++) {
            threads.add(new Thread(new Runnable() {
                @Override
                public void run() {
                    for (int i = 0; i < 10000000; i++) {
                        ex2.increaseCounter();
                    }
                }
            }));
        }
        Long startTime = System.nanoTime();
        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            thread.join();
        }
        Long elapsedTime = System.nanoTime() - startTime;
        System.err.println(CountCounters.testsNames[1] +  " Counter result is: " + ex2.counter);
        System.err.println("Total exec time: "
                + elapsedTime/1000000 + " [millis]");
    }

    public static void syncBlockCounterIncreasment() throws InterruptedException {
        Ex2 ex2 = new Ex2();
        List<Thread> threads = new ArrayList<Thread>();

        for (int i = 0; i < 2; i++) {
            threads.add(new Thread(new Runnable() {
                @Override
                public void run() {
                    for (int i = 0; i < 10000000; i++) {
                        ex2.increaseCounterSyncBlock();
                    }
                }
            }));
        }
        Long startTime = System.nanoTime();
        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            thread.join();
        }
        Long elapsedTime = System.nanoTime() - startTime;
        System.err.println(CountCounters.testsNames[2] +  " Counter result is: " + ex2.counter);
        System.err.println("Total exec time: "
                + elapsedTime/1000000 + " [millis]");
    }

    public static void atomicCounterIncreasment() throws InterruptedException {
        Ex2 ex2 = new Ex2();
        List<Thread> threads = new ArrayList<Thread>();

        for (int i = 0; i < 2; i++) {
            threads.add(new Thread(new Runnable() {
                @Override
                public void run() {
                    for (int i = 0; i < 10000000; i++) {
                        ex2.atomicCounter.incrementAndGet();
                    }
                }
            }));
        }
        Long startTime = System.nanoTime();
        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            thread.join();
        }
        Long elapsedTime = System.nanoTime() - startTime;
        System.err.println(CountCounters.testsNames[3] +  " Counter result is: " + ex2.atomicCounter.get());
        System.err.println(CountCounters.testsNames[3] + " Total exec time: "
                + elapsedTime/1000000 + " [millis]");
    }

    public static void ReentrantLockCounterIncreasment() throws InterruptedException {
        Ex2 ex2 = new Ex2();
        List<Thread> threads = new ArrayList<Thread>();

        for (int i = 0; i < 2; i++) {
            threads.add(new Thread(new Runnable() {
                @Override
                public void run() {
                    for (int i = 0; i < 10000000; i++) {
                        ex2.increaseCounterReentrantLock();
                    }
                }
            }));
        }
        Long startTime = System.nanoTime();
        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            thread.join();
        }
        Long elapsedTime = System.nanoTime() - startTime;
        System.err.println(CountCounters.testsNames[4] +  " Counter result is: " + ex2.counter);
        System.err.println("Total exec time: "
                + elapsedTime/1000000 + " [millis]");
    }


}