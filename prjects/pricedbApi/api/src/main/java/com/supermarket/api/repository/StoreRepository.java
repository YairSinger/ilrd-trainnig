package com.supermarket.api.repository;

import com.supermarket.api.model.Product;
import com.supermarket.api.model.Store;
import org.springframework.data.jpa.repository.JpaRepository;



public interface StoreRepository extends JpaRepository<Store, String> {
}