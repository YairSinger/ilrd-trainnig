package com.supermarket.api.model;

import jakarta.persistence.*;



@Entity
@Table(name = "Stores")
public class Store {
    @Id
    private String storeId;

    // Getters and setters
}