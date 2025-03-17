package com.pricedb.scheduler;

import com.pricedb.service.PriceService;
import com.pricedb.service.XmlFetcherService;
import lombok.RequiredArgsConstructor;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;
import java.time.LocalDateTime;

@Component
@RequiredArgsConstructor
public class PriceUpdateScheduler {
    private final PriceService priceService;
    private final XmlFetcherService xmlFetcherService;

    @Scheduled(cron = "${price.update.cron}")
    public void scheduledPriceUpdate() {
        LocalDateTime yesterdayDate = LocalDateTime.now().minusDays(1);
        priceService.cleanupOldEntries(yesterdayDate);
        xmlFetcherService.fetchLatestPrices();
    }
}