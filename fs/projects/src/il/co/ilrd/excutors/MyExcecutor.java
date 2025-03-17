package il.co.ilrd.excutors;

import java.util.concurrent.*;

public class MyExcecutor {
    public static void main(String[] args) {
        BlockingQueue<Runnable> queue = new ArrayBlockingQueue<>(20);
        ExecutorService executor = new ThreadPoolExecutor(Runtime.getRuntime().availableProcessors(), 20, Long.MAX_VALUE, TimeUnit.NANOSECONDS,queue);
        Callable<Integer> task = new Callable<Integer>() {
            @Override
            public Integer call() throws Exception {

                long sTime = System.currentTimeMillis();
                for (int i = 0; i < 10000000; i++) {

                }
                return new Integer(String.valueOf(System.currentTimeMillis() - sTime));
            }
        };
        Future<Integer> res = executor.submit(task);

        System.out.println(res.cancel(true));
        executor.shutdown();


    }

    public static void singleThread(){
        ExecutorService executorService = Executors.newFixedThreadPool(1);
        for (int i = 0; i < 15; i++) {
            executorService.submit(()-> System.err.println(Thread.activeCount() + " running threads"));
        }
    }

}
