package com.pricedb.model;

import jakarta.persistence.*;
import lombok.Data;
import java.time.LocalDateTime;

@Entity
@Table(name = "products")
@Data
public class Product {
    @Id
    private String id;
    
    private String name;
    private String manufacturer;
    private Double amountPerItem;
    private String amountUnit;
    private LocalDateTime lastUpdated;
    private String updateSource;
}