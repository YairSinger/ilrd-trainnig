package com.bank.service;

import com.bank.exception.ValidationException;
import com.bank.model.User;
import com.bank.repository.UserRepository;

import org.hibernate.StaleObjectStateException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Isolation;
import org.springframework.transaction.annotation.Transactional;
import jakarta.persistence.EntityManager;
import jakarta.persistence.LockModeType;
import jakarta.persistence.OptimisticLockException;
import jakarta.persistence.PessimisticLockException;
import org.springframework.dao.DataAccessException;
import org.springframework.orm.ObjectOptimisticLockingFailureException;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.List;

@Service
public class BankService {

    @Autowired
    private UserRepository userRepository;

    @Autowired
    private EntityManager entityManager;
    @Transactional
    public User registerUser(String name, String email, String phone) {
        
          List<String> errors = new ArrayList<>();

         // Check if email already exists
         if (userRepository.findByEmail(email) != null) {
            errors.add("Email already registered");
        }

         // If there are any errors, throw validation exception
         if (!errors.isEmpty()) {
            throw new ValidationException(errors);
        }

        User user = new User();
        user.setName(name.trim());
        user.setEmail(email.trim().toLowerCase());
        user.setPhone(phone.trim());
        return userRepository.save(user);
    }
    @Transactional(readOnly = true)
    public User loginUser(String email) {
        return userRepository.findByEmail(email);
    }

    @Transactional(isolation = Isolation.SERIALIZABLE, timeout = 10)
public double transferFunds(String fromEmail, String toEmail, double amount) {
    System.out.println("Starting transfer from " + fromEmail + " to " + toEmail);
    try {
        // First, get both users without locks to get their IDs
        User fromUser = userRepository.findByEmail(fromEmail);
        User toUser = userRepository.findByEmail(toEmail);
        System.out.println("Attempting to lock users - From ID: " + fromUser.getId() + ", To ID: " + toUser.getId());
        if (fromUser == null || toUser == null) {
            throw new IllegalArgumentException("One or both users not found");
        }

        // Lock users based on ID order to prevent deadlocks
        User firstLockUser;
        User secondLockUser;
        boolean isFromFirst = fromUser.getId() < toUser.getId();
        
        if (isFromFirst) {
            firstLockUser = entityManager.createQuery(
                    "SELECT u FROM User u WHERE u.id = :id", User.class)
                    .setParameter("id", fromUser.getId())
                    .setLockMode(LockModeType.PESSIMISTIC_WRITE)
                    .getSingleResult();

            secondLockUser = entityManager.createQuery(
                    "SELECT u FROM User u WHERE u.id = :id", User.class)
                    .setParameter("id", toUser.getId())
                    .setLockMode(LockModeType.PESSIMISTIC_WRITE)
                    .getSingleResult();
        } else {
            firstLockUser = entityManager.createQuery(
                    "SELECT u FROM User u WHERE u.id = :id", User.class)
                    .setParameter("id", toUser.getId())
                    .setLockMode(LockModeType.PESSIMISTIC_WRITE)
                    .getSingleResult();

            secondLockUser = entityManager.createQuery(
                    "SELECT u FROM User u WHERE u.id = :id", User.class)
                    .setParameter("id", fromUser.getId())
                    .setLockMode(LockModeType.PESSIMISTIC_WRITE)
                    .getSingleResult();
        }

        System.out.println("Locks acquired for transfer from " + fromEmail + " to " + toEmail);

        // Map back to from/to users
        fromUser = isFromFirst ? firstLockUser : secondLockUser;
        toUser = isFromFirst ? secondLockUser : firstLockUser;

        // Validate transaction
        if (fromUser.getBalance() < amount) {
            throw new IllegalArgumentException("Insufficient funds");
        }

        // Perform transfer
        fromUser.setBalance(fromUser.getBalance() - amount);
        toUser.setBalance(toUser.getBalance() + amount);

        // Save changes
        entityManager.merge(fromUser);
        entityManager.merge(toUser);
        entityManager.flush();

        return fromUser.getBalance();

    } catch (PessimisticLockException e) {
        System.err.println("PassimisticLock exception Error in transfer from " + fromEmail + " to " + toEmail + ": " + e.getMessage());
        throw new RuntimeException("Transaction could not be completed due to concurrent access. Please try again.", e);
    } catch (DataAccessException e) {
        System.err.println("Data Access exception Error in transfer from " + fromEmail + " to " + toEmail + ": " + e.getMessage());
        throw new RuntimeException("Database error occurred during transfer", e);
    }
}    @Transactional(readOnly = true)
    public List<User> getAllUsers() {
        return userRepository.findAll();
    }

    
}
