package com.supermarket.api.service;

import com.supermarket.api.model.Price;
import com.supermarket.api.model.Product;
import com.supermarket.api.model.Store;
import com.supermarket.api.repository.PriceRepository;
import com.supermarket.api.repository.ProductRepository;
import com.supermarket.api.repository.StoreRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class SupermarketService {
    private final ProductRepository productRepository;
    private final StoreRepository storeRepository;
    private final PriceRepository priceRepository;

    @Autowired
    public SupermarketService(ProductRepository productRepository,
                              StoreRepository storeRepository,
                              PriceRepository priceRepository) {
        this.productRepository = productRepository;
        this.storeRepository = storeRepository;
        this.priceRepository = priceRepository;
    }

    public List<Product> getAllProducts() {
        return productRepository.findAll();
    }

    public Product getProduct(String id) {
        return productRepository.findById(id)
                .orElseThrow(() -> new ResourceNotFoundException("Product not found"));
    }

    public List<Store> getAllStores() {
        return storeRepository.findAll();
    }

    public List<Price> getPricesForProduct(String productId) {
        return priceRepository.findByProductId(productId);
    }

    public List<Price> getPricesForStore(String storeId) {
        return priceRepository.findByStoreId(storeId);
    }
}