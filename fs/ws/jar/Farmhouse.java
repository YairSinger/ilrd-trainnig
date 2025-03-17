package quizes.pizzaDecorator;

public class Farmhouse implements Pizza{

    @Override
    public String getDescription() {
        return "Farmhouse pizza";
    }

    @Override
    public int getPrice() {
        return 11;
    }
}
