//Project: Pair
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Isreal Weiss
//Date: 18.01.2024
//Status: Pre-reviewed


package il.co.ilrd.Pair;

import java.util.*;

public class Pair<K, V> implements Map.Entry<K,V> {
        private K key;
        private V value;

        public Pair(K key, V value){
            this.key = key;
            this.value = value;
        }

        //private static Pair<T,T> minMaxInternal()
        public static <K, V> Pair<K, V> of(K key , V value){
            return new Pair<>(key , value);
        }

        public static <K, V> Pair<V, K> swap(Pair<K, V> pair){
            return new Pair<V,K>(pair.value, pair.key);
        }

        @Override
        public K getKey(){
            return this.key;
        }

        public void setKey(K newKey){
            this.key = newKey;
        }

        @Override
        public V getValue(){
            return this.value;
        }

        @Override
        public V setValue(V newValue){
            V old = this.value;
            this.value = newValue;
            return old;
        }

        @Override
        public int hashCode(){
           return Objects.hash(this.key, this.value);
        }

        @Override
        public boolean equals(Object o) {
            if (o == null || !(o instanceof Pair)) {
                return false;
            } else {
                return Objects.equals(this.key, ((Pair<K, V>) o).key) && Objects.equals(this.value, ((Pair<K, V>) o).value);
            }
        }

        @Override
        public String toString(){
            return "[" + key.toString() + ", " + value.toString() + "]";
        }

        public static <T extends Comparable<T>> Pair<T, T> minMax(T[] array){
           return minMax(array,Comparator.naturalOrder());
        }

        public static <T> Pair<T, T> minMax(T[] array, Comparator<? super T> comparator){
            Pair <T,T> minMax = new Pair<>(null,null);
            int i = 0;
            int len = array.length;

            if (len % 2 == 0){
                if (comparator.compare(array[0],array[1]) < 0){
                    minMax.key = array[0];//min
                    minMax.value = array[1]; //max
                }else{
                    minMax.key = array[1];//min
                    minMax.value = array[0]; //max
                }
                i = 2;
            }else{
                minMax.key = array[0];//min
                minMax.value = array[0]; //max
                i = 1;
            }
            for(;i < len - 1; i += 2){
                if (comparator.compare(array[i],array[i+1]) > 0){
                    if (comparator.compare(array[i],minMax.value) > 0){
                        minMax.value = array[i];
                    }
                    if (comparator.compare(array[i + 1],minMax.key) > 0){
                        minMax.key = array[i + 1];
                    }
                }else{
                    if (comparator.compare(array[i + 1],minMax.value) > 0){
                        minMax.value = array[i + 1];
                    }
                    if (comparator.compare(array[i],minMax.key) > 0){
                        minMax.key = array[i];
                    }
                }
            }
            return minMax;
        }
   }

