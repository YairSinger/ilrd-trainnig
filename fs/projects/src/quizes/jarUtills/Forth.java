package quizes.jarUtills;

public class Forth implements Runnable{

    static {
        System.out.println("Forth Loaded");
    }
    public static void printFirst(){
        System.out.println("print Forth");
    }
    @Override
    public void run() {
        System.out.println("Forth run");
    }


}
