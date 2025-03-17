package il.co.ilrd.dirMonitor;

import com.sun.beans.util.Cache;
import il.co.ilrd.observer.Callback;
import il.co.ilrd.observer.Dispatcher;
import org.junit.Test;

import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.util.function.Function;

import static org.junit.Assert.*;

public class DirMonitorTest {

//    @Test
//    public void newFileUpdate(){
//        DirMonitor dirMonitor = new DirMonitor<>("/home/yair/git/prjects/plagAndPlayFolder",
//                new WatchEvent.Kind<?>[]{StandardWatchEventKinds.ENTRY_MODIFY});
//        Callback<WatchEvent<?>> callback = new Callback<>(new Updater(),new StopDirMonitor());
//        dirMonitor.subscribe(callback);
//        dirMonitor.startMonitor();
//        try {
//            Thread.sleep(10000);
//            //add .jar file
//            // add non .jar file
//        } catch (InterruptedException e) {
//            throw new RuntimeException(e);
//        }
//        dirMonitor.stopMonitor();
//        System.out.println("dirMonitor is paused");
//        try {
//            Thread.sleep(10000);
//            //add .jar file
//            // add non .jar file
//        } catch (InterruptedException e) {
//            throw new RuntimeException(e);
//        }
//        dirMonitor.startMonitor();
//        System.out.println("dirMonitor resumed");
//        try {
//            Thread.sleep(10000);
//
//        } catch (InterruptedException e) {
//            throw new RuntimeException(e);
//        }
//        dirMonitor.unsubscribe(callback);
//        System.out.println(" unsubscribed from dirMonitor ");
//        try {
//            Thread.sleep(10000);
//
//        } catch (InterruptedException e) {
//            throw new RuntimeException(e);
//        }

    }



