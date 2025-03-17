package com.pricedb.repository;

import com.pricedb.model.Product;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.domain.Pageable;

import java.time.LocalDateTime;
import java.util.List;

public interface ProductRepository extends JpaRepository<Product, String> {
    List<Product> findByLastUpdatedBefore(LocalDateTime date);

     @Query("SELECT p FROM Product p WHERE LOWER(p.name) LIKE LOWER(CONCAT('%', :query, '%'))")
    List<Product> findByProductNameContainingIgnoreCase(String query, Pageable pageable);
}