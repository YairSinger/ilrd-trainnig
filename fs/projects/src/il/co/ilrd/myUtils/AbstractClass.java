package il.co.ilrd.myUtils;

abstract class StopableThread extends Thread{
    private boolean stopRunning = false; // private variables are not inherited!
    @Override
    public void run(){
        while (!stopRunning) {
            threadAction();
        }
    }

    public void setStopRunning(boolean stopRunning) {
        this.stopRunning = stopRunning;
    }

    abstract void threadAction();
    public void stopRunning() {

        setStopRunning(true);
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
