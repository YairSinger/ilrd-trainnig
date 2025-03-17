package com.bank.service;

import java.time.Instant;
import java.util.UUID;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import com.bank.exception.TokenRefreshException;
import com.bank.model.RefreshToken;
import com.bank.model.User;
import com.bank.repository.RefreshTokenRepository;
import com.bank.repository.UserRepository;

@Service
public class RefreshTokenService {
    @Autowired
    private RefreshTokenRepository refreshTokenRepository;
    
    @Autowired
    private UserRepository userRepository;

    @Value("${jwt.expiration.refresh}")
    private Long refreshTokenDurationMs;

    public RefreshToken createRefreshToken(User user) {
        RefreshToken refreshToken = new RefreshToken();
        refreshToken.setUser(user);
        refreshToken.setExpiryDate(Instant.now().plusMillis(refreshTokenDurationMs));
        refreshToken.setToken(UUID.randomUUID().toString());
        return refreshTokenRepository.save(refreshToken);
    }

    public RefreshToken verifyExpiration(RefreshToken token) throws TokenRefreshException {
        if (token.getExpiryDate().compareTo(Instant.now()) < 0) {
            // Token has expired - clean up and throw exception
            refreshTokenRepository.delete(token);
            throw new TokenRefreshException(token.getToken(), 
                "Refresh token expired. Please make a new login request");
        }
        
        return token;
    }

    public RefreshToken findByToken(String refreshToken) {
      return  refreshTokenRepository.findByToken(refreshToken);
       
    }
}