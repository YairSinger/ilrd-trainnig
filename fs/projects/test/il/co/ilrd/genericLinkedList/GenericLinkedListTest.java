package il.co.ilrd.genericLinkedList;

import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.DisplayName;

import java.util.*;

import static org.junit.Assert.*;

public class GenericLinkedListTest {

    static GenericLinkedList<Integer> list = null;
    static GenericLinkedList<Integer> list2 = null;
    static GenericLinkedList<String> listStrings = null;
    static List<String> strList = null;
    static List<Integer> integerList = null;

//    static Iterator<E> iterator = null;
    @BeforeClass
    public static void preTests(){
        list = new GenericLinkedList<>();
        list2 = new GenericLinkedList<>();

        listStrings = new GenericLinkedList<>();
        strList = new ArrayList<>();
        strList.add("one");
        strList.add("two");
        strList.add("three");
        strList.add("four");

        integerList = new ArrayList<>();
        integerList.add(1);
        integerList.add(2);
        integerList.add(3);
        integerList.add(4);
        integerList.add(5);
        integerList.add(6);
        integerList.add(7);
        integerList.add(8);






    }

    @AfterEach
    public void resetList(){
        while(list.size() > 0){
            list.popFront();
        }
        while(strList.size() > 0){
            list.popFront();
        }
    }


    @Test
    public void pushFront() {

        Integer integer = new Integer(5);
        assertEquals(list.size(),0);
        list.pushFront(integer);
        assertEquals(list.size(),1);
        Integer returned = list.popFront();
        assertEquals(returned.intValue(), 5);
        assertEquals(list.size(), 0);
    }




    @Test
    public void isEmpty() {
        assertTrue(list.isEmpty());
        Integer integer = new Integer(5);
        list.pushFront(integer);
        assertFalse(list.isEmpty());
    }

    @Test
    public void find() {
        for (int i = 0; i < 4; i++) {
            listStrings.pushFront(strList.get(i));
        }
        assertEquals(strList.size(), 4);
        Iterator<String> iterator = listStrings.find("four");
        String res = iterator.next();
        assertEquals("four", res);
        iterator = listStrings.find("ytgy6");
        Iterator<String> finalIterator = iterator;
        assertThrows(NoSuchElementException.class, () -> {
            finalIterator.next();});
        iterator = listStrings.find("one");
        res = iterator.next();
        assertEquals( "one", res);
    }

    @Test
    public void merge(){
        for (int i = 0; i < 4; i++) {
            list.pushFront(integerList.get(i));
            list2.pushFront(integerList.get(i + 4));
        }
        GenericLinkedList<Integer> merged = GenericLinkedList.merge(list,list2);
        assertEquals(8, merged.size());

    }

    @Test
    public void newReverse(){
        for (int i = 0; i < 4; i++) {
            listStrings.pushFront(strList.get(i));
        }
        GenericLinkedList<String> reversed = GenericLinkedList.newReverse(listStrings);
        System.out.println("before reverse");
        for (String s : listStrings) {
            System.out.println(s);
        }

        System.out.println("reversed");
        for (String s : reversed) {
            System.out.println(s);
        }
    }

    @Test
    @DisplayName("testExceptions")
    public void testExceptions(){
        for (int i = 0; i < 4; i++) {
            listStrings.pushFront(strList.get(i));
        }
        Iterator<String> iterator = listStrings.find("two");
        assertTrue(iterator.hasNext());
        listStrings.pushFront("yfgy");
        Iterator<String> finalIterator1 = iterator;
        assertThrows(ConcurrentModificationException.class, () -> {
            finalIterator1.next();});
        iterator = listStrings.find("two");
        assertTrue(iterator.hasNext());
        listStrings.popFront();
        Iterator<String> finalIterator = iterator;
        assertThrows(ConcurrentModificationException.class, () -> {
            finalIterator.next();});

    }



}
