package com.bank.security.jwt;

import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Component;
import org.springframework.web.filter.OncePerRequestFilter;
import java.io.IOException;
import java.util.ArrayList;
import com.bank.service.BankService;
import com.bank.model.User;
import com.bank.security.jwt.JwtService;

@Component
public class JwtRequestFilter extends OncePerRequestFilter {
    @Autowired
    private JwtService jwtService;
    
    @Autowired
    private BankService bankService;

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain chain)
            throws ServletException, IOException {
        
        final String authHeader = request.getHeader("Authorization");
        System.out.println("Auth header: " + authHeader); // Debug log

        String email = null;
        String jwt = null;

        if (authHeader != null && authHeader.startsWith("Bearer ")) {
            jwt = authHeader.substring(7);
            try {
                email = jwtService.getEmailFromToken(jwt);
                System.out.println("Extracted email: " + email); // Debug log
            } catch (Exception e) {
                System.out.println("Token validation failed: " + e.getMessage()); // Debug log
                // Token validation failed
            }
        }

        if (email != null && SecurityContextHolder.getContext().getAuthentication() == null) {
            User user = bankService.loginUser(email);
            if (jwtService.validateToken(jwt)) {
                // Set authentication in context
                UsernamePasswordAuthenticationToken authentication = 
                    new UsernamePasswordAuthenticationToken(user, null, new ArrayList<>());
                SecurityContextHolder.getContext().setAuthentication(authentication);
            }
        }
        chain.doFilter(request, response);
    }
}