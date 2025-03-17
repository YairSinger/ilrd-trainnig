package il.co.ilrd.waitablePQ;

public abstract class StopableThread extends Thread{
    public boolean stopRunning = false; // private variables are not inherited!
    @Override
    public void run(){
        while (!stopRunning) {
            threadAction();
        }
    }
    abstract void threadAction();
    public void stopRunning() {
        stopRunning = true;
    }
    static void nap(int n){
        try {
            Thread.sleep(n);
        }
        catch (InterruptedException e){
            System.err.println(e);
        }
    }
}
