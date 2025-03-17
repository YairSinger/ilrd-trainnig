package com.supermarket.api.repository;

import com.supermarket.api.model.Product;
import org.springframework.data.jpa.repository.JpaRepository;

public interface ProductRepository extends JpaRepository<Product, String> {
    // Custom queries if needed
}

