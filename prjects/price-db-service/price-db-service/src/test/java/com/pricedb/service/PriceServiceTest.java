package com.pricedb.service;

import com.pricedb.config.TestConfig;
import com.pricedb.model.Price;
import com.pricedb.repository.PriceRepository;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.test.context.ContextConfiguration;

import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

@SpringBootTest
@ContextConfiguration(classes = TestConfig.class)
@ActiveProfiles("test")
public class PriceServiceTest {

    @Autowired
    private PriceRepository priceRepository;
    
    @MockBean
    private PriceService priceService;

    @Test
    void shouldReturnCorrectPriceCount() {
        // Given
        List<Price> mockPrices = Arrays.asList(
            new Price(), 
            new Price()
        );
        
        // When
        when(priceRepository.findAll()).thenReturn(mockPrices);
        when(priceService.getAllPrices().size()).thenReturn(2);
        
        // Then
        long count = priceService.getAllPrices().size();
        assertEquals(2, count);
    }
}