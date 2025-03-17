package il.co.ilrd.rps;

/**
 * @Purpose enable to instantiate an implementation of ICommand via cmdFactory
 */
public interface CmdCreator<K,D> {

    ICommand createCommand(D msg);
    K getKey();
}
