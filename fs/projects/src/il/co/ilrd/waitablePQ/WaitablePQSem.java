//Project: WaitablePQ
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Yuval
//Date: 18.02.2024
//

package il.co.ilrd.waitablePQ;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantLock;


public class WaitablePQSem<E>{
    private PriorityQueue<E> pq;
    private Semaphore sem = new Semaphore(0);
    private ReentrantLock lock = new ReentrantLock();

    public WaitablePQSem(){ // Only if E inmplements comperable
        this(null);
    }
    public WaitablePQSem(Comparator<? super E> comperator){
        pq = new PriorityQueue<>(comperator);
    }

    public int size(){
        return pq.size();
    }

    public boolean isEmpty(){
        return pq.isEmpty();
    }

    public E dequeue() throws InterruptedException{
       return dequeue(Long.MAX_VALUE, TimeUnit.DAYS);
    }
    public E dequeue(long timeOut, TimeUnit unit) throws InterruptedException { // Advanced
      if(!sem.tryAcquire(1,timeOut, unit)){ return null;}

        E polled = null;
        lock.lock();
        try {
            polled = pq.poll();
        } finally {
            lock.unlock();
        }

        return polled;
    }

    public boolean remove(E element) throws InterruptedException{
        Objects.requireNonNull(element);
        boolean isRemoved = false;
        lock.lock();
        try {
            if(sem.tryAcquire()){
              if(pq.remove(element)) {
                  isRemoved = true;
              }else{
                  sem.release();
              }
            }
        } finally {
            lock.unlock();
        }
       return isRemoved;
    }


    public void enqueue(E element) throws InterruptedException {
        Objects.requireNonNull(element);
        lock.lock();
        try {
            pq.add(element);
            sem.release();
        } finally {
            lock.unlock();
        }
    }

}
