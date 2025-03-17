package quizes.jarUtills;

public class First implements Runnable{
    static {
        System.out.println("First Loaded");
    }
    public static void printFirst(){
        System.out.println("print First");
    }
    @Override
    public void run() {
        System.out.println("First run");
    }
}
