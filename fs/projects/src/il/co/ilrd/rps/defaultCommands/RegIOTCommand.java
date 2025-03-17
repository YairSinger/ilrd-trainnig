package il.co.ilrd.rps.defaultCommands;

import il.co.ilrd.rps.ICommand;

public class RegIOTCommand implements ICommand {
        String IOT;

        public RegIOTCommand(String IOT) {
            this.IOT = IOT.toString();
        }
        @Override
        public void execute() {
            System.err.println("Registering device S.N :" + IOT + " in database");
        }
    }
