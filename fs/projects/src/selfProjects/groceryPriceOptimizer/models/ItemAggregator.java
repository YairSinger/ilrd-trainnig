package selfProjects.groceryPriceOptimizer.models;

import java.util.ArrayList;
import java.util.List;

public class ItemAggregator {
    private List<Item> items;

    public ItemAggregator() {
        this.items = new ArrayList<>();
    }

    public void addItem(Item item) {
        if (!items.contains(item)) {
            items.add(item);
        }
    }

    public List<Item> getItems() {
        return items;
    }

    @Override
    public String toString() {
        return "Aggregator: " + items.toString();
    }
}