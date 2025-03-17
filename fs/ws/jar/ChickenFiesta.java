package quizes.pizzaDecorator;

public class ChickenFiesta implements Pizza{

    @Override
    public String getDescription() {
        return "Chicken Fiesta pizza";
    }

    @Override
    public int getPrice() {
        return 13;
    }
}
