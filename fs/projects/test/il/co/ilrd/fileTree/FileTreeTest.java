package il.co.ilrd.fileTree;

import org.junit.jupiter.api.Test;

import static org.junit.Assert.*;

public class FileTreeTest {
    @Test
    public void testTree(){
        FileTree tree = new FileTree("/home/yair/git/utils");
        tree.display();


    }

}