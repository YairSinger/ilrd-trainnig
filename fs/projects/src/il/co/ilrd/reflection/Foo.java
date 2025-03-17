package il.co.ilrd.reflection;

import javax.swing.*;
import java.awt.*;
import java.lang.reflect.InvocationTargetException;
import java.util.Iterator;
import java.util.Spliterator;
import java.util.function.Consumer;

public final class Foo implements Iterable, Icon {
    static public int fooClassInt;
    public int fooInstanceInt;
    public void f1(){
        System.out.println("Foo f1 is called");
    }

    public Foo() {
        System.out.println("foo obj created");
    }

    @Override
    public Iterator iterator() {
        return null;
    }

    @Override
    public void forEach(Consumer consumer) {
        Iterable.super.forEach(consumer);
    }

    @Override
    public Spliterator spliterator() {
        return Iterable.super.spliterator();
    }

    @Override
    public void paintIcon(Component component, Graphics graphics, int i, int i1) {

    }

    @Override
    public int getIconWidth() {
        return 0;
    }

    @Override
    public int getIconHeight() {
        return 0;
    }

    public static void main(String[] args) throws InvocationTargetException, InstantiationException, IllegalAccessException, NoSuchMethodException {
        Foo foo1 = new Foo();
        ObjectAnalyzer analyzer = new ObjectAnalyzer(foo1);
        analyzer.printAncestor();
        analyzer.classInterfaces();
        analyzer.classModifiers();
        analyzer.classMembers();
        Foo foo2 = (Foo) analyzer.newInstanceAnalyzer();
       analyzer.callInstanceMethod(foo2, "f1");
    }
}
