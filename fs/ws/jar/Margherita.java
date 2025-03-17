package quizes.pizzaDecorator;

public class Margherita implements Pizza{

    @Override
    public String getDescription() {
        return "Margherita pizza";
    }

    @Override
    public int getPrice() {
        return 12;
    }
}
