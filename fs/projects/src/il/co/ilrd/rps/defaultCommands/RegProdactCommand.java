package il.co.ilrd.rps.defaultCommands;

import il.co.ilrd.rps.ICommand;

public class RegProdactCommand implements ICommand {
    String productName;
        public RegProdactCommand(String productName) {
        this.productName = productName.toString();
    }

    @Override
    public void execute() {
        System.err.println("Registering Product :" + productName + " in database");
    }
}