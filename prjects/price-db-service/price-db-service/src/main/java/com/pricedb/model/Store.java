package com.pricedb.model;


import jakarta.persistence.*;
import lombok.Data;
import java.time.LocalDateTime;

@Entity
@Table(name = "stores")
@Data
public class Store {
    @Id
    private String id;
    
    private String storeName;
    private String chainName;
    private String address;
    private LocalDateTime lastUpdated;
    private String updateSource;
}