package il.co.ilrd.threadPool;

import il.co.ilrd.multiThreadedCountingSort.DictionaryCharBuffer;
import il.co.ilrd.multiThreadedCountingSort.SingleThreadCountingSort;

import java.util.concurrent.Callable;

public class CreateCallRunAbles{
    public static Callable<DictionaryCharBuffer> getDictionarySortCallable() {
        return new Callable<DictionaryCharBuffer>() {
            public DictionaryCharBuffer linuxDictionary = new DictionaryCharBuffer();

            @Override
            public DictionaryCharBuffer call() throws Exception {
                SingleThreadCountingSort sort = new SingleThreadCountingSort();
                linuxDictionary.setDictionaryChars(sort.countingSort(linuxDictionary.getDictionaryChars()));
                return linuxDictionary;
            }
        };
    }
    public static Runnable getMaxInteger() {
        return new Runnable() {
            public long counter = 0;

            @Override
            public void run() {
                while (counter < 20000000000L) {
                    ++counter;
                }
            }
        };
    }

        public static Runnable getMaxIntegerPrint(){
            return new Runnable() {
                public long counter = 0;
                @Override
                public void run() {
                    while (counter < 2000000){
                        ++counter;
                    }
                    System.out.println("finish counting to " + counter);

                }
            };
    }

    public static Runnable runnableWait(int milis){
        return new Runnable() {

            @Override
            public void run() {
                try {
                    Thread.sleep(milis);
                } catch (InterruptedException e) {
                    System.err.println("interrupted");
                    throw new RuntimeException(e);
                }
                System.err.println("finish runnableSleep");

            }
        };
    }
}
