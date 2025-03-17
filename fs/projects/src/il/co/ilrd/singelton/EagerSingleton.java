//Project: EagerSingleton
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Yaara
//Date: 10.01.2024
//Status: Approved

package il.co.ilrd.singelton;

public class EagerSingleton {
    private  static final EagerSingleton instance = new EagerSingleton();

    private EagerSingleton() {}
    public static EagerSingleton getInstance(){
        return instance;
    }
}
