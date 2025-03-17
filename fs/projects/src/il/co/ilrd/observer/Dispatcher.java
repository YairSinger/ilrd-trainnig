//Project: Observer
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Tal
//Date: 02.2024
//status: Approved


package il.co.ilrd.observer;

import java.util.*;

public class Dispatcher<T> {
    private final List<Callback<T>> subscribersCallbacks = new ArrayList<>();


    public void subscribe(Callback<T> callback){
        callback.setDispatcher(this);
        if(subscribersCallbacks.contains(callback)){
            throw new RuntimeException("callback already subscribed to dispatcher");
        }
        subscribersCallbacks.add(Objects.requireNonNull(callback));
    }
    public void unsubscribe(Callback<T> callback){
        subscribersCallbacks.remove(Objects.requireNonNull(callback));
        callback.setDispatcher(null);
    }
    public void updateAll(T msg){
        for(int i = 0; i < subscribersCallbacks.size(); i++){
            try{
                subscribersCallbacks.get(i).update(msg);
            }catch (Exception ignore){}
        }

    }
    public void stopService(){
        for (Callback<T> subscriber : subscribersCallbacks) {
            subscriber.stopUpdate();
        }

    }

}