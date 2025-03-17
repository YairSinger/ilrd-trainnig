package il.co.ilrd.rps.defaultCommands;

import il.co.ilrd.rps.CmdCreator;
import il.co.ilrd.rps.ICommand;

public class RegPrdCmdCreator<K,D> implements CmdCreator<K,D> {
    @Override
    public ICommand createCommand(D msg) {
        return new RegProdactCommand((String) msg);
    }

    @Override
    public K getKey() {
        return (K) RegProdactCommand.class.getName();
    }
}

