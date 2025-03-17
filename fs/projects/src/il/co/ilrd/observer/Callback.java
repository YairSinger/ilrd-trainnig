//Project: Observer
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Tal
//Date: 02.2024
//status: Approved
package il.co.ilrd.observer;

import java.util.Objects;
import java.util.function.Function;

public class Callback<T> {

    private final Function<T,Void> update;
    private final Function<Void, Void> stopUpdate;
    private Dispatcher<T> dispatcher;

    public Callback(Function<T, Void> update, Function<Void, Void> stopUpdate){
        this.update = Objects.requireNonNull(update);
        this.stopUpdate = Objects.requireNonNull(stopUpdate);
    }
    void update(T msg){
        this.update.apply(msg);
    }
    void stopUpdate(){
        this.stopUpdate.apply(null);
    }
    public void unsubscribe(){
        if(dispatcher != null){
            dispatcher.unsubscribe(this);
        }
    }
    void setDispatcher(Dispatcher<T> dispatcher){
        this.dispatcher = dispatcher;
    }

}