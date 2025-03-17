package com.pricedb.model;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class PriceUpdateRequest {
    private String productId;
    private String storeId;
    private Double price;
    private String updateSource;
}