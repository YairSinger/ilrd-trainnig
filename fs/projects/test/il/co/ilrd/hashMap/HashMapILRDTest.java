package il.co.ilrd.hashMap;

import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
/*

import java.util.*;

import static java.lang.Character.valueOf;
import static org.junit.Assert.*;

public class HashMapILRDTest {

    static HashMapILRD<String, Integer> hashMap = null;
    static List<Integer> integerList = new ArrayList<>();
    static List<String> stringList = new ArrayList<>();

    @BeforeClass
    public static void beforeAll(){
    hashMap = new HashMapILRD<>(10);
        for (int i = 0; i < 26; i++) {
            integerList.add(i , i);
            stringList.add(i, Character.valueOf((char) ('a' + i)).toString());
        }

    }


    public void loadAZToHash() {
        for (int i = 0; i < 26; i++) {
            hashMap.put(stringList.get(i), integerList.get(i));
        }
    }



    @AfterEach
    public void clearMap(){
       hashMap.clear();
    }


    @Test
    public void isEmpty() {
       assertTrue(hashMap.isEmpty());
       hashMap.put("a",1);
        assertFalse(hashMap.isEmpty());
        hashMap.remove("a");
        assertTrue(hashMap.isEmpty());


    }

    @Test
    public void tesNullKey() {

        hashMap.put(null,1);

        assertFalse(hashMap.isEmpty());
        hashMap.put("a",1);
        assertTrue(hashMap.containsKey(null));
        Integer integer = hashMap.get(null);
        assertEquals(1,integer.intValue());
        integer = hashMap.put(null,3);

        assertEquals(1, integer.intValue());

    }

    @Test
    public void tesNullValue() {

        hashMap.put("a",null);

        assertFalse(hashMap.isEmpty());
        hashMap.put("b",null);
        assertEquals(2, hashMap.size());

        assertTrue(hashMap.containsValue(null));
        Integer integer = hashMap.put("a", 1);

       assertNull(integer);

    }


    @Test
    public void containsKey() {
        Integer integer = valueOf(1);
        assertFalse(hashMap.containsKey("a"));
        assertFalse(hashMap.containsKey(integer));
        hashMap.put("a",1);
        assertTrue(hashMap.containsKey("a"));
        hashMap.remove("a");
    }

    @Test
    public void containsValue() {
       Integer integer = new Integer(1);
        assertFalse(hashMap.containsValue(integer));
        hashMap.put("a",1);
        assertTrue(hashMap.containsValue(integer));
        hashMap.remove("a");
    }

    @Test
    public void getAndPut() {

        hashMap.put("a",1);
        Integer integer = hashMap.get("a");
        assertEquals(1,integer.intValue());
        integer = hashMap.get("b");
        assertNull(integer);
        hashMap.remove("a");
    }


    @Test
    public void remove() {
       Integer integer = hashMap.remove("a");
       assertNull(integer);
        hashMap.put("a",1);
        integer = hashMap.remove("a");
        assertEquals(1,integer.intValue());

    }

    @Test
    public void putAll() {
        HashMapILRD<String, Integer> tempHash = new HashMapILRD<>();
        tempHash.put("sk", 1);
        tempHash.put("a1", 1);
        tempHash.put("a", -5);
        assertEquals(3, tempHash.size());
        loadAZToHash();
        tempHash.putAll(hashMap);
        assertEquals(28,tempHash.size());
        assertEquals(0,tempHash.get("a").intValue());




    }

    @Test
    public void clear() {
        loadAZToHash();
        assertEquals(26, hashMap.size());
        hashMap.clear();
        assertEquals(0, hashMap.size());
        assertTrue(hashMap.isEmpty());

    }

    @Test
    public void keySet() {
        loadAZToHash();
        Set<String> keys = hashMap.keySet();
        assertEquals(26, keys.size());
        for (String key : keys) {
            System.out.println(key);
        }
    }

    @Test
    public void values() {
        loadAZToHash();
        Collection<Integer> values = hashMap.values();
        assertEquals(26,values.size());
        for (Integer value : values) {
            System.out.println(value);
        }
    }

    @Test
    public void entrySet() {
        loadAZToHash();
        Set<Map.Entry<String,Integer>> entrySet = hashMap.entrySet();
        assertEquals(26,entrySet.size());

        for (Map.Entry<String, Integer> stringIntegerEntry : entrySet) {
            System.out.println(stringIntegerEntry);
        }
        hashMap.clear();
        assertTrue(hashMap.isEmpty());

    }
}*/
