package com.pricedb.service;

import lombok.extern.slf4j.Slf4j;
import java.io.*;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.zip.GZIPInputStream;

@Slf4j
public class SimpleXmlFetcher {
    private final Path downloadDirectory;

    public SimpleXmlFetcher(String relativePath) {
        // Create directory relative to project root
        this.downloadDirectory = Paths.get(System.getProperty("user.dir"), relativePath);
        createDownloadDirectory();
    }

    private void createDownloadDirectory() {
        try {
            Files.createDirectories(downloadDirectory);
        } catch (IOException e) {
            throw new RuntimeException("Could not create download directory", e);
        }
    }

    public File downloadAndExtractGzFile(String fileUrl) throws IOException {
        // Download GZ file
        File gzFile = downloadGzFile(fileUrl);
        
        // Extract and get XML file
        File xmlFile = extractGzFile(gzFile);
        
        // Delete GZ file after extraction
        Files.deleteIfExists(gzFile.toPath());
        
        return xmlFile;
    }

    private File downloadGzFile(String fileUrl) throws IOException {
        URL url = new URL(fileUrl);
        String fileName = fileUrl.substring(fileUrl.lastIndexOf("/") + 1);
        File outputFile = downloadDirectory.resolve(fileName).toFile();

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

    private File extractGzFile(File gzFile) throws IOException {
        String xmlFileName = gzFile.getName().replaceFirst("[.][^.]+$", ".xml");
        File outputFile = downloadDirectory.resolve(xmlFileName).toFile();

        try (GZIPInputStream gzipIn = new GZIPInputStream(new FileInputStream(gzFile));
             FileOutputStream fileOut = new FileOutputStream(outputFile)) {
            byte[] buffer = new byte[8192];
            int bytesRead;
            while ((bytesRead = gzipIn.read(buffer)) != -1) {
                fileOut.write(buffer, 0, bytesRead);
            }
        }
        return outputFile;
    }

    public Path getDownloadDirectory() {
        return downloadDirectory;
    }
}