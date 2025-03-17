package quizes.jarUtills;

public class Third implements Runnable{
    static {
        System.out.println("Third loaded");
    }
    public static void printThird(){
        System.out.println("print Third");
    }
    @Override
    public void run() {
        System.out.println("Third run");
    }
}
