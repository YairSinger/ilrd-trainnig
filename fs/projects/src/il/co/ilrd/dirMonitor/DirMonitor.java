//Project: DirMonitor
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Yael
//Date: 05.03.2024
//status: pre-reviewed

package il.co.ilrd.dirMonitor;




import il.co.ilrd.observer.*;
import java.io.IOException;
import java.nio.file.*;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class DirMonitor<T> {
    private Thread watcher;
    private WatchService watchService;
    private final Dispatcher<WatchEvent<T>> dispatcher;

    private final Lock lock;
    private volatile boolean isMonitoring = true;

    public DirMonitor(String pathToFolder ,WatchEvent.Kind<?>[] events){
        lock = new ReentrantLock();
        createWatchService(pathToFolder,events);
        dispatcher = new Dispatcher<>();
        initWatcherThread();
    }
    public void subscribe(Callback<WatchEvent<T>> call){
        dispatcher.subscribe(Objects.requireNonNull(call));
    }

    public void unsubscribe(Callback<WatchEvent<T>> call){
        dispatcher.unsubscribe(Objects.requireNonNull(call));
    }

    public void startMonitor(){
        if (!watcher.isAlive()){
            watcher.start();
        }

        if(!isMonitoring) {
            lock.unlock();
            isMonitoring = true;
        }
    }

    public void stopMonitor(){
        isMonitoring = false;
        lock.lock();
    }

    private void initWatcherThread(){

        watcher = new Thread(() -> {
            WatchKey watchKey;
            while (true) {
                try {lock.lock();
                }finally {lock.unlock();
                }
                try {
                    if ((watchKey = watchService.take()) == null) break;
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                List<WatchEvent<?>> list = watchKey.pollEvents();

                for (WatchEvent<?> event : list ) {
                    if(list.size() > 1 && event.kind().equals( StandardWatchEventKinds.ENTRY_CREATE)){
                    }else{
                        @SuppressWarnings("unchecked")
                        WatchEvent<T> eventRef = (WatchEvent<T>)event;
                    dispatcher.updateAll(eventRef);
                    }
                }
                watchKey.reset();
            }
        });
    }

    private void createWatchService(String pathToFolder, WatchEvent.Kind<?>[] events){

        try {
            watchService = FileSystems.getDefault().newWatchService();
            Path path = Paths.get(Objects.requireNonNull(pathToFolder));
            path.register(watchService,Objects.requireNonNull(events));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

}