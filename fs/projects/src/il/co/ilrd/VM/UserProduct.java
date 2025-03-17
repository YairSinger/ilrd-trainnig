package il.co.ilrd.VM;

public class UserProduct implements ProductProtoTypes{
    private double price;
    private String name;

    public UserProduct(String name, double price){
        this.name = name;
        this.price = price;
    }
    @Override
    public double getPrice(){
        return price;
    }
    @Override
    public String getName(){
        return name;
    }
}
