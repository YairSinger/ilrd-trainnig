package il.co.ilrd.concurrency;

public class Ex1 extends Thread {
    private volatile boolean runningFlag = true;
    public void run() {
        long startTime = System.currentTimeMillis();
        int i = 0;
        while (runningFlag) {
            System.err.println("thread num "+Thread.currentThread().getId());
            try {
                //Wait for one sec so it doesn't print too fast
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }

    public void setRunningFlag(boolean runningFlag) {
        this.runningFlag = runningFlag;
    }
}

class Test{
    public static void main(String[] args) {
        Ex1 ex1 = new Ex1();
        ex1.start();
        System.err.println("thread num "+Thread.currentThread().getId());
        try {
            //Wait for one sec so it doesn't print too fast
            Thread.sleep(5000);
            ex1.setRunningFlag(false);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}