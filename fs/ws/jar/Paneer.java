package quizes.pizzaDecorator;

public class


Paneer extends PizzaTopping{

    public Paneer(Pizza basePizza) {
        this.basePizza = basePizza;
    }

    @Override
    public String getDescription() {
        return basePizza.getDescription() + "with Paneer";
    }

    @Override
    public int getPrice() {
        return basePizza.getPrice() + 2;
    }
}
