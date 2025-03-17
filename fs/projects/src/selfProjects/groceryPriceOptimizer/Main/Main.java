package selfProjects.groceryPriceOptimizer.Main;



import selfProjects.groceryPriceOptimizer.models.*;
import selfProjects.groceryPriceOptimizer.services.PriceDatabase;
import selfProjects.groceryPriceOptimizer.services.ShoppingListService;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        // Initialize Price Database
        PriceDatabase priceDb = new PriceDatabase();

        // Fetch items from the database
        Item apple = new Item("Apple");
        Item organicApple = new Item("Organic Apple");

        // Create Item Aggregators
        ItemAggregator appleAggregator = new ItemAggregator();
        appleAggregator.addItem(apple);
        appleAggregator.addItem(organicApple);

        List<ItemAggregator> aggregators = new ArrayList<>();
        aggregators.add(appleAggregator);

        // Generate Shopping List
        ShoppingListService shoppingService = new ShoppingListService(priceDb);
        List<Map<String, PriceRecord>> shoppingList = shoppingService.calculateCheapestShoppingList(aggregators);

        // Print the result
        System.out.println("Cheapest Shopping List:");
        for (Map<String, PriceRecord> sellerEntry : shoppingList) {
            sellerEntry.forEach((seller, record) -> {
                System.out.println(seller + ": " + record);
            });
        }
    }
}