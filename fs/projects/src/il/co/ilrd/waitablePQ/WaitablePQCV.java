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
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;


public class WaitablePQCV<E>{
    private PriorityQueue<E> pq;
    private ReentrantLock lock;
    private Condition condVar;

    public WaitablePQCV(){ // Only if E inmplements comperable
        this(null);
    }
    public WaitablePQCV(Comparator<? super E> comperator){
        lock = new ReentrantLock();
        condVar = lock.newCondition();
        pq = new PriorityQueue<>(comperator);
    }

    public E dequeue() throws InterruptedException{
        return dequeue(Long.MAX_VALUE, TimeUnit.DAYS);
    }
    public E dequeue(Long timeOut , TimeUnit unit) throws InterruptedException{ // Advanced
        E polled = null;
        lock.lock();
        try {
            while(isEmpty()){
                if(!condVar.await(timeOut,unit)){
                    return null;
                }
            }
            polled = pq.poll();
        } finally {
            lock.unlock();
        }
        return polled;
    }

    public boolean remove(E element) throws InterruptedException{
        Objects.requireNonNull(element);
        lock.lock();
        boolean isRemoved = false;
        try {
            isRemoved = pq.remove(element);
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
            condVar.signalAll();
        } finally {
            lock.unlock();
        }
    }

    public int size() {
        return pq.size();
    }

    public boolean isEmpty(){
        return pq.isEmpty();
    }
}
