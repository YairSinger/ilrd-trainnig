package selfProjects.groceryPriceOptimizer.services;



import selfProjects.groceryPriceOptimizer.models.Item;
import selfProjects.groceryPriceOptimizer.models.ItemAggregator;
import selfProjects.groceryPriceOptimizer.models.PriceRecord;

import java.util.*;

public class ShoppingListService {
    private PriceDatabase priceDb;

    public ShoppingListService(PriceDatabase priceDb) {
        this.priceDb = priceDb;
    }

    public List<Map<String, PriceRecord>> calculateCheapestShoppingList(List<ItemAggregator> aggregators) {
        List<Map<String, PriceRecord>> shoppingList = new ArrayList<>();

        for (ItemAggregator aggregator : aggregators) {
            PriceRecord cheapest = null;

            for (Item item : aggregator.getItems()) {
                for (PriceRecord record : priceDb.getRecordsForItem(item)) {
                    if (cheapest == null || record.getPricePerUnit() < cheapest.getPricePerUnit()) {
                        cheapest = record;
                    }
                }
            }

            if (cheapest != null) {
                Map<String, PriceRecord> sellerEntry = new HashMap<>();
                sellerEntry.put(cheapest.getSeller(), cheapest);
                shoppingList.add(sellerEntry);
            }
        }

        return shoppingList;
    }
}
