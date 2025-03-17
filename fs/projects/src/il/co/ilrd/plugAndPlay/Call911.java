package il.co.ilrd.plugAndPlay;
import il.co.ilrd.rps.ICommand;

public  class Call911 implements ICommand {
        private final String msg;
        public Call911(String  msg) {
            this.msg = msg;
        }
        @Override
        public void execute() {
            System.out.println("Call911 is executed with msg: " + msg);
        }
}
