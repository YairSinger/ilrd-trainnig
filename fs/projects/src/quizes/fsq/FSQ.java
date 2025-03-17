package quizes.fsq;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class FSQ<E> {
    private final int capacity;
    private final Object[] buffer;
    private final Semaphore deqSem;
    private final Semaphore enqSem;
    private final Lock deqLock;
    private final Lock enqLock;
    private int deqInx;
    private int enqInx;

    public FSQ(int capacity) {
        this.capacity = capacity;
        buffer = new Object[capacity];
        deqSem = new Semaphore(0);
        enqSem = new Semaphore(capacity);
        deqLock = new ReentrantLock();
        enqLock = new ReentrantLock();
        deqInx = 0;
        enqInx = 0;
    }

    public void enququ(E element){
        try {
            enqSem.acquire();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        enqLock.lock();
        try {
            buffer[enqInx] = element;
            enqInx = (enqInx + 1) % capacity;
        }finally {
            enqLock.unlock();
        }
        deqSem.release();
    }

    @SuppressWarnings("unchecked")
    public E dequeue(){
                deqLock.lock();
        E element;
        try {
            deqSem.acquire();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        try {
           element  = (E) buffer[deqInx];
            deqInx = (deqInx + 1) % capacity;
        }finally {
            deqLock.unlock();
        }
        enqSem.release();
        return element;
    }


}
