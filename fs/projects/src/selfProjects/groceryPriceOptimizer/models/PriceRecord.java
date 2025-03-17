package selfProjects.groceryPriceOptimizer.models;

public class PriceRecord {
    private Item item;
    private String seller;
    private double price;
    private double amount; // Amount in mass or quantity

    public PriceRecord(Item item, String seller, double price, double amount) {
        this.item = item;
        this.seller = seller;
        this.price = price;
        this.amount = amount;
    }

    public Item getItem() {
        return item;
    }

    public String getSeller() {
        return seller;
    }

    public double getPrice() {
        return price;
    }

    public double getAmount() {
        return amount;
    }

    public double getPricePerUnit() {
        return price / amount;
    }

    @Override
    public String toString() {
        return String.format("Item: %s, Seller: %s, Price: %.2f, Amount: %.2f, Price/Unit: %.2f",
                item, seller, price, amount, getPricePerUnit());
    }
}
