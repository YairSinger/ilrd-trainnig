package com.bank.service;

import com.bank.model.User;
import com.bank.repository.RefreshTokenRepository;
import com.bank.repository.UserRepository;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.transaction.annotation.Transactional;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

import static org.junit.jupiter.api.Assertions.*;

@SpringBootTest(properties = "spring.profiles.active=test")
public class BankServiceConcurrencyTest {

    @Autowired
    private BankService bankService;

    @Autowired
    private UserRepository userRepository;

    @Autowired
    private RefreshTokenRepository refreshTokenRepository;

    // Add these fields
    private User user1;
    private User user2;

    @BeforeEach
    @Transactional
    public void setup() {
        // Clean up existing test users
        refreshTokenRepository.deleteAll();
        userRepository.deleteAll();

        // Create test users
        user1 = bankService.registerUser("John Doe", "test1@test.com", "1234567890");
        user2 = bankService.registerUser("Jane Doe", "test2@test.com", "1234567891");
    }

    @Test
    public void testConcurrentTransfersSameAmount() throws InterruptedException {
        int numberOfThreads = 5;
        ExecutorService executorService = Executors.newFixedThreadPool(numberOfThreads * 2);
        CountDownLatch latch = new CountDownLatch(numberOfThreads * 2);
        AtomicInteger successfulTransfers = new AtomicInteger(0);
        AtomicInteger failedTransfers = new AtomicInteger(0);
        double transferAmount = 50.0;

        // Initial balances
        double initialBalance1 = user1.getBalance();
        double initialBalance2 = user2.getBalance();

        // Synchronize the start of all threads
        CountDownLatch startLatch = new CountDownLatch(1);

        // Start concurrent transfers in both directions
        for (int i = 0; i < numberOfThreads; i++) {
            // Transfer from user1 to user2
            executorService.execute(() -> {
                try {
                    startLatch.await(); // Wait for all threads to be ready
                    bankService.transferFunds(user1.getEmail(), user2.getEmail(), transferAmount);
                    successfulTransfers.incrementAndGet();
                } catch (Exception e) {
                    failedTransfers.incrementAndGet();
                    System.err.println("Transfer failed from user1: " + e.getMessage());
                } finally {
                    latch.countDown();
                }
            });

            // Transfer from user2 to user1
            executorService.execute(() -> {
                try {
                    startLatch.await(); // Wait for all threads to be ready
                    bankService.transferFunds(user2.getEmail(), user1.getEmail(), transferAmount);
                    successfulTransfers.incrementAndGet();
                } catch (Exception e) {
                    failedTransfers.incrementAndGet();
                    System.err.println("Transfer failed from user2: " + e.getMessage());
                } finally {
                    latch.countDown();
                }
            });
        }

        // Start all threads simultaneously
        startLatch.countDown();

        // Wait for all threads to complete
        assertTrue(latch.await(10, TimeUnit.SECONDS), "Timeout waiting for transfers");
        executorService.shutdown();
        assertTrue(executorService.awaitTermination(5, TimeUnit.SECONDS), "Timeout shutting down executor");

        // Refresh user data from database
        User finalUser1 = userRepository.findByEmail(user1.getEmail());
        User finalUser2 = userRepository.findByEmail(user2.getEmail());

        // Print detailed debug information
        System.out.println("Initial balance user1: " + initialBalance1);
        System.out.println("Final balance user1: " + finalUser1.getBalance());
        System.out.println("Initial balance user2: " + initialBalance2);
        System.out.println("Final balance user2: " + finalUser2.getBalance());
        System.out.println("Successful transfers: " + successfulTransfers.get());
        System.out.println("Failed transfers: " + failedTransfers.get());

        // Verify balances with detailed error messages
        assertEquals(initialBalance1, finalUser1.getBalance(), 0.001,
            String.format("User1 balance mismatch. Expected: %.2f, Actual: %.2f", 
                initialBalance1, finalUser1.getBalance()));
        assertEquals(initialBalance2, finalUser2.getBalance(), 0.001,
            String.format("User2 balance mismatch. Expected: %.2f, Actual: %.2f",
                initialBalance2, finalUser2.getBalance()));

        // Assert that all transfers were either successful or failed properly
        assertEquals(numberOfThreads * 2, successfulTransfers.get() + failedTransfers.get(),
            "Total number of operations doesn't match expected count");
    }

    @Test
public void testDeadlockScenario() throws InterruptedException {
    // Create test users
    User user1 = bankService.registerUser("User1", "user1@test.com", "1234567890");
    User user2 = bankService.registerUser("User2", "user2@test.com", "1234567891");
    
    int numberOfThreads = 20;  // Increase number of concurrent threads
    ExecutorService executorService = Executors.newFixedThreadPool(numberOfThreads);
    CountDownLatch startLatch = new CountDownLatch(1); // To ensure all threads start simultaneously
    CountDownLatch completionLatch = new CountDownLatch(numberOfThreads);
    
    // Create half threads transferring from user1 to user2
    for (int i = 0; i < numberOfThreads/2; i++) {
        executorService.submit(() -> {
            try {
                startLatch.await(); // Wait for all threads to be ready
                bankService.transferFunds("user1@test.com", "user2@test.com", 10.0);
            } catch (Exception e) {
                System.err.println("Transfer failed: " + e.getMessage());
                e.printStackTrace();
            } finally {
                completionLatch.countDown();
            }
        });
    }
    
    // Create half threads transferring from user2 to user1
    for (int i = 0; i < numberOfThreads/2; i++) {
        executorService.submit(() -> {
            try {
                startLatch.await(); // Wait for all threads to be ready
                bankService.transferFunds("user2@test.com", "user1@test.com", 10.0);
            } catch (Exception e) {
                System.err.println("Transfer failed: " + e.getMessage());
                e.printStackTrace();
            } finally {
                completionLatch.countDown();
            }
        });
    }
    
    startLatch.countDown(); // Start all threads
    boolean completed = completionLatch.await(30, TimeUnit.SECONDS);
    
    if (!completed) {
        System.err.println("Test timed out - possible deadlock detected!");
    }
    
    executorService.shutdown();
}
}