package il.co.ilrd.jarLoader;

import org.junit.Test;
import java.util.Arrays;
import java.util.Iterator;
import static org.junit.Assert.*;

public class DynamicJarLoaderTest {
    public static String path2 = "/home/yair/git/fs/projects/src/GLinkedList.jar";
    public static String path3 = "/home/yair/Downloads/myJar.jar";

    @Test
    public void loadGenericLinkList() {
        DynamicJarLoader loader = new DynamicJarLoader(Iterable.class.getName());
        Class<?>[] list = loader.load(path2);
        Iterable obj;
        try {
          obj = (Iterable) (list[0].newInstance());
        } catch (InstantiationException e) {
            throw new RuntimeException(e);
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        }
        Iterator iterator = obj.iterator();
        assertFalse(iterator.hasNext());

    }
    @Test
    public void load() {
        DynamicJarLoader djl = new DynamicJarLoader(Comparable.class.getName());

        System.out.println(Arrays.toString(djl.load(path3)));

        Class<?> cl = djl.load(path3)[0];
        Comparable obj = null;
        try {
            obj = (Comparable) cl.newInstance();
        } catch (InstantiationException e) {
            throw new RuntimeException(e);
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        }

        obj.compareTo(obj);
    }
}