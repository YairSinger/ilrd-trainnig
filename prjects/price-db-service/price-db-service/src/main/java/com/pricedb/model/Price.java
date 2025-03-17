package com.pricedb.model;

import jakarta.persistence.*;
import lombok.Data;
import java.time.LocalDateTime;

@Entity
@Table(name = "prices", 
       uniqueConstraints = @UniqueConstraint(columnNames = {"product_id", "store_id"}))
@Data
public class Price {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne
    @JoinColumn(name = "product_id", nullable = false)
    private Product product;

    @ManyToOne
    @JoinColumn(name = "store_id", nullable = false)
    private Store store;

    private Double pricePerItem;
    private LocalDateTime lastUpdated;
    private String updateSource;
}