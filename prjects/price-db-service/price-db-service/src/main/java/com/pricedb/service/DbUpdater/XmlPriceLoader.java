package com.pricedb.service.DbUpdater;

import org.springframework.stereotype.Component;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.nio.file.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.concurrent.TimeUnit;

@Component
public class XmlPriceLoader {
    private static final long MAX_WAIT_TIME = 2 * 60 * 1000; // 2 minutes in milliseconds
    private long lastLoadTime = System.currentTimeMillis(); // Track the last file load time

    private static final String DB_URL = "jdbc:mysql://localhost:3306/SupermarketPrices";
    private static final String DB_USER = "prices_monitor_app";
    private static final String DB_PASSWORD = "Gigi2000#";

   

    public void monitorAndProcess(String folderPath) throws IOException {
        Path directoryPath = Paths.get(folderPath);
        WatchService watchService = FileSystems.getDefault().newWatchService();

        // Register the directory with WatchService
        directoryPath.register(watchService, StandardWatchEventKinds.ENTRY_CREATE);

        System.out.println("Watching directory: " + folderPath);

        while (true) {
            WatchKey key;
            try {
                key = watchService.poll(10, TimeUnit.SECONDS); // Poll with a timeout of 10 seconds
            } catch (InterruptedException e) {
                System.err.println("Interrupted while waiting for new files.");
                break;
            }

            if (key == null) {
                // If no events, check if we should exit due to max wait time
                if (System.currentTimeMillis() - lastLoadTime >= MAX_WAIT_TIME) {
                    System.out.println("Exiting as maximum wait time elapsed.");
                    break;
                }
                continue; // No events, so keep waiting
            }

            boolean fileProcessed = false; // Flag to check if any file was processed


            for (WatchEvent<?> event : key.pollEvents()) {
                WatchEvent.Kind<?> kind = event.kind();

                if (kind == StandardWatchEventKinds.ENTRY_CREATE) {
                    Path filePath = directoryPath.resolve((Path) event.context());

                    // Process only .xml files
                    if (filePath.toString().endsWith(".xml")) {
                        System.out.println("New XML file detected: " + filePath);
                        try {
                            loadXmlToDatabase(filePath.toString());
                        } catch (Exception e) {
                            System.err.println("Error processing file " + filePath + ": " + e.getMessage());
                        }
                    }
                }
            }

            // If no file was processed and maximum wait time has elapsed, exit the loop
            if (!fileProcessed && System.currentTimeMillis() - lastLoadTime >= MAX_WAIT_TIME) {
                System.out.println("Exiting as maximum wait time elapsed since last load.");
                break;
            }

            boolean valid = key.reset();
            if (!valid) {
                System.out.println("WatchKey no longer valid. Exiting...");
                break;
            }
        }

        watchService.close();
    }

    public void loadXmlToDatabase(String xmlFilePath) throws ParserConfigurationException, IOException, SAXException {
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
            System.out.println("Data loaded successfully for file: " + xmlFilePath);

            // Delete the XML file after successful commit
            Path path = Paths.get(xmlFilePath);
            try {
                Files.delete(path);
                System.out.println("XML file deleted successfully: " + xmlFilePath);
            } catch (Exception e) {
                System.err.println("Failed to delete the file: " + e.getMessage());
            }
        } catch (Exception e) {
            System.err.println("Error loading XML file: " + e.getMessage());
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
        String query1 = "INSERT IGNORE INTO Products (product_id, product_name, quantity, UnitQty, manifactureName) VALUES (?, ?, ?, ?, ?)";

        try (PreparedStatement stmt = connection.prepareStatement(query1)) {

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
                "VALUES (?, ?, ?, ?, ?, ?) ON DUPLICATE KEY UPDATE price = ?, price_update_date = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setString(1, storeId);
            stmt.setString(2, itemCode);
            stmt.setDouble(3, Double.parseDouble(itemPrice));
            stmt.setString(4, priceUpdateDate);
            stmt.setString(5, normalizedUnitQty);
            stmt.setDouble(6, Double.parseDouble(normalizedPrice));

            stmt.setDouble(7, Double.parseDouble(itemPrice));         // price
            stmt.setString(8, priceUpdateDate);                      // price_update_date

            stmt.executeUpdate();
        }
    }
}