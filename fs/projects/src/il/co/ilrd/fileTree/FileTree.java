//Project: FileTree
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Israel;
//Date: 11.02.2024
//Status: Approved

package il.co.ilrd.fileTree;

import il.co.ilrd.genericFactory.GenericFactory;
import il.co.ilrd.myUtils.ConsoleColors;

import java.io.File;
import java.util.*;

import static java.util.Collections.sort;

public class FileTree {
    private final FolderComposite folder;
    private final GenericFactory<Boolean,FileComponent,File> fileFactory = new GenericFactory<>();

    public FileTree(String path){
        if (path.equals(null)){
            throw new NullPointerException("path was null");
        }
        fileFactory.registerCreator(false,FolderComposite::new);
        fileFactory.registerCreator(true,FileLeaf::new);
        folder = new FolderComposite(new File(path));
    }

    public void display() {
        folder.display(0);
    }

    private static void printFileNameAndIndentation(int indentation, File file){
        char[] spaces = new char[indentation];
        Arrays.fill(spaces, ' ');
        if (file.isDirectory()){
            System.out.println(new String(spaces) +"├──" + ConsoleColors.BLUE + file.getName() + ConsoleColors.RESET);
        } else if (file.canExecute()) {
            System.out.println(new String(spaces) + "├──" +ConsoleColors.GREEN + file.getName()+ ConsoleColors.RESET);
        }
        else{
            System.out.println(new String(spaces) + "├──"+ ConsoleColors.WHITE + file.getName()+ ConsoleColors.RESET);
        }
    }

    private interface FileComponent{
        void display(int indentation);
    }

    private class FolderComposite implements FileComponent {
        private final List<FileComponent> components = new ArrayList<>();
        private final  File folder;

        public FolderComposite(File folder) {
            this.folder =  Objects.requireNonNull(folder);

            ArrayList<File> files = new ArrayList<File>(Arrays.asList(folder.listFiles()));
            Collections.sort(files);

            for (File file : files) {
                components.add(fileFactory.createObject(file.isFile(),file));
            }
        }

        @Override
        public void display(int indentation) {
           printFileNameAndIndentation(indentation,folder);

            for (FileComponent component : components) {
                component.display(indentation + 3);
            }
        }
    }

    private class FileLeaf implements FileComponent {

        private  final File file;

        private FileLeaf(File file) {
            this.file =  Objects.requireNonNull(file);

        }

        @Override
        public void display(int indentation) {
            printFileNameAndIndentation(indentation,file);
        }
    }
}

