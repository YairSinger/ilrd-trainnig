package il.co.ilrd.waitablePQ;//package il.co.ilrd.waitablePQ;

import org.junit.jupiter.api.Test;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class WaitablePQSemTest {
    @Test
    public void testEnqueueDequeue() throws InterruptedException {
        WaitablePQSem<Integer> waitablePQSem = new WaitablePQSem<>();
        waitablePQSem.enqueue(3);
        waitablePQSem.enqueue(1);
        waitablePQSem.enqueue(2);

        assertEquals(1, waitablePQSem.dequeue());
        assertEquals(2, waitablePQSem.dequeue());
        assertEquals(3, waitablePQSem.dequeue());
    }

    @Test
    public void testEnqueueDequeueConcurrently() throws InterruptedException {
        final int THREAD_COUNT = 10;
        final int OPERATIONS_PER_THREAD = 1000;
        WaitablePQSem<Integer> waitablePQSem = new WaitablePQSem<>();
        ExecutorService executor = Executors.newFixedThreadPool(THREAD_COUNT);
        CountDownLatch latch = new CountDownLatch(THREAD_COUNT);

        for (int i = 0; i < THREAD_COUNT; i++) {
            executor.execute(() -> {
                try {
                    for (int j = 0; j < OPERATIONS_PER_THREAD; j++) {
                        waitablePQSem.enqueue(j);
                        waitablePQSem.dequeue();
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } finally {
                    latch.countDown();
                }
            });
        }

        latch.await();
        executor.shutdown();
        executor.awaitTermination(1, TimeUnit.MINUTES);

        assertTrue(waitablePQSem.isEmpty());
    }
}

//public class WaitablePQTest {
//
//
//    @Test
//    public void singleThreadComparable() throws InterruptedException {
//        WaitablePQ<Integer> pq = new WaitablePQ<>();
//        pq.enqueue(new Integer(5));
//        pq.enqueue(new Integer(0));
//        Integer integer = new Integer(7);
//        pq.enqueue(integer);
//        assertEquals(0, pq.dequeue().intValue());
//        assertEquals(5, pq.dequeue().intValue());
//        assertTrue(pq.remove(integer));
//        assertFalse(pq.remove(integer));
//
//    }
//
//    @Test
//    public void singleThreadComparator() throws InterruptedException {
//        Lavrador lavrador = new Lavrador(12, 120, "Yair");
//        Lavrador lavrador2 = new Lavrador(14, 150, "Yair");
//        Lavrador lavrador3 = new Lavrador(20, 120, "Yair");
//        Lavrador lavrador4 = new Lavrador(4, 160, "Yair");
//
//        WaitablePQ<Dog> pq = new WaitablePQ<>(new Dog(1));
//        pq.enqueue(lavrador);
//        pq.enqueue(lavrador2);
//        pq.enqueue(lavrador3);
//        pq.enqueue(lavrador4);
//
//        assertEquals(4, pq.dequeue().getAge());
//        assertEquals(12, pq.dequeue().getAge());
//        assertTrue(pq.remove(lavrador2));
//        assertFalse(pq.remove(lavrador4));
//    }
//
//
//    @Test
//    public void multiThreadsEnqueue() throws InterruptedException {
//        List<Thread> threads = new ArrayList<Thread>();
//        int numOfThreads = 10;
//        int totalEnqueues = 2000000;
//        WaitablePQ<Integer> pq = new WaitablePQ<>();
//        for (int i = 0; i < numOfThreads; i++) {//consumers
//            int finalI = i;
//            threads.add(new Thread(new Runnable() {
//                @Override
//                public void run() {
//                    for (int j = finalI * totalEnqueues / numOfThreads; j < (finalI + 1) * (totalEnqueues / numOfThreads); j++) {
//                        try {
//                            pq.enqueue(new Integer(j));
//                        } catch (InterruptedException e) {
//                            throw new RuntimeException(e);
//                        }
//                    }
//
//                }
//            }));
//
//        }
//
//        for (Thread thread : threads) {
//            thread.start();
//        }
//
//        for (Thread thread : threads) {
//            thread.join();
//        }
//
//        assertEquals(totalEnqueues, pq.size());
//        for (int i = 0; i < totalEnqueues; i++) {
//            assertEquals(i, pq.dequeue().intValue());
//        }
//    }
//    @Test
//    public void multiThreadsEnqueueAndDequeue() throws InterruptedException {
//        List<Thread> threads = new ArrayList<Thread>();
//        int numOfThreads = 17;
//        int totalEnqueues = 100000;
//
//        WaitablePQ<Integer> pq = new WaitablePQ<>();
//        for (int i = 0; i < numOfThreads; i++) {//consumers
//            int finalI = i;
//            threads.add(new Thread(new Runnable() {
//                @Override
//                public void run() {
//                    for (int j = finalI * totalEnqueues / numOfThreads; j < (finalI + 1) * (totalEnqueues / numOfThreads); j++) {
//                        try {
//                            pq.enqueue(new Integer(j));
//                        } catch (InterruptedException e) {
//                            throw new RuntimeException(e);
//                        }
//                    }
//
//                }
//            }));
//
//        }
//        List<Thread> threadsDequeuers = new ArrayList<Thread>();
//        for (int i = 0; i < numOfThreads; i++) {//consumers
//            int finalI = i;
//
//            threadsDequeuers.add(new Thread(new Runnable() {
//                int counter = 0;
//                int threadInx = finalI;
//                int firstInx = finalI * totalEnqueues / numOfThreads;
//                int lastInx = (finalI + 1) * (totalEnqueues / numOfThreads);
//                @Override
//                public void run() {
//                    for (int j = firstInx ; j < lastInx; j++) {
//                        try {
//                            pq.dequeue();
//                        } catch (InterruptedException e) {
//                            throw new RuntimeException(e);
//                        }
//                    }
//
//                }
//
//            }));
//
//        }
//        for (Thread threadsRemover : threadsDequeuers) {
//            threadsRemover.start();
//        }
//        for (Thread thread : threads) {
//            thread.start();
//        }
//
//
//        for (int threadInx=0; threadInx < numOfThreads;++threadInx) {
//            threads.get(threadInx).join();
//            threadsDequeuers.get(threadInx).join();
//        }
//
//        assertTrue( pq.isEmpty());
//    }
//
//    public void multiEnqueueRemove() throws InterruptedException {
//        List<Thread> threads = new ArrayList<Thread>();
//        int numOfThreads = 7;
//
//        int totalEnqueues = 200;
//        Lock lock = new ReentrantLock();
//        AtomicInteger numOfRemoved = new AtomicInteger(0);
//
//        WaitablePQ<Integer> pq = new WaitablePQ<>();
//        for (int i = 0; i < numOfThreads; i++) {//consumers
//            int finalI = i;
//
//            threads.add(new Thread(new Runnable() {
//                int threadInx = finalI;
//                int firstInx = finalI * totalEnqueues / numOfThreads;
//                int lastInx = (finalI + 1) * (totalEnqueues / numOfThreads);
//
//                @Override
//                public void run() {
//                    if (threadInx == numOfThreads - 1){
//                        lastInx = totalEnqueues;
//                    }
//                    for (int j = firstInx; j < lastInx; j++) {
//                        try {
//                            pq.enqueue(new Integer(j));
//                        } catch (InterruptedException e) {
//                            throw new RuntimeException(e);
//                        }
//                    }
//
//                }
//            }));
//
//        }
//        List<Thread> threadsRemovers = new ArrayList<Thread>();
//        for (int i = 0; i < numOfThreads; i++) {//consumers
//            int finalI = i;
//
//            threadsRemovers.add(new Thread(new Runnable() {
//                int threadInx = finalI;
//                int firstInx = finalI * totalEnqueues / numOfThreads;
//                int lastInx = (finalI + 1) * (totalEnqueues / numOfThreads);
//                int counter = 0;
//
//                Integer temp = new Integer(0);
//                @Override
//                public void run() {
//                    if (threadInx == numOfThreads - 1){
//                        lastInx = totalEnqueues;
//                    }
//                    for (int j = firstInx; j < lastInx; j++) {
//                        temp = Integer.valueOf(j);
//
////                        try {
////                            Thread.sleep(200);
////                        } catch (InterruptedException e) {
////                            throw new RuntimeException(e);
////                        }
//
//                        try {
////                            lock.lock();
//                           if(pq.remove(temp)) {
//                             numOfRemoved.incrementAndGet();
//                           }
//                        } catch (InterruptedException e) {
//                            throw new RuntimeException(e);
//                        }finally {
////                            lock.unlock();
//                        }
//                    }
//                    lock.lock();
//                    int total = numOfRemoved.addAndGet(counter);
//                    //System.err.println("thread No: "+ threadInx + "removed: " + counter +" current total removed: " + total);
//                    lock.unlock();
//                }
//
//            }));
//
//        }
//        for (int i = 0; i < numOfThreads; i++) {
//            threadsRemovers.get(i).start();
//            threads.get(i).start();
//        }
//
//
//
//        for (Thread thread : threads) {
//            thread.join();
//        }
//
////        for (int i = 0; i < numOfThreads; i++) {
////            threadsRemovers.get(i).start();
////        }
//
//        for (Thread threadsRemover : threadsRemovers) {
//            threadsRemover.join();
//        }
//
//        System.out.println("num of removed is: " + numOfRemoved.intValue());
//        assertEquals(totalEnqueues - numOfRemoved.intValue(), pq.size());
//
//    }
//
//    @Test
//    public void multiEnqueueRemove2() throws InterruptedException {
//        List<StopableThread> producers = new ArrayList<>();
//        List<StopableThread> consumers = new ArrayList<>();
//        int totalEnqueues = 10;
//        int numOfThreads = 10;
//        Lock lock = new ReentrantLock();
//        AtomicInteger inputData = new AtomicInteger(0);
//        boolean[] isInsertLut = new boolean[totalEnqueues * 2];
//        for (boolean b : isInsertLut) {
//            b = false;
//        }
//        WaitablePQ<Integer> pq = new WaitablePQ<>();
//        class Producer extends StopableThread{
//            @Override
//            void threadAction() {
//                for (int i = 0; i < (totalEnqueues/numOfThreads); i++) {
//                    try {
//                        int data = inputData.incrementAndGet();
//                        pq.enqueue(new Integer(data));
//                        isInsertLut[data] = true;
//                    } catch (InterruptedException e) {
//                        throw new RuntimeException(e);
//                    }
//                }
//            }
//        }
//
//        class Consumer extends StopableThread{
//            @Override
//            void threadAction() {
//                for (int i = 0; i < (totalEnqueues/numOfThreads); i++) {
//                    int data = inputData.get();
//                    try {
//                        if(pq.remove(new Integer(data))){
//                            if (!(isInsertLut[data])){
//                                throw new NoSuchElementException("second remove");
//                            }
//                            isInsertLut[data] = false;
//                        }
//                    } catch (InterruptedException e) {
//                        throw new RuntimeException(e);
//                    }
//                }
//            }
//        }
//
//        for (int i = 0; i < numOfThreads; i++) {
//            producers.add(new Producer());
//            //consumers.add(new Consumer());
//        }
//
//        for (int i = 0; i < numOfThreads; i++) {
//            producers.get(i).start();
//           // consumers.get(i).start();
//        }
//
//        for (StopableThread producer : producers) {
//            producer.stopRunning();
//            producer.join();
//        }
//
////        for (StopableThread consumer : consumers) {
////            consumer.stopRunning();
////            consumer.join();
////        }
//
//        int count = 0;
//        for (boolean b : isInsertLut) {
//            if(b) { ++count;}
//        }
//        System.out.println("num of enqueues: " + totalEnqueues + " num of remained :" +  count);
//
//    }
//
//
//}



