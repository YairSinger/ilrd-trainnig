package il.co.ilrd.Singelton;

import il.co.ilrd.singelton.DoubleCheckedLockingSingleton;
import il.co.ilrd.singelton.EagerSingleton;
import il.co.ilrd.singelton.HolderSingleton;
import il.co.ilrd.singelton.LazySingleton;
import org.junit.Test;
import org.junit.jupiter.api.DisplayName;

import static org.junit.Assert.*;

public class SingletonTest {
    @Test
    @DisplayName("EagerSingleton")
    public void EagerSingleton(){
        EagerSingleton eager1 = EagerSingleton.getInstance();
        EagerSingleton eager2 = EagerSingleton.getInstance();
       assertEquals(eager1 , eager2);

    }

    @Test
    @DisplayName("LazySingleton")
    public void LazySingleton(){
        LazySingleton lazy1 = LazySingleton.getInstance();
        LazySingleton lazy2 = LazySingleton.getInstance();

        assertEquals(lazy1 , lazy2);

        TestWithThreadLazy thread1 = new TestWithThreadLazy();
        TestWithThreadLazy thread2 = new TestWithThreadLazy();

        thread1.start();
        thread2.start();

    }

    public class TestWithThread extends Thread{
        @Override
        public void run(){
            DoubleCheckedLockingSingleton double_checked_singleton1 = DoubleCheckedLockingSingleton.getInstance();
            System.out.println(double_checked_singleton1);
        }
    }
    @Test
    @DisplayName("DoubleCheckedLockingSingleton")
    public void DoubleCheckedLockingSingleton(){
        DoubleCheckedLockingSingleton double_checked_singleton1 = DoubleCheckedLockingSingleton.getInstance();
        DoubleCheckedLockingSingleton double_checked_singleton2 = DoubleCheckedLockingSingleton.getInstance();

        TestWithThread thread1 = new TestWithThread();
        TestWithThread thread2 = new TestWithThread();

        thread1.start();
        thread2.start();


        assertEquals(double_checked_singleton1 , double_checked_singleton2);
    }

    public class TestWithThreadLazy extends Thread{
        @Override
        public void run(){
            LazySingleton lazySingleton = LazySingleton.getInstance();
            System.out.println(lazySingleton);
        }
    }

    @Test
    @DisplayName("HolderSingleton")
    public void HolderSingleton(){
        HolderSingleton holder1 = HolderSingleton.getInstance();
        HolderSingleton holder2 = HolderSingleton.getInstance();
        assertEquals(holder1 , holder2);

    }

}