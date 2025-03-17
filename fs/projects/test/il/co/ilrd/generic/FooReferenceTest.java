package il.co.ilrd.generic;

import il.co.ilrd.reflection.Foo;
import org.junit.Test;

import static org.junit.Assert.*;

public class FooReferenceTest {

    @Test
    public void setAndGet() {
        FooReference ref = new FooReference();
        Integer integer = new Integer(4);
        Character character = new Character('j');
        ref.set(integer);
        System.out.println(ref.get().getClass().getName());
        ref.set(character);
        System.out.println(ref.get().getClass().getName());
        FooReference ref2 = new FooReference(integer);

        System.out.println(ref2.get().getClass().getName());
    }


}