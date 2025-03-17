package il.co.ilrd.rps.defaultCommands;

import il.co.ilrd.rps.ICommand;

public class UpdateIOTCommand implements ICommand {
    String [] update;

    public UpdateIOTCommand(String update) {

        this.update = update.toString().split("@");
    }

    @Override
    public void execute() {
        System.err.println("update device S.N :" + update[0] + " content: " + update[1]);
    }

}
