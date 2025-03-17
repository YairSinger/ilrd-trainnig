package quizes.lruc;

import java.util.LinkedHashMap;
import java.util.Map;

public class LRUCache<K, V> {

    private LinkedHashMap<K,V> map = null;
    private int capacity = 0;
    public LRUCache(int maxCapacity) {
        this.capacity = maxCapacity;
        map = new LinkedHashMap<K,V>(maxCapacity, 0.75f, true){
            @Override
            protected boolean removeEldestEntry(Map.Entry<K, V> entry) {
                return size() > capacity;
            }
        };
    }

    public void put(K key, V value) {
        map.put(key,value);
    }

    public V get(K key,V defaultValue) {

        return map.getOrDefault(key, defaultValue);
    }


}