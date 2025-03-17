package com.pricedb;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.scheduling.annotation.EnableScheduling;

@SpringBootApplication
@EnableScheduling
public class PriceDbServiceApplication {
    public static void main(String[] args) {
        SpringApplication.run(PriceDbServiceApplication.class, args);
    }
}
