//Project: DoubleCheckedLockingSingleton
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Yaara
//Date: 10.01.2024
//Status: Approved


package il.co.ilrd.singelton;


public class DoubleCheckedLockingSingleton {
   private static DoubleCheckedLockingSingleton instance;
    private DoubleCheckedLockingSingleton() {
        System.out.println("DoubleCheckedLockingSingleton instance was created");
    }
    public static DoubleCheckedLockingSingleton getInstance(){
        if (instance == null) {
            synchronized (DoubleCheckedLockingSingleton.class){
                if (instance == null) {
                    instance = new DoubleCheckedLockingSingleton();
                }
            }
        }
        return instance;
    }
}
