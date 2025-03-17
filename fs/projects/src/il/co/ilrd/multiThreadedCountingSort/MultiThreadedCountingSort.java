package il.co.ilrd.multiThreadedCountingSort;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicIntegerArray;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class MultiThreadedCountingSort {

    private AtomicInteger[] charsHistogram = new AtomicInteger[256];
    private int numOfThreads = 1;
    private char[] chars;
    private ReentrantLock lock = new ReentrantLock();
    private Condition cond_var = lock.newCondition();
    private Semaphore readyThreadsHistograms = new Semaphore(0);
    private char[] sorted;
    private int[] leftBordersValues;

    private int[][] histograms;

    private final int MIN_ASCII_VALUE = 128;


    public char[] countingSort(char[] chars, int numOfThreads) throws InterruptedException {
        this.chars = chars;
        this.numOfThreads = numOfThreads;


        List<Thread> threads = new ArrayList<>();
        histograms = new int[numOfThreads][256];

        for (int i = 0; i < numOfThreads; i++) {//producer

            threads.add(new Thread(new ThreadCountSort(i * (chars.length / numOfThreads), (i + 1) * (chars.length / numOfThreads), i)));
        }
        for (Thread thread : threads) {
            thread.start();
        }

        for (int k = 0; k < numOfThreads; k++) {
            try {
                readyThreadsHistograms.acquire();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }


        for (int i = 1; i < charsHistogram.length; i++) {
            charsHistogram[i].addAndGet(charsHistogram[i - 1].get());//histogram
        }

        leftBordersValues = new int[numOfThreads];
        leftBordersValues[0] = 0;

        sorted = new char[chars.length];
        lock.lock();
        cond_var.signalAll();
        lock.unlock();

        for (Thread thread : threads) {
            thread.join();
        }

        return sorted;
    }

    private class ThreadCountSort implements Runnable {

        private int firstInx;
        private int lastInx;
        private int threadInx;

        private int[] histogram = new int[256];


        public ThreadCountSort(int firstInx, int lastInx, int threadInx) {
            this.firstInx = firstInx;
            this.lastInx = lastInx;
            this.threadInx = threadInx;
        }

        @Override
        public void run() {
            if (lastInx > chars.length) {
                lastInx = chars.length;
            }
            for (int i = firstInx; i < lastInx; i++) {
                ++histogram[chars[i]];

            }
            for (int i = 0; i < histogram.length; i++) {
                charsHistogram[i].addAndGet(histogram[i]);
            }

            lock.lock();
            readyThreadsHistograms.release();
            try {
                cond_var.await();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            lock.unlock();


            firstInx = threadInx * (histogram.length / numOfThreads);
            lastInx = (threadInx + 1) * (histogram.length / numOfThreads);

            for (int i = lastInx - 1; i > firstInx; i--) {
                int stop = charsHistogram[i - 1].get();
                for (int j = charsHistogram[i].get(); j < stop; j--, --i) {
                    sorted[j - 1] = (char) i;
                }
            }
            int stop;
            if (firstInx == 0) {
                stop = 0;
            } else {
                stop = charsHistogram[firstInx - 1].get();
            }
            for (int j = charsHistogram[firstInx].get(); j < stop; j--) {
                sorted[j - 1] = (char) firstInx;
            }


        }
    }

    public static void main(String[] args) throws InterruptedException {
        long startTime, elapsedTime, singleThreadTime;
        int numOfTests = 100;
        String str = "ababababgyjughygfkuygftyuvtuyvftvtvftftu;oj9uaaaggggvyugfyababaugfyufrsdets  jkgyf hguiytoyugyugff";
        char[] smallArr = str.toCharArray();
        char[] unsortedDictionary = new DictionaryCharBuffer().getDictionaryChars();
        char[] sortedDictonary = new char[0];

        startTime = System.currentTimeMillis();
        for (int j = 0; j < numOfTests; j++) {
            sortedDictonary = new SingleThreadCountingSort().countingSort(unsortedDictionary);
        }
        singleThreadTime = System.currentTimeMillis() - startTime;
        System.out.println("single threaded counting sort: " + singleThreadTime / 1000 + " [sec]");

        for (int i = 1; i < 32; i <<= 1) {
            unsortedDictionary = new DictionaryCharBuffer().getDictionaryChars();
            startTime = System.currentTimeMillis();
            sortedDictonary = new char[0];
            for (int j = 0; j < numOfTests; j++) {
                sortedDictonary = new MultiThreadedCountingSort().countingSort(smallArr, i);
            }
            elapsedTime = System.currentTimeMillis() - startTime;
            System.out.println(i + " Threads counting sort " + (singleThreadTime - elapsedTime) / singleThreadTime + " [%] improvment");

            //assertEquals(unsortedDictionary.length, sortedDictonary.length);
            // System.out.println(sortedDictonary);
            //Arrays.sort(unsortedDictionary);
            //assertTrue(isEquals(unsortedDictionary, sortedDictonary));
            //}
        }
    }
}

