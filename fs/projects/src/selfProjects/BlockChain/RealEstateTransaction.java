package selfProjects.BlockChain;

public class RealEstateTransaction implements ITransaction{
   private String givver;
   private String reciver;

   private long price;

    public RealEstateTransaction(String reciver, String givver, long price) {
        this.reciver = reciver;
        this.givver = givver;
        this.price = price;
    }


    @Override
    public String getGivver() {
        return "";
    }

    @Override
    public String getReciver() {
        return "";
    }

    @Override
    public long getPrice() {
        return 0;
    }
}
