package il.co.ilrd.multiThreadedCountingSort;

import java.util.ArrayList;
import java.util.List;

public class MultiTimesCountingSort {
    private int[][] histograms;
    private char[][] sortedArrays;
    private int numOfThreads;

    private char[] arrToSort;
    private int numOfSorts;

    private final int asciiSize = 256;

    public MultiTimesCountingSort(int numOfThreads, int numOfSorts) {
        this.numOfThreads = numOfThreads;
        histograms = new int[numOfThreads][asciiSize];
        this.numOfSorts = numOfSorts;
    }

    public void Sort(char[] chars) throws InterruptedException {
        arrToSort = chars;
        List<Thread> threads = new ArrayList<>();
       for (int i = 0; i < numOfThreads; i++) {//producer
            threads.add(new Thread(new ThreadMultipleCountSort(numOfSorts/numOfThreads)));
        }
        for (Thread thread : threads) {
            thread.start();
        }
        for (Thread thread : threads) {
            thread.join();
        }
    }

    private class ThreadMultipleCountSort implements Runnable {

    private int numOfTimesToSort;


        public ThreadMultipleCountSort(int numOfTimesToSort) {
            this.numOfTimesToSort = numOfTimesToSort;
        }

        @Override
        public void run() {
            for(int i = 0; i < numOfTimesToSort; i++) {
                new SingleThreadCountingSort().countingSort(arrToSort);
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        long startTime, elapsedTime, singleThreadTime;
        int numOfTests = 10;
        String str = "ababababgyjughygfkuygftyuvtuyvftvtvftftu;oj9uaaaggggvyugfyababaugfyufrsdets  jkgyf hguiytoyugyugff";
        char[] smallArr = str.toCharArray();
        char[] unsortedDictionary = new DictionaryCharBuffer().getDictionaryChars();
        char[] sortedDictonary = new char[0];
        int[] numThreadsArr = {2,3,4,8,16,20,24};

        startTime = System.currentTimeMillis();
        for (int j = 0; j < numOfTests; j++) {
            sortedDictonary = new SingleThreadCountingSort().countingSort(unsortedDictionary);
        }
        System.out.println(sortedDictonary);
//        singleThreadTime = System.currentTimeMillis() - startTime;
//        System.out.println("single threaded counting sort: " + singleThreadTime / 1000 + " [sec]");
//        for (int i = 0; i < 7; i++) {
//            unsortedDictionary = new DictionaryCharBuffer().getDictionaryChars();
//            MultiTimesCountingSort multiTimesCountingSort = new MultiTimesCountingSort(numThreadsArr[i] , numOfTests);
//            startTime = System.currentTimeMillis();
//            multiTimesCountingSort.Sort(unsortedDictionary);
//            elapsedTime = System.currentTimeMillis() - startTime;
//            System.out.println(numThreadsArr[i]  + " Threads counting sort " + elapsedTime / 1000 + " [sec]");
//
//        }
    }
}
