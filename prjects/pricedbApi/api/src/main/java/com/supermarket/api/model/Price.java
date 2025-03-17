package com.supermarket.api.model;

import jakarta.persistence.*;


@Entity
@Table(name = "Prices")
public class Price {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String storeId;
    private String productId;
    private Double price;
    private String priceUpdateDate;
    private String normalizePriceUnit;
    private Double normalizedPrice;

    // Getters and setters
}