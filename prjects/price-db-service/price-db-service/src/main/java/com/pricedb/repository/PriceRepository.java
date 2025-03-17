package com.pricedb.repository;

import com.pricedb.model.Price;
import com.pricedb.model.Product;
import com.pricedb.model.Store;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.domain.Pageable;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Optional;

public interface PriceRepository extends JpaRepository<Price, Long> {
    Optional<Price> findByProductAndStore(Product product, Store store);
    List<Price> findByLastUpdatedBefore(LocalDateTime date);
      List<Price> findByProduct_ProductIdAndLastUpdatedBeforeOrderByLastUpdatedDesc(
        String productId, LocalDateTime date);

    @Query("SELECT p FROM Price p WHERE p.product.category = :category ORDER BY p.pricePerItem ASC")
    List<Price> findTopNLowestPricesByCategory(String category, Pageable pageable);

    @Query("SELECT p FROM Price p ORDER BY p.pricePerItem ASC")
    List<Price> findTopNLowestPrices(Pageable pageable);
}