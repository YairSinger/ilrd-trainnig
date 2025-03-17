package quizes.pizzaDecorator;

public class FreshTomato extends PizzaTopping{

    public FreshTomato(Pizza basePizza) {
        this.basePizza = basePizza;
    }

    public static void main(String[] args) {
        System.out.println("wrong main!");
    }

    @Override
    public String getDescription() {
        return basePizza.getDescription() + "with Fresh Tomato";
    }

    @Override
    public int getPrice() {
        return basePizza.getPrice() + 1;
    }
}
