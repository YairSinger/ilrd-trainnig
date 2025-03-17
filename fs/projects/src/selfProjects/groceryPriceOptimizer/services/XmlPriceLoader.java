package selfProjects.groceryPriceOptimizer.services;

import org.w3c.dom.*;
import javax.xml.parsers.*;
import javax.swing.*;
import java.io.File;
import java.sql.*;

public class XmlPriceLoader {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/SupermarketPrices";
    private static final String DB_USER = "prices_monitor_app";
    private static final String DB_PASSWORD = "Gigi2000#";

    public static void main(String[] args) {
        JFileChooser fileChooser = new JFileChooser();

        // Set the dialog title
        fileChooser.setDialogTitle("Select a File");
        String xmlFilePath = "";
        // Show the Open dialog
        int result = fileChooser.showOpenDialog(null);

        if (result == JFileChooser.APPROVE_OPTION) {
            // Get the selected file path as a string
            xmlFilePath = fileChooser.getSelectedFile().getAbsolutePath();
            System.out.println("Selected file path: " + xmlFilePath);
        } else {
            System.out.println("File selection canceled.");
        }
        
        XmlPriceLoader loader = new XmlPriceLoader();
        loader.loadXmlToDatabase(xmlFilePath);
    }

    public void loadXmlToDatabase(String xmlFilePath) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            connection.setAutoCommit(false);

            // Parse XML file
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse(new File(xmlFilePath));
            document.getDocumentElement().normalize();

            // Extract store information
            String storeId = document.getElementsByTagName("StoreId").item(0).getTextContent();

            // Insert store into the database
            insertStore(connection, storeId);

            // Process items
            NodeList itemList = document.getElementsByTagName("Item");
            for (int i = 0; i < itemList.getLength(); i++) {
                Element itemElement = (Element) itemList.item(i);
                loadItem(connection, storeId, itemElement);
            }

            connection.commit();
            System.out.println("Data loaded successfully!");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void insertStore(Connection connection, String storeId) throws SQLException {
        String query = "INSERT IGNORE INTO Stores (store_id) VALUES (?)";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setString(1, storeId);
            stmt.executeUpdate();
        }
    }

    private void loadItem(Connection connection, String storeId, Element itemElement) throws SQLException {
        // Extract item details
        String itemCode = itemElement.getElementsByTagName("ItemCode").item(0).getTextContent();
        String itemName = itemElement.getElementsByTagName("ItemName").item(0).getTextContent();
        String itemPrice = itemElement.getElementsByTagName("ItemPrice").item(0).getTextContent();
        String itemUnitQty = itemElement.getElementsByTagName("UnitQty").item(0).getTextContent();
        String itemQuantity = itemElement.getElementsByTagName("Quantity").item(0).getTextContent();
        String normalizedUnitQty = itemElement.getElementsByTagName("UnitOfMeasure").item(0).getTextContent();
        String normalizedPrice = itemElement.getElementsByTagName("UnitOfMeasurePrice").item(0).getTextContent();
        String manufacturerName = itemElement.getElementsByTagName("ManufacturerName").item(0).getTextContent();

        String priceUpdateDate = itemElement.getElementsByTagName("PriceUpdateDate").item(0).getTextContent();

        // Insert product into Products table
        insertProduct(connection, itemCode, itemName, itemUnitQty, itemQuantity, manufacturerName);

        // Insert price into Prices table
        insertPrice(connection, storeId, itemCode, itemPrice, priceUpdateDate, normalizedUnitQty, normalizedPrice);
    }

    private void insertProduct(Connection connection, String itemCode, String itemName, String itemUnitQty, String itemQuantity, String manufacturerName) throws SQLException {
        String query = "INSERT IGNORE INTO Products (product_id, product_name, quantity, UnitQty, manifactureName) VALUES (?, ?)";
        System.out.println("Executing query: " + query);
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            System.out.println("Parameter count: " + stmt.getParameterMetaData().getParameterCount());
            stmt.setString(1, itemCode);
            stmt.setString(2, itemName);
            stmt.setDouble(3, Double.parseDouble(itemQuantity));
            stmt.setString(4, itemUnitQty);
            stmt.setString(5, manufacturerName);
            stmt.executeUpdate();
        }
    }

    private void insertPrice(Connection connection, String storeId, String itemCode, String itemPrice, String priceUpdateDate, String normalizedUnitQty, String normalizedPrice) throws SQLException {
        String query = "INSERT INTO Prices (store_id, product_id, price, price_update_date,normalize_price_unit, normalized_price) " +
                "VALUES (?, ?, ?, ?) ON DUPLICATE KEY UPDATE price = ?, price_update_date = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setString(1, storeId);
            stmt.setString(2, itemCode);
            stmt.setDouble(3, Double.parseDouble(itemPrice));
            stmt.setString(4, priceUpdateDate);
            stmt.setString(5, normalizedUnitQty);
            stmt.setDouble(6, Double.parseDouble(normalizedPrice));
            stmt.executeUpdate();
        }
    }
}
