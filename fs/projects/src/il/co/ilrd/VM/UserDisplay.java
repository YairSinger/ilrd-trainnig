package il.co.ilrd.VM;

public class UserDisplay implements VMDisplay{
    @Override
    public void output(String msg){
        System.out.println(msg);
    }

}
