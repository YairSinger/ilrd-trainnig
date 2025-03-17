package il.co.ilrd.generic;

import java.util.ArrayList;
import java.util.List;

public class GenericIlrd<T> {

    public static <E> void printArray(E[] inputArray) {
        // display array elements
        for (E element : inputArray)
            System.out.printf("%s ", element);

        System.out.println();
    }



    public static void main(String[] args) {

        String arr[] = new String[3];
        arr[0] = "first";
        arr[1] = "second";
        arr[2] = "third";

        Integer intArr[] = {1,2,3};

        Character charecterArr[] = {'A', 'B' ,' '};
        System.out.println("Printing String array");
        printArray(arr);
        System.out.println("Printing Integer array");
        printArray(intArr);
        System.out.println("Printing Charecter array");
        printArray(charecterArr);

    }
}
