//Project: HolderSingleton
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Yaara
//Date: 10.01.2024
//Status: Approved


package il.co.ilrd.singelton;

public class HolderSingleton {
    private HolderSingleton(){};

    private static class NestedHolderSingleton{
        private static final HolderSingleton instance = new HolderSingleton();
    }

    public static HolderSingleton getInstance(){
        return NestedHolderSingleton.instance;
    }
}
