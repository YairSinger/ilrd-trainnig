package il.co.ilrd.rps.defaultCommands;

import il.co.ilrd.rps.CmdCreator;
import il.co.ilrd.rps.ICommand;

public class UpdateIotCmdCreator<K,D> implements CmdCreator<K,D> {
    @Override
    public ICommand createCommand(D msg) {
        return new UpdateIOTCommand((String)msg);
    }

    @Override
    public K getKey() {
        return (K)UpdateIOTCommand.class.getName();
    }
}
