//package il.co.ilrd.observer;
//
//import java.lang.ref.WeakReference;
//import java.util.HashSet;
//import java.util.Set;
//
//class DispatcherWeak<T> {
//    private Set<Callback<T>> subscribersCallbacks = new HashSet<>();
//
//
//    public void subscribe(Callback<T> callback){
//        callback.setDispatcher(this);
//        WeakReference<Callback<T>> reference = new WeakReference<>(callback);
//        subscribersCallbacks.add(reference);
//    }
//    public void unsubscribe(Callback<T> callback){
//        WeakReference<Callback<T>> reference = new WeakReference<>(callback);
//        subscribersCallbacks.remove(reference);
//    }
//    public void updateAll(T msg){
//        for (WeakReference<Callback<T>> subscriber : subscribersCallbacks) {
//            subscriber.get().update(msg);
//        }
//    }
//    public void stopService(){
//        for (WeakReference<Callback<T>> subscriber : subscribersCallbacks) {
//            subscriber.get().stopUpdate();
//        }
//
//    }
//
//}