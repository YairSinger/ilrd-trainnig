//Project:HashMap
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Yaara
//Date: 29.01.2024
//status: Approved

        package il.co.ilrd.hashMap;
import il.co.ilrd.Pair.Pair;

import java.util.*;

public class HashMapILRD<K, V> implements Map<K, V> {

    private static final int DEFAULT_CAPACITY = 16;
    private static final float DEFAULT_LOAD_FACTOR = 0.75f; // Advanced
    private final List<List<Map.Entry<K, V>>> hashMap;
    private float loadFactor = DEFAULT_LOAD_FACTOR;
    private int capacity;
    private int modCount;
    private int size;

    private Set<K> keySet = null;

    private Collection<V> values = null;

    private Set<Entry<K, V>> entrySet = null;

    public HashMapILRD() {
        this(DEFAULT_CAPACITY);
    }
    private void initHash(){
        for (int i = 0; i < capacity; i++) {
            hashMap.add(new LinkedList<>());
        }
    }

    public HashMapILRD(int capacity) {
        if (capacity < 1){
            throw new IllegalArgumentException("invalid capacity" + capacity);
        }
        this.capacity = capacity;
        hashMap = new ArrayList<>(capacity);
        initHash();
    }

    private int bucketIndex(Object key){
        return ((Math.abs(Objects.hashCode(key))) % capacity);
    }
    private Map.Entry<K,V> findPair(K key){
        for (Entry<K, V> kvPair : hashMap.get(bucketIndex(key))) {
            if (Objects.equals(kvPair.getKey(),key)) {
               return kvPair;
            }
        }
        return null;
    }
//    public HashMapILRD(int capacity, float loadFactor) {// Advanced
//    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    @SuppressWarnings("unchecked")
    public boolean equals(Object o){
        if (!(o instanceof HashMapILRD)){
            return false;
        }
        Set<Map.Entry<K,V>> entrySet = entrySet();
        V value;

        for (Entry<K, V> kvEntry : entrySet) {
            value = ((HashMapILRD<K,V>)o).get(kvEntry.getKey());
            if (!Objects.equals(value, kvEntry.getValue())){
                return false;
            }
        }
        return ((HashMapILRD<K,V>)o).size() == size;
    }

    @Override
    public int hashCode(){
        int hash = 0;
        for (Entry<K,V> kvEntry : entrySet()) {
            hash += Objects.hashCode(kvEntry);

        }
        return hash;
    }

    @Override

    public boolean containsKey(Object key) {
       return findPair((K)key) == null ? false : true;
    }

    @Override
    public boolean containsValue(Object value) {

        for (V v : this.values()) {
            if(Objects.equals(value, v)){
                return true;
            }
        }
        return false;
    }

    @Override

    public V get(Object key) {
       Entry<K,V> found = findPair((K)key);
       return found == null ? null : found.getValue();

    }

    @Override
    public V put(K key, V value) {
        ++modCount;

        Entry<K,V> kvPair = findPair(key);
        V oldValue = null;

        if( kvPair!= null){
            oldValue = kvPair.getValue();
            kvPair.setValue(value);
        }else {
            hashMap.get(bucketIndex(key)).add(Pair.of(key, value));
            ++size;
        }

        return oldValue;
    }

    @Override
    public V remove(Object key) {
        ++modCount;
        --size;
        V oldValue = null;

        Map.Entry<K,V> kvPair = findPair((K)key);
        if( kvPair!= null){
            oldValue = kvPair.getValue();
            hashMap.get(bucketIndex(key)).remove(kvPair);
        }
        return oldValue;
    }

    @Override
    public void putAll(Map<? extends K, ? extends V> map) {
        for (Entry<? extends K, ? extends V> entry : map.entrySet()) {
            this.put(entry.getKey(),entry.getValue());
        }
    }

    @Override
    public void clear() {
        ++modCount;
        for (List<Entry<K, V>> pairs : hashMap) {
            size -= pairs.size();
            pairs.clear();

        }
    }

    @Override
    public Set<K> keySet() {
        if (keySet == null){
            keySet = new KeySet();
        }
        return keySet;
    }

    @Override
    public Collection<V> values() {
        if (values == null){
            values = new ValuesCollection();
        }
        return values ;
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        if (entrySet == null){
            entrySet = new EntrySet();
        }
        return entrySet;
    }

    class KeySet extends AbstractSet<K> {

        @Override
        public Iterator<K> iterator() {

            return new KeySetIterator();
        }

        @Override
        public int size() {
            return size;
        }

        class KeySetIterator implements Iterator<K> {
            private  final Iterator<Entry<K,V>> iterator = new EntrySet().iterator();
            @Override
            public boolean hasNext() {
                return iterator.hasNext();
            }

            @Override
            public K next() {

                return iterator.next().getKey();
            }
        }
    }

    class ValuesCollection extends AbstractCollection<V> {

        @Override
        public Iterator<V> iterator() {
            return new ValueCollectionIterator();
        }

        @Override
        public int size() {
            return  size;
        }

        class ValueCollectionIterator implements Iterator<V> {
            private final Iterator<Entry<K,V>> iterator = new EntrySet().iterator();

            @Override
            public boolean hasNext() {
                return iterator.hasNext();
            }

            @Override
            public V next() {
                return iterator.next().getValue();
            }
        }
    }




        public class EntrySet extends AbstractSet<Entry<K, V>> {

            @Override
            public Iterator<Entry<K, V>> iterator() {
                return new EntrySetIterator();
            }

            @Override
            public int size() {
                return size;
            }

            private class EntrySetIterator implements Iterator<Entry<K, V>> {
                private final Iterator<List<Entry<K, V>>> arrayListIterator = hashMap.iterator();
                private Iterator<Entry<K, V>> entryIterator = arrayListIterator.next().iterator();
                private  final int expectedModCount = modCount;

                private EntrySetIterator() {
                    nextPair();
                }

                @Override
                public boolean hasNext() {
                    return entryIterator.hasNext();
                }

                @Override
                public Entry<K, V> next() {
                    if (modCount != expectedModCount) {
                        throw new ConcurrentModificationException();
                    }
                    Map.Entry<K, V> currPair = entryIterator.next();
                    nextPair();
                    return currPair;
                }

                private void nextPair() {
                    while (!entryIterator.hasNext() && arrayListIterator.hasNext()) {
                        entryIterator = arrayListIterator.next().iterator();
                    }
                }

            }
        }
    }















