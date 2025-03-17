package il.co.ilrd.multiThreadedCountingSort;

public class SingleThreadCountingSort {
    private int[] histogram = new int[256];

    public char[] countingSort(char[] chars) {

        for (int i = 0; i < chars.length; i++) {
            histogram[chars[i]]++;
        }

        for (int i = 1; i < histogram.length; i++) {
            histogram[i] += histogram[i - 1];
        }

        char[] sorted = new char[chars.length];

//        for (int i = 0; i < chars.length; i++) {
//            sorted[histogram[chars[i]] - 1] = chars[i];
//            histogram[chars[i]]--;
//        }

        for (int i = histogram.length - 1; i > 0; i--) {
            int stop = histogram[i - 1];
            for (int j = histogram[i]; j > stop ; j--) {
                sorted[histogram[i] - 1] = ((char)i);
            }
        }

        while (histogram[0] > 0){
            sorted[histogram[0] - 1] = (char)0;
            --histogram[0];
        }
        return sorted;
    }

}
