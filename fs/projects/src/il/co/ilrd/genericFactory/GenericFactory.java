//Project: GenericFactory
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Oron;
//Date: 14.02.2024
//Status: Approved

package il.co.ilrd.genericFactory;
import java.util.HashMap;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Objects;
import java.util.function.Function;

public class GenericFactory<K, T, D > {
    private final Map<K, Function<D, ? extends T>> creators = new HashMap<>();

    public void registerCreator(K key, Function<D, ? extends T> creator) {

        creators.put(key,Objects.requireNonNull(creator));
    }

    public T createObject(K key, D creatorParam) {
        Function<D, ? extends T> func = creators.get(key);
        if (func == null){
            throw new IllegalArgumentException("received func is null");
        }

        return func.apply(creatorParam);
    }

    public T createObject(K key) {
        return createObject(key,null);
    }
}