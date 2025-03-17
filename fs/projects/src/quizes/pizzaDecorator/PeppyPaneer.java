package quizes.pizzaDecorator;

public class PeppyPaneer implements Pizza{

    @Override
    public String getDescription() {
        return "Peppy Paneer pizza";
    }

    @Override
    public int getPrice() {
        return 10;
    }
}
