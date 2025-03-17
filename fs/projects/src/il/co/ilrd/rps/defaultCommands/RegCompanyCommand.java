package il.co.ilrd.rps.defaultCommands;

import il.co.ilrd.rps.ICommand;

public class RegCompanyCommand implements ICommand {
    String companyName;

    public RegCompanyCommand(String companyName) {
        this.companyName = companyName.toString();
    }

    @Override
    public void execute() {
        System.err.println("Registering company :" + companyName + " in database");
    }

}
