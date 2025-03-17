package com.pricedb.service.DbUpdater;

import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Component;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

@Slf4j
@Component
public class PriceDbUpdater {
    private final List<String> urls;
    private final String xmlRawDirectory;
    private final XmlPriceLoader xmlPriceLoader;

    public PriceDbUpdater(String xmlRawDirectory, XmlPriceLoader xmlPriceLoader) {
        this.urls = new ArrayList<>();
        this.xmlRawDirectory = xmlRawDirectory;
        this.xmlPriceLoader = xmlPriceLoader;
    }

    public void addUrl(String url) {
        urls.add(url);
    }

    public void fetchAndProcessXmlFiles() {
        File directory = new File(xmlRawDirectory);
        if (!directory.exists()) {
            directory.mkdirs();
        }

        ExecutorService executor = Executors.newFixedThreadPool(urls.size() * 2);

        for (String url : urls) {
            // Producer: Fetch and extract XML files
            executor.execute(() -> {
                GzXmlFetcher fetcher = new GzXmlFetcher();
                fetcher.fetchAndProcessAllPages(url, directory);
            });

            // Consumer: Process XML files
            executor.execute(() -> {
                try {
                    xmlPriceLoader.monitorAndProcess(xmlRawDirectory);
                } catch (Exception e) {
                    log.error("Error processing XML files: ", e);
                }
            });
        }

        executor.shutdown();
    }
}