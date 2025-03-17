package com.pricedb.service;

import com.pricedb.service.DbUpdater.PriceDbUpdater;

import com.pricedb.service.DbUpdater.XmlPriceLoader;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import java.io.File;

@Service
public class XmlFetcherService {
    
    @Value("${xml.download.directory}")
    private String xmlDownloadDir;
    
    @Value("${price.sources.url}")
    private String priceSourceUrl;
    
    public void fetchLatestPrices() {
        File directory = new File(xmlDownloadDir);
        directory.mkdirs();
        
        PriceDbUpdater updater = new PriceDbUpdater(xmlDownloadDir, new XmlPriceLoader());
        updater.addUrl(priceSourceUrl);
        updater.fetchAndProcessXmlFiles();
    }
}