package com.pricedb.controller;

import com.pricedb.service.XmlFetcherService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api/v1/admin")
@RequiredArgsConstructor
public class UpdateController {
    private final XmlFetcherService xmlFetcherService;

    @PostMapping("/update-prices")
    public ResponseEntity<String> triggerPriceUpdate() {
        xmlFetcherService.fetchLatestPrices();
        return ResponseEntity.ok("Price update triggered successfully");
    }
}