//Project: CommandPlugAndPlayFactory
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Yuval
//Date: 07.03.2024
//status: approved


package il.co.ilrd.plugAndPlay;


import il.co.ilrd.dirMonitor.DirMonitor;
import il.co.ilrd.genericFactory.GenericFactory;
import il.co.ilrd.jarLoader.DynamicJarLoader;
import il.co.ilrd.observer.Callback;
import il.co.ilrd.rps.CmdCreator;
import il.co.ilrd.rps.ICommand;


import java.io.File;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.util.Objects;


public class CommandPlugAndPlayFactory<K,D> {
    private final String pathToFolderMonitored;
    private final GenericFactory<K, ICommand, D> factory;


    public CommandPlugAndPlayFactory(String pathToFolder, GenericFactory<K, ICommand, D> factory) {
        this.pathToFolderMonitored = Objects.requireNonNull(pathToFolder);
        this.factory = Objects.requireNonNull(factory);
        CommandClassLoader<ICommand> loader = new CommandClassLoader<>();
        loader.loadExisting(pathToFolderMonitored);

        DirMonitor<ICommand> dirMonitor = new DirMonitor<>(pathToFolder, new WatchEvent.Kind<?>[]{StandardWatchEventKinds.ENTRY_MODIFY,
                StandardWatchEventKinds.ENTRY_CREATE});
        loader.subscribe(dirMonitor);
        dirMonitor.startMonitor();

    }

    private class CommandClassLoader<T> {  // for test
        private final Callback<WatchEvent<T>> callback;
        private final DynamicJarLoader jarLoader;

        private CommandClassLoader() {
            jarLoader = new DynamicJarLoader(CmdCreator.class.getName());
            callback = new Callback<>((event) -> {
                loadNewJarClasses(event);
                return null;
            }
                    , (Void) -> {
                System.out.println("unsubscribed");
                return null;
            });
        }

        private void subscribe(DirMonitor<T> monitor) {
            monitor.subscribe(callback);
        }

        private void loadExisting(String pathToFolder) {
            File folder = new File(pathToFolder);
            for (File file : Objects.requireNonNull(folder.listFiles())) {
                if (file.isFile() && file.getName().endsWith(".jar")) {
                    Class<?>[] loadedClasses = jarLoader.load(file.getAbsolutePath());
                    addToFactory(loadedClasses);
                }
            }
        }

        @SuppressWarnings("unchecked")
        private void addToFactory(Class<?>[] classes) {
            for (Class<?> aClass : classes) {
                CmdCreator<K,D> cmdCreator;
                try {
                    cmdCreator = (CmdCreator<K,D>) aClass.newInstance();
                } catch (InstantiationException | IllegalAccessException e) {
                    throw new RuntimeException(e);
                }
                CmdCreator<K,D> finalCmdCreator = cmdCreator;
                factory.registerCreator(cmdCreator.getKey(), finalCmdCreator::createCommand);
            }
        }

        private void loadNewJarClasses(WatchEvent<?> event) {
            if (event.context().toString().endsWith(".jar")) {
                Class<?>[] loadedClasses = jarLoader.load(pathToFolderMonitored + "/" + event.context().toString());
                addToFactory(loadedClasses);
            }
        }

    }
}

