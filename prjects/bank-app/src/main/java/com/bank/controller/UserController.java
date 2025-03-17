package com.bank.controller;

import com.bank.model.User;
import com.bank.exception.TokenRefreshException;
import com.bank.model.RefreshToken;
import com.bank.service.BankService;
import com.bank.security.jwt.JwtService;
import com.bank.service.RefreshTokenService;

import jakarta.validation.Valid;

import com.bank.payload.AuthResponse;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/users")
@CrossOrigin(origins = "*")
public class UserController {
    @Autowired
    private BankService bankService;
    
    @Autowired
    private JwtService jwtService;
    
    @Autowired
    private RefreshTokenService refreshTokenService;

    // Registration endpoint - creates user and returns tokens
    @PostMapping("/register")
    public ResponseEntity<?> registerUser(@Valid @RequestBody User user) {
        User newUser = bankService.registerUser(user.getName(), user.getEmail(), user.getPhone());
        
        String accessToken = jwtService.generateAccessToken(newUser);
        RefreshToken refreshToken = refreshTokenService.createRefreshToken(newUser);
        
        return ResponseEntity.ok(new AuthResponse(
            accessToken,
            refreshToken.getToken(),
            newUser.getEmail(),
            newUser.getBalance()
        ));
    }

    // Login endpoint - validates user and returns tokens
    @PostMapping("/login")
    public ResponseEntity<?> loginUser(@RequestParam String email) {
        System.out.println("Login attempt for email: " + email);  // Debug log
        User user = bankService.loginUser(email);
        if (user != null) {
            System.out.println("User found: " + user.getEmail());  // Debug log
            String accessToken = jwtService.generateAccessToken(user);
            RefreshToken refreshToken = refreshTokenService.createRefreshToken(user);
            
            return ResponseEntity.ok(new AuthResponse(
                accessToken,
                refreshToken.getToken(),
                user.getEmail(),
                user.getBalance()
            ));
        }
        System.out.println("User not found for email: " + email);  // Debug log
        return ResponseEntity.status(HttpStatus.UNAUTHORIZED).build();
    }

    // Token refresh endpoint
    @PostMapping("/refresh")
public ResponseEntity<?> refreshToken(@RequestParam String refreshToken) {
    try {
        // Find refresh token in repository
        RefreshToken token = refreshTokenService.findByToken(refreshToken);
        if (token == null) {
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED)
                .body("Invalid refresh token");
        }

        // Verify the token hasn't expired
        try {
            token = refreshTokenService.verifyExpiration(token);
        } catch (TokenRefreshException e) {
            return ResponseEntity.status(HttpStatus.UNAUTHORIZED)
                .body("Refresh token expired. Please login again");
        }

        // Get user and generate new access token
        User user = token.getUser();
        String newAccessToken = jwtService.generateAccessToken(user);
        
        // Return new tokens and user info
        return ResponseEntity.ok(new AuthResponse(
            newAccessToken,
            refreshToken,  // Return same refresh token as it's still valid
            user.getEmail(),
            user.getBalance()
        ));

    } catch (Exception e) {
        return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR)
            .body("Error while refreshing token: " + e.getMessage());
    }
}

    @GetMapping("/all")
    public ResponseEntity<?> getAllUsers() {
        try {
            List<User> users = bankService.getAllUsers();
            return ResponseEntity.ok(users);
        } catch (Exception e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR)
                .body("Error fetching users: " + e.getMessage());
        }
    }
}