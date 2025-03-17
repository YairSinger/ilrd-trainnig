//Project: SimpleRPS
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Alon;
//Date: 26.02.2024
//Status: Approved


package il.co.ilrd.rps;

import il.co.ilrd.Pair.Pair;
import il.co.ilrd.genericFactory.GenericFactory;
import il.co.ilrd.plugAndPlay.CommandPlugAndPlayFactory;
import il.co.ilrd.rps.defaultCommands.RegCompanyCommand;
import il.co.ilrd.rps.defaultCommands.RegIOTCommand;
import il.co.ilrd.rps.defaultCommands.RegProdactCommand;
import il.co.ilrd.rps.defaultCommands.UpdateIOTCommand;
import il.co.ilrd.threadPool.ThreadPool;

public class RPS {
    private final ThreadPool threadPool;
    private ParserILRD parser;
    private CommandPlugAndPlayFactory<String,String> plugAndPlayFactory;

    private GenericFactory<String, ICommand,String> commandFactory; //Requestkey,command,Requestdata

   // public RPS() {
   //    this(new DelimiterParser<String,String>());
   // }

    public RPS(ParserILRD parser) {
        this.parser = parser;
        threadPool = new ThreadPool();
        commandFactory = new GenericFactory<>();
        plugAndPlayFactory = new CommandPlugAndPlayFactory<>("/home/yair/git/prjects/plugAndPlayFolder", commandFactory);
    }

    public void handleRequest(String request){
        threadPool.submit(()-> { Pair<String,String> pair = parser.parse(request);
              ICommand command = commandFactory.createObject(pair.getKey(),pair.getValue());
              command.execute();return null;});

    }

    public class DelimiterParser<K,D> implements ParserILRD<K,D>{
        @Override
        public  Pair<K, D> parse(String request){ //Pair<requesrKey, requestVData>
          String [] splited = request.split("-");
          return new Pair<>((K)splited[0], (D)splited[1]);
        }

    }


}
