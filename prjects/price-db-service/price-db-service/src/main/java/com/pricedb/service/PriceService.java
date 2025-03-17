package com.pricedb.service;

import com.pricedb.model.Price;
import com.pricedb.model.Product;
import com.pricedb.model.Store;
import com.pricedb.repository.PriceRepository;
import com.pricedb.repository.ProductRepository;
import com.pricedb.repository.StoreRepository;
import lombok.RequiredArgsConstructor;

import org.springframework.data.domain.PageRequest;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class PriceService {
    private final ProductRepository productRepository;
    private final StoreRepository storeRepository;
    private final PriceRepository priceRepository;

    @Transactional
    public void updatePrice(String productId, String storeId, Double pricePerItem, String updateSource) {
        Product product = productRepository.findById(productId)
                .orElseThrow(() -> new RuntimeException("Product not found"));
        Store store = storeRepository.findById(storeId)
                .orElseThrow(() -> new RuntimeException("Store not found"));

        Price price = priceRepository.findByProductAndStore(product, store)
                .orElse(new Price());

        price.setProduct(product);
        price.setStore(store);
        price.setPricePerItem(pricePerItem);
        price.setLastUpdated(LocalDateTime.now());
        price.setUpdateSource(updateSource);

        priceRepository.save(price);
    }
    public Store saveStore(Store store) {
       return storeRepository.save(store);
    }

    @Transactional
    public void cleanupOldEntries(LocalDateTime beforeDate) {
        List<Price> oldPrices = priceRepository.findByLastUpdatedBefore(beforeDate);
        priceRepository.deleteAll(oldPrices);
    }

    public List<Price> getAllPrices() {
        return priceRepository.findAll();
    }
    public Product saveProduct(Product product) {
        return productRepository.save(product);
    }
    public void savePrice(Price price) {
        priceRepository.save(price);
    }

    public Map<String, List<Price>> comparePricesByStore(String productId, LocalDateTime date) {
        List<Price> prices = priceRepository.findByProduct_ProductIdAndLastUpdatedBeforeOrderByLastUpdatedDesc(
            productId, date);
        return prices.stream()
            .collect(Collectors.groupingBy(price -> price.getStore().getId()));
    }

    public List<Product> searchProducts(String query, int page, int size) {
        return productRepository.findByProductNameContainingIgnoreCase(
            query, PageRequest.of(page, size));
    }

    public List<Price> findLowestPrices(String category, int limit) {
        if (category != null) {
            return priceRepository.findTopNLowestPricesByCategory(category, PageRequest.of(0, limit));
        }
        return priceRepository.findTopNLowestPrices(PageRequest.of(0, limit));
    }
}