package il.co.ilrd.multiThreadedCountingSort;

import org.junit.Test;

import java.util.Arrays;

import static org.junit.Assert.*;

public class MultiThreadedCountingSortTest {

    public boolean isSorted(char[] arr) {

        for (int i = 1; i < arr.length; i++) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }

    public boolean isEquals(char[] str1, char[] str2) {
        int i = 0;
        for (int j = 0; j < str2.length; j++) {
            if (str1[i] != str2[i]) {
                return false;
            }
        }
        return true;
    }

    @Test
    public void MultiThreadedCountingSortTest() throws InterruptedException {

        long startTime, elapsedTime, singleThreadTime;
        int numOfTests = 1;

        char[] unsortedDictionary = new DictionaryCharBuffer().getDictionaryChars();
        startTime = System.currentTimeMillis();
        char[] sortedDictonary = new char[0];
        for (int j = 0; j < numOfTests; j++) {
            sortedDictonary = new SingleThreadCountingSort().countingSort(unsortedDictionary);
        }

        singleThreadTime = System.currentTimeMillis() - startTime;
        System.out.println("single threaded counting sort: " + singleThreadTime / 1000 + " [sec]");

        for (int i = 1; i < 2; i <<= 1) {
            unsortedDictionary = new DictionaryCharBuffer().getDictionaryChars();
            startTime = System.currentTimeMillis();
            sortedDictonary = new char[0];
            for (int j = 0; j < numOfTests; j++) {
                sortedDictonary = new MultiThreadedCountingSort().countingSort(unsortedDictionary, i);
            }
            elapsedTime = System.currentTimeMillis() - startTime;
            System.out.println(i + " Threads counting sort " + (singleThreadTime - elapsedTime) / singleThreadTime + " [%] improvment");

            assertEquals(unsortedDictionary.length, sortedDictonary.length);
            //System.out.println(sortedDictonary);
            Arrays.sort(unsortedDictionary);
            //assertTrue(isEquals(unsortedDictionary, sortedDictonary));

        }


    }
}
