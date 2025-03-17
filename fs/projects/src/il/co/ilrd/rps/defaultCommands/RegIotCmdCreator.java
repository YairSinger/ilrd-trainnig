package il.co.ilrd.rps.defaultCommands;

import il.co.ilrd.rps.CmdCreator;
import il.co.ilrd.rps.ICommand;

public class RegIotCmdCreator<K,D> implements CmdCreator<K,D> {
    @Override
    public ICommand createCommand(D msg) {
        return new RegIOTCommand((String)msg);
    }

    @Override
    public K getKey() {
        return (K)RegIOTCommand.class.getName();
    }
}


