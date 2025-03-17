package com.bank.security.jwt;

import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

@ConfigurationProperties(prefix = "jwt")
@Component
public class JwtProperties {
    private String secret;
    private Expiration expiration;

    // Getters and setters
    public String getSecret() {
        return secret;
    }

    public void setSecret(String secret) {
        this.secret = secret;
    }

    public Expiration getExpiration() {
        return expiration;
    }

    public void setExpiration(Expiration expiration) {
        this.expiration = expiration;
    }

    public static class Expiration {
        private long access;
        private long refresh;

        // Getters and setters
        public long getAccess() {
            return access;
        }

        public void setAccess(long access) {
            this.access = access;
        }

        public long getRefresh() {
            return refresh;
        }

        public void setRefresh(long refresh) {
            this.refresh = refresh;
        }
    }
}