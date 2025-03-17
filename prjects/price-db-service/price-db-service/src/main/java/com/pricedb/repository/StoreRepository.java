package com.pricedb.repository;

import com.pricedb.model.Store;
import org.springframework.data.jpa.repository.JpaRepository;
import java.time.LocalDateTime;
import java.util.List;

public interface StoreRepository extends JpaRepository<Store, String> {
    List<Store> findByLastUpdatedBefore(LocalDateTime date);
}