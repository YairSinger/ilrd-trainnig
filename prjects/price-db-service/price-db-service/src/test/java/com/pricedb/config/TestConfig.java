package com.pricedb.config;

import com.pricedb.repository.PriceRepository;
import com.pricedb.repository.ProductRepository;
import com.pricedb.repository.StoreRepository;
import org.springframework.boot.test.context.TestConfiguration;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Primary;
import org.springframework.context.annotation.Profile;

import static org.mockito.Mockito.mock;

@TestConfiguration
@Profile("test")
public class TestConfig {

    @Bean
    @Primary
    public PriceRepository priceRepository() {
        return mock(PriceRepository.class);
    }
    
    @Bean
    @Primary
    public ProductRepository productRepository() {
        return mock(ProductRepository.class);
    }
    
    @Bean
    @Primary
    public StoreRepository storeRepository() {
        return mock(StoreRepository.class);
    }
}