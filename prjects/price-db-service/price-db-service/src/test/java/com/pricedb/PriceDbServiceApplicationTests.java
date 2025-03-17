package com.pricedb;

import com.pricedb.config.TestConfig;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.test.context.ContextConfiguration;

import static org.junit.jupiter.api.Assertions.assertTrue;

@SpringBootTest
@ContextConfiguration(classes = {PriceDbServiceApplication.class, TestConfig.class})
@ActiveProfiles("test")
public class PriceDbServiceApplicationTests {

    @Test
    void contextLoads() {
        assertTrue(true);
    }
}