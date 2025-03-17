package com.pricedb.service.DbUpdater;

import lombok.extern.slf4j.Slf4j;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import org.springframework.stereotype.Component;
import java.io.*;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.zip.GZIPInputStream;

@Slf4j
@Component
public class GzXmlFetcher {
    private static final int TOTAL_PAGES = 80; // Configurable

    public void fetchAndProcessAllPages(String baseUrl, File xmlRawDirectory) {
        for (int page = 1; page <= TOTAL_PAGES; page++) {
            String pageUrl = baseUrl + "?page=" + page;
            try {
                log.info("Fetching XML from page {}: {}", page, pageUrl);
                fetchPageContent(pageUrl, xmlRawDirectory);
            } catch (Exception e) {
                log.error("Error processing page {}: ", page, e);
            }
        }
    }

    private void fetchPageContent(String pageUrl, File xmlRawDirectory) throws Exception {
        List<String> gzLinks = fetchGzFileLinks(pageUrl);
        for (String gzLink : gzLinks) {
            try {
                File gzFile = downloadGzFile(gzLink, xmlRawDirectory);
                extractGzFile(gzFile, xmlRawDirectory);
            } catch (Exception e) {
                log.error("Error processing GZ file from {}: ", gzLink, e);
            }
        }
    }

    private List<String> fetchGzFileLinks(String pageUrl) throws IOException {
        List<String> gzLinks = new ArrayList<>();
        Document document = Jsoup.connect(pageUrl)
                .userAgent("Mozilla/5.0")
                .timeout(30000)
                .get();

        Elements links = document.getElementsByAttribute("href");
        for (Element link : links) {
            String href = link.absUrl("href");
            if (href.toLowerCase().endsWith(".gz")) {
                gzLinks.add(href);
            }
        }
        return gzLinks;
    }

    private File downloadGzFile(String fileUrl, File downloadDir) throws IOException {
        URL url = new URL(fileUrl);
        String fileName = fileUrl.substring(fileUrl.lastIndexOf("/") + 1);
        File outputFile = new File(downloadDir, fileName);

        try (InputStream in = url.openStream();
             FileOutputStream fos = new FileOutputStream(outputFile)) {
            byte[] buffer = new byte[8192];
            int bytesRead;
            while ((bytesRead = in.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
        }
        return outputFile;
    }

    private void extractGzFile(File gzFile, File outputDir) throws IOException {
        String xmlFileName = gzFile.getName().replaceFirst("[.][^.]+$", ".xml");
        File outputFile = new File(outputDir, xmlFileName);

        try (GZIPInputStream gzipIn = new GZIPInputStream(new FileInputStream(gzFile));
             FileOutputStream fileOut = new FileOutputStream(outputFile)) {
            byte[] buffer = new byte[8192];
            int bytesRead;
            while ((bytesRead = gzipIn.read(buffer)) != -1) {
                fileOut.write(buffer, 0, bytesRead);
            }
        } finally {
            if (!gzFile.delete()) {
                log.warn("Failed to delete GZ file: {}", gzFile.getAbsolutePath());
            }
        }
    }
}