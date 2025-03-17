package com.pricedb.controller;

import com.pricedb.model.Price;
import com.pricedb.model.PriceUpdateRequest;
import com.pricedb.model.Product;
import com.pricedb.model.Store;
import com.pricedb.service.PriceService;
import lombok.RequiredArgsConstructor;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/v1/prices")
@RequiredArgsConstructor
public class PriceController {
    private final PriceService priceService;

    @GetMapping("/compare")
    public Map<String, List<Price>> comparePrices(
            @RequestParam String productId,
            @RequestParam(required = false) @DateTimeFormat(iso = DateTimeFormat.ISO.DATE_TIME) LocalDateTime date) {
        return priceService.comparePricesByStore(productId, date != null ? date : LocalDateTime.now());
    }

    @GetMapping("/search")
    public List<Product> searchProducts(
            @RequestParam String query,
            @RequestParam(defaultValue = "0") int page,
            @RequestParam(defaultValue = "20") int size) {
        return priceService.searchProducts(query, page, size);
    }


    @GetMapping("/lowest")
    public List<Price> getLowestPrices(
            @RequestParam(required = false) String category,
            @RequestParam(defaultValue = "10") int limit) {
        return priceService.findLowestPrices(category, limit);
    }
    
    @PostMapping("/prices/update")
    public ResponseEntity<Void> updatePrice(@RequestBody PriceUpdateRequest request) {
        priceService.updatePrice(
            request.getProductId(), 
            request.getStoreId(), 
            request.getPrice(),
            request.getUpdateSource()
        );
        return ResponseEntity.ok().build();
    }

    @PostMapping("/products")
    public ResponseEntity<Product> createProduct(@RequestBody Product product) {
        return ResponseEntity.ok(priceService.saveProduct(product));
    }

    @PostMapping("/stores") 
    public ResponseEntity<Store> createStore(@RequestBody Store store) {
        return ResponseEntity.ok(priceService.saveStore(store));
    }   
}