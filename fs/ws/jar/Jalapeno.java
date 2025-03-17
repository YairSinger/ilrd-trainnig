package quizes.pizzaDecorator;

public class Jalapeno extends PizzaTopping{

    public Jalapeno(Pizza basePizza) {
        this.basePizza = basePizza;
    }

    @Override
    public String getDescription() {
        return basePizza.getDescription() + " with Jalapeno";
    }

    @Override
    public int getPrice() {
        return basePizza.getPrice() + 4;
    }
}


