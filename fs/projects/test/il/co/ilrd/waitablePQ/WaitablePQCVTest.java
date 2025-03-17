package il.co.ilrd.waitablePQ;

import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

public class WaitablePQCVTest {
    @Test
    public void singleThreadComparable() throws InterruptedException {
        WaitablePQCV<Integer> pq = new WaitablePQCV<>();
        pq.enqueue(new Integer(5));
        pq.enqueue(new Integer(0));
        Integer integer = new Integer(7);
        pq.enqueue(integer);
        assertEquals(0, pq.dequeue().intValue());
        assertEquals(5, pq.dequeue().intValue());
        assertTrue(pq.remove(integer));
        assertFalse(pq.remove(integer));

    }

    @Test
    public void singleThreadComparator() throws InterruptedException {
        Lavrador lavrador = new Lavrador(12, 120, "Yair");
        Lavrador lavrador2 = new Lavrador(14, 150, "Yair");
        Lavrador lavrador3 = new Lavrador(20, 120, "Yair");
        Lavrador lavrador4 = new Lavrador(4, 160, "Yair");

        WaitablePQCV<Dog> pq = new WaitablePQCV<>(new Dog(1));
        pq.enqueue(lavrador);
        pq.enqueue(lavrador2);
        pq.enqueue(lavrador3);
        pq.enqueue(lavrador4);

        assertEquals(4, pq.dequeue().getAge());
        assertEquals(12, pq.dequeue().getAge());
        assertTrue(pq.remove(lavrador2));
        assertFalse(pq.remove(lavrador4));
    }

    @Test
    public void multiThreadsEnqueue() throws InterruptedException {
        List<Thread> threads = new ArrayList<Thread>();
        int numOfThreads = 10;
        int totalEnqueues = 2000000;
        WaitablePQCV<Integer> pq = new WaitablePQCV<>();
        for (int i = 0; i < numOfThreads; i++) {//consumers
            int finalI = i;
            threads.add(new Thread(new Runnable() {
                @Override
                public void run() {
                    for (int j = finalI * totalEnqueues / numOfThreads; j < (finalI + 1) * (totalEnqueues / numOfThreads); j++) {
                        try {
                            pq.enqueue(new Integer(j));
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }

                }
            }));

        }

        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            thread.join();
        }

        assertEquals(totalEnqueues, pq.size());
        for (int i = 0; i < totalEnqueues; i++) {
            assertEquals(i, pq.dequeue().intValue());
        }
    }

    @Test
    public void multiThreadsEnqueueAndDequeue() throws InterruptedException {
        List<Thread> threads = new ArrayList<Thread>();
        int numOfThreads = 17;
        int totalEnqueues = 100000;

        WaitablePQCV<Integer> pq = new WaitablePQCV<>();
        for (int i = 0; i < numOfThreads; i++) {//consumers
            int finalI = i;
            threads.add(new Thread(new Runnable() {
                @Override
                public void run() {
                    for (int j = finalI * totalEnqueues / numOfThreads; j < (finalI + 1) * (totalEnqueues / numOfThreads); j++) {
                        try {
                            pq.enqueue(new Integer(j));
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }

                }
            }));

        }
        List<Thread> threadsDequeuers = new ArrayList<Thread>();
        for (int i = 0; i < numOfThreads; i++) {//consumers
            int finalI = i;

            threadsDequeuers.add(new Thread(new Runnable() {
                int counter = 0;
                int threadInx = finalI;
                int firstInx = finalI * totalEnqueues / numOfThreads;
                int lastInx = (finalI + 1) * (totalEnqueues / numOfThreads);
                @Override
                public void run() {
                    for (int j = firstInx ; j < lastInx; j++) {
                        try {
                            pq.dequeue();
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }

                }

            }));

        }
        for (Thread threadsRemover : threadsDequeuers) {
            threadsRemover.start();
        }
        for (Thread thread : threads) {
            thread.start();
        }


        for (int threadInx=0; threadInx < numOfThreads;++threadInx) {
            threads.get(threadInx).join();
            threadsDequeuers.get(threadInx).join();
        }

        assertTrue( pq.isEmpty());
    }

}