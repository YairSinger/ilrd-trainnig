//Project: LazySingleton
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Yaara
//Date: 10.01.2024
//Status: Approved

package il.co.ilrd.singelton;

public class LazySingleton {
    private volatile static LazySingleton instance;

    private LazySingleton() {}
    public static LazySingleton getInstance(){
        if (instance == null){
            instance = new LazySingleton();
        }
        return instance;
    }
}
