package com.bank.security.jwt.util;

import io.jsonwebtoken.SignatureAlgorithm;
import io.jsonwebtoken.security.Keys;
import java.security.Key;

import io.jsonwebtoken.io.Encoders;

public class JwtSecretGenerator {
    public static void main(String[] args) {
        // Generate a secure key for HS256
        Key key = Keys.secretKeyFor(SignatureAlgorithm.HS256);
        
        // Convert it to Base64 encoded string
        String secretString = Encoders.BASE64.encode(key.getEncoded());
        
        System.out.println("Generated JWT Secret Key:");
        System.out.println(secretString);
    }
}