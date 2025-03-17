package quizes.pizzaDecorator;

public class Capsicum extends PizzaTopping{

    public Capsicum(Pizza basePizza) {
        this.basePizza = basePizza;
    }

    @Override
    public String getDescription() {
        return basePizza.getDescription() + " with Capsicum";
    }

    @Override
    public int getPrice() {
        return basePizza.getPrice() + 3;
    }
}
