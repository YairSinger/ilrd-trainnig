
import java.util.*;
import java.io.*;
import java.lang.Thread;
import java.lang.ref.WeakReference;



class ArrayEx4 {
    
    public static void main(String[] args) {
    	ArrayList<WeakReference<int[]>> myList = new ArrayList<WeakReference<int[]>>();
                try{Thread.sleep(10000);}catch(InterruptedException e){System.out.println(e);} 
        for (int i = 0; i < 10; ++i){
            int[] myIntArray = new int[100000];
            WeakReference<int[]> myArrRef = new WeakReference<int[]>(myIntArray);
            myList.add(myArrRef);
            System.out.println("Total memory (bytes): " + Runtime.getRuntime().totalMemory());
            System.out.println("Free memory (bytes): " + Runtime.getRuntime().freeMemory());
            try{Thread.sleep(1);}catch(InterruptedException e){System.out.println(e);} 
           
        }

        printCounter(0);
    }

    public static void printCounter(int counter) {
    	
        System.out.println("counter is : " + counter);

        if (counter < 200){
            printCounter(counter + 1);            
        }
        
    }
}


