package quizes.pizzaDecorator;

public class Main {
    public static void main(String[] args) {
        Pizza myPizza = new PeppyPaneer();
        System.out.print("The price of " + myPizza.getDescription() + " is " + myPizza.getPrice());
        System.out.println("");
        myPizza = new Jalapeno(myPizza);
        System.out.print("The price of " + myPizza.getDescription() + " is " + myPizza.getPrice());
        System.out.println("");
        myPizza = new Jalapeno(myPizza);
        System.out.print("The price of " + myPizza.getDescription() + " is " + myPizza.getPrice());
        System.out.println("");
        myPizza = new BBQ(myPizza);
        System.out.print("The price of " + myPizza.getDescription() + " is " + myPizza.getPrice());
    }
}
