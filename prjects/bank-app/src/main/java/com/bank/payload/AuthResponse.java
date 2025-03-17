package com.bank.payload;



public class AuthResponse {
    private String accessToken;
    private String refreshToken;
    private String email;
    private double balance;

    public AuthResponse(String accessToken, String refreshToken, String email, double balance) {
        this.accessToken = accessToken;
        this.refreshToken = refreshToken;
        this.email = email;
        this.balance = balance;
    }

    // Getters and setters
    public String getAccessToken() { return accessToken; }
    public void setAccessToken(String accessToken) { this.accessToken = accessToken; }
    public String getRefreshToken() { return refreshToken; }
    public void setRefreshToken(String refreshToken) { this.refreshToken = refreshToken; }
    public String getEmail() { return email; }
    public void setEmail(String email) { this.email = email; }
    public double getBalance() { return balance; }
    public void setBalance(double balance) { this.balance = balance; }
}