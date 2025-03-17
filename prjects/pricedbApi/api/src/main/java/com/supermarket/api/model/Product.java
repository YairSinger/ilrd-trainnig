package com.supermarket.api.model;
import jakarta.persistence.*;


@Entity
@Table(name = "Products")
public class Product {
    @Id
    private String productId;
    private String productName;
    private Double quantity;
    private String unitQty;
    private String manifactureName;

    // Getters and setters
}