package com.bank.exception;

public class TokenRefreshException extends Throwable {

    public TokenRefreshException(String token, String string) {
        super(string + " " + token);        
    }

}
