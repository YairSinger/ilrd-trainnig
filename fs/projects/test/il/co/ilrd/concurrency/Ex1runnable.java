package il.co.ilrd.concurrency;

public class Ex1runnable implements Runnable{
    private volatile boolean runFlag = true;
    @Override
    public void run() {
        long startTime = System.currentTimeMillis();
        int i = 0;
        while (runFlag) {
            System.err.println("thread num "+Thread.currentThread().getId());
            try {
                //Wait for one sec so it doesn't print too fast
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }

    public void setRunFlag(boolean runFlag) {
        this.runFlag = runFlag;
    }
}

class Test2{
    public static void main(String[] args) {
        Ex1runnable ex1 = new Ex1runnable();
        Thread thread = new Thread(ex1, "t1");
        thread.start();
       System.err.println("thread num "+Thread.currentThread().getId());
        try {
            //Wait for one sec so it doesn't print too fast
            Thread.sleep(5000);
            ex1.setRunFlag(false);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

