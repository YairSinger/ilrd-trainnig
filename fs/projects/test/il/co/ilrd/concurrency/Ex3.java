package il.co.ilrd.concurrency;

import java.util.*;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Ex3 {
    public  AtomicBoolean pongFlag = new AtomicBoolean(false);
    public Semaphore pongSemaphore = new Semaphore(1);
    public Semaphore pingSemaphore = new Semaphore(0);
    public Semaphore producedSem = new Semaphore(0);
    public Semaphore waitingForMassage = new Semaphore(0);


    private final LinkedList<String> list = new LinkedList<>();



    public void pong(){
      while(true) {
          if (pongFlag.get()) {
              System.err.println("pong");
              pongFlag.set(false);
              return;
          }
      }
    }

    public  void ping(){
        while (true) {
            if (!pongFlag.get()) {
                System.err.println("ping");
                pongFlag.set(true);
                return;
            }
        }
    }

    public void pongSem() throws InterruptedException {
        pingSemaphore.acquire();
        System.err.println("pong");
        pongSemaphore.release();
    }
    public void pingSem() throws InterruptedException {
        pongSemaphore.acquire();
        System.err.println("ping");
        pingSemaphore.release();
    }

    public static void main(String[] args) throws InterruptedException {
        pingPong();
        pingPongSemaphores();
        producersConsumers();
        producersConsumersSem();
        oneProducerMultiConsumers();
    }
    public static void pingPong() throws InterruptedException {
        Ex3 ex3 = new Ex3();
        ReentrantLock lock = new ReentrantLock();
        List<Thread> threads = new ArrayList<Thread>();
        threads.add(new Thread(() -> {
            for (int i = 0; i < 10; i++) {
                ex3.ping();
            }
        }));
        threads.add(new Thread(() -> {
            for (int i = 0; i < 10; i++) {
                ex3.pong();
            }
        }));
        System.err.println("ping pong with atomic var");
        for (Thread thread : threads) {
            thread.start();
        }
        for (Thread thread : threads) {
            thread.join();
        }
    }

    public static void producersConsumers() throws InterruptedException {
      Ex3 ex3 = new Ex3();
        List<Thread> threads = new ArrayList<>();
        for (int i = 0; i < 10; i++) {//producer

            threads.add(new Thread(() -> {
                for (int j = 0; j < 5; j++) {
                    synchronized (ex3.list) {
                        ex3.list.add(j + " produced by " + Thread.currentThread().getId());
                    }
                }
            }));
        }
        for (int i = 0; i < 10; i++) {
            threads.add(new Thread(() -> {
                for (int j = 0; j < 50; j++) {

                    synchronized (ex3.list){

                    if(!(ex3.list.isEmpty())){

                            System.err.println( ex3.list.pop());

                        }
                }
                }
            }));
        }

        System.err.println("Multi Producer Multi Consumer WO Semaphore");
        for (Thread thread : threads) {
            thread.start();
        }
        for (Thread thread : threads) {
            thread.join();
        }
    }

    public static void producersConsumersSem() throws InterruptedException {
        Ex3 ex3 = new Ex3();
        List<Thread> threads = new ArrayList<>();
        for (int i = 0; i < 10; i++) {//producer

            threads.add(new Thread(() -> {
                for (int j = 0; j < 5; j++) {
                    synchronized (ex3.list) {
                        ex3.list.add(j + " produced by " + Thread.currentThread().getId());
                        ex3.producedSem.release();
                    }
                }
            }));
        }
        for (int i = 0; i < 10; i++) {//consumers
            threads.add(new Thread(() -> {

                for (int j = 0; j < 5; j++) {
                    synchronized (ex3.list){
                        try {
                            ex3.producedSem.acquire();
                            if(!(ex3.list.isEmpty())){
                                System.err.println( ex3.list.pop());
                            }
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }

                    }
                }
            }));
        }

        System.err.println("Multi Producer Multi Consumer with Semaphore");
        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            thread.join();
        }
    }

    public static void pingPongSemaphores() throws InterruptedException {
        Ex3 ex3 = new Ex3();
        List<Thread> threads = new ArrayList<Thread>();
        threads.add(new Thread(new Runnable() {

            @Override
            public void run() {
                for (int i = 0; i < 10; i++) {
                    try {
                        ex3.pingSem();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        }));
        threads.add(new Thread(new Runnable() {

            @Override
            public void run() {
                for (int i = 0; i < 10; i++) {
                    try {
                        ex3.pongSem();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        }));
        System.err.println("ping pong with 2 semaphores");
        for (Thread thread : threads) {
            thread.start();
        }
        for (Thread thread : threads) {
            thread.join();
        }
    }

    public static void oneProducerMultiConsumers() throws InterruptedException {
        Ex3 ex3 = new Ex3();
        final Integer[] versionNumber = {new Integer(0)};
        ReentrantLock reentrantLock = new ReentrantLock();
        Condition versionUpdate = reentrantLock.newCondition();

        List<Thread> threads = new ArrayList<Thread>();
        Integer numOfConsumers = new Integer(4);
        threads.add(new Thread(new Runnable() {  //producer
            @Override
            public void run() {
                for (int j = 0; j < 3; j++) {

                    for (int k = 0; k < numOfConsumers.intValue(); k++) {
                        try {
                            ex3.waitingForMassage.acquire();
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }
                    ++versionNumber[0];
                    reentrantLock.lock();
                    versionUpdate.signalAll();
                    reentrantLock.unlock();

                }
            }
        }));

        for (int i = 0; i < numOfConsumers; i++) {//consumers
            threads.add(new Thread(new Runnable() {
                @Override
                public void run() {
                    Integer oldVersion = new Integer(-1);

                    for (int j = 0; j < 3; j++) {


                        reentrantLock.lock();
                        ex3.waitingForMassage.release();

                        while (oldVersion.equals(versionNumber[0])) {
                            try {
                                versionUpdate.await();
                            } catch (InterruptedException e) {
                                throw new RuntimeException(e);
                            }
                        }

                        reentrantLock.unlock();
                        oldVersion = versionNumber[0].intValue();
                        System.err.println(Thread.currentThread().getId() + " Thread received version No" + versionNumber[0].intValue());
                    }

                }
            }));

        }

        System.err.println("Condition vars");
        for (Thread thread : threads) {
            thread.start();
        }
        for (Thread thread : threads) {
            thread.join();
        }
    }
}



