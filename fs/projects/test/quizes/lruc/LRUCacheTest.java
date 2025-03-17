//Writer: Yair Singer
//Date 28.01.2024


package quizes.lruc;

import org.junit.Test;

import static org.junit.Assert.*;

public class LRUCacheTest {

    @Test
    public void putGet() {
        Integer defaultValue = new Integer(-1);
        Integer received = null;
        LRUCache lruCache = new LRUCache(3);
        lruCache.put("one", new Integer(1));
        lruCache.put("two", new Integer(2));
        lruCache.put("three", new Integer(3));
        lruCache.put("four", new Integer(4));

        received = (Integer) lruCache.get("four", defaultValue);
        assertEquals(4,received.intValue());

        received = (Integer) lruCache.get("three", defaultValue);
        assertEquals(3,received.intValue());

        received = (Integer) lruCache.get("one", defaultValue);
        assertEquals(-1,received.intValue());
        lruCache.put("one", new Integer(1));


        received = (Integer) lruCache.get("one", defaultValue);
        assertEquals(1 ,received.intValue());
        received = (Integer) lruCache.get("two", defaultValue);
        assertEquals(-1,received.intValue());




    }


}