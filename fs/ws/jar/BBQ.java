package quizes.pizzaDecorator;

public class BBQ extends PizzaTopping{

    public BBQ(Pizza basePizza) {
        this.basePizza = basePizza;
    }

    @Override
    public String getDescription() {
        return basePizza.getDescription() + " with BBQ";
    }

    @Override
    public int getPrice() {
        return basePizza.getPrice() + 5;
    }
}
