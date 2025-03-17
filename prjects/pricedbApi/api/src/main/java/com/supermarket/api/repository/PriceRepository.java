package com.supermarket.api.repository;


import com.supermarket.api.model.Price;
import com.supermarket.api.model.Product;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;


public interface PriceRepository extends JpaRepository<Price, Long> {
    List<Price> findByProductId(String productId);
    List<Price> findByStoreId(String storeId);
}