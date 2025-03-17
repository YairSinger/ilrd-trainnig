//package quizes.singletonFactory;
//import il.co.ilrd.genericFactory.GenericFactory;
//
//import java.util.HashMap;
//import java.util.Map;
//import java.util.function.Function;
//
//public class SingletonFactory<K,D,T> {
//    private GenericFactory<K,D,T> factory =  new GenericFactory<>();
//    private SingletonFactory(){}
//
//    private static class IdiomInner{
//
//
//        private void add( Function<?,?> recipe){
//           synchronized (SingletonFactory.class){
//               fac
//           }
//        }
//    }
//
//    public static<K,D,T> SingletonFactory<K,D,T> getInstance(){
//        return (SingletonFactory<K, D, T>) IdiomInner.instance;
//    }
//
//    public void add(K key, Function<D,T> recipe){
//        synchronized (SingletonFactory.class){
//            IdiomInner.instance.map.put(key,recipe))
//        }
//    }
//}
