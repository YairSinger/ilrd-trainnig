package il.co.ilrd.plugAndPlay;

import il.co.ilrd.genericFactory.GenericFactory;
import il.co.ilrd.rps.ICommand;
import org.junit.Test;

public class PlugAndPlayTest {
    @Test
    public void base() throws InterruptedException {
        GenericFactory<String, ICommand,String> factory = new GenericFactory<>();
        CommandPlugAndPlayFactory plugAndPlay = new CommandPlugAndPlayFactory("/home/yair/git/prjects/plugAndPlayFolder/userCommands",factory);
        ICommand command = factory.createObject("il.co.ilrd.rps.defaultCommands.RegIOTCommand" , "abc123");
        ICommand command2 = factory.createObject("il.co.ilrd.rps.defaultCommands.RegProdactCommand", "abc");
        ICommand command3 = factory.createObject("il.co.ilrd.rps.defaultCommands.RegProdactCommand","Tadiran ZZZ model");
        ICommand command4 = factory.createObject("il.co.ilrd.rps.defaultCommands.UpdateIOTCommand","abc123 @working ");
       command.execute();
       command2.execute();
       command3.execute();
       command4.execute();
//       ICommand call911 = factory.createObject("il.co.ilrd.plugAndPlay.Call911", "help me! I'm lost!!!");
//       call911.execute();
       System.out.println("add jar file to userCommands folder");
       Thread.sleep(10000);
        ICommand call911 = factory.createObject("il.co.ilrd.plugAndPlay.Call911", "help me! I'm lost!!!");
        call911.execute();





    }

}