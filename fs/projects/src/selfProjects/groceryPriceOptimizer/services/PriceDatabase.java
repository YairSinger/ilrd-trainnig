package selfProjects.groceryPriceOptimizer.services;

import selfProjects.groceryPriceOptimizer.models.Item;
import selfProjects.groceryPriceOptimizer.models.PriceRecord;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class PriceDatabase {

    public List<PriceRecord> getRecordsForItem(Item item) {
        List<PriceRecord> results = new ArrayList<>();

        String query = "SELECT item_name, seller, price, amount FROM prices WHERE item_name = ?";

        try (Connection conn = DBConnection.connect();
             PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, item.getName());
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                String itemName = rs.getString("item_name");
                String seller = rs.getString("seller");
                double price = rs.getDouble("price");
                double amount = rs.getDouble("amount");

                results.add(new PriceRecord(new Item(itemName), seller, price, amount));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return results;
    }

    public List<PriceRecord> getAllRecords() {
        List<PriceRecord> results = new ArrayList<>();

        String query = "SELECT item_name, seller, price, amount FROM prices";

        try (Connection conn = DBConnection.connect();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(query)) {

            while (rs.next()) {
                String itemName = rs.getString("item_name");
                String seller = rs.getString("seller");
                double price = rs.getDouble("price");
                double amount = rs.getDouble("amount");

                results.add(new PriceRecord(new Item(itemName), seller, price, amount));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return results;
    }
}

