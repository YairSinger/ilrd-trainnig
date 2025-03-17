package com.bank.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.http.SessionCreationPolicy;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.security.web.authentication.UsernamePasswordAuthenticationFilter;

import com.bank.security.jwt.JwtRequestFilter;

import org.springframework.beans.factory.annotation.Autowired;


@Configuration
@EnableWebSecurity
public class SecurityConfig {

    @Autowired
    private JwtRequestFilter jwtRequestFilter;

    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        http
            .csrf(csrf -> csrf.disable())  // Disable CSRF for API endpoints
            .sessionManagement(session -> session
                .sessionCreationPolicy(SessionCreationPolicy.STATELESS))
            .authorizeHttpRequests(auth -> auth
                // Allow access to static resources
                .requestMatchers("/", "/index.html", "/static/**", "/*.js", "/*.css", "/*.ico", "/images/**").permitAll()
                // Allow access to public API endpoints
                .requestMatchers("/api/users/login", "/api/users/register", "/api/users/refresh").permitAll()
                // Require authentication for all other requests
                .requestMatchers("/api/users/transfer").authenticated()
                .requestMatchers("/api/users/all").authenticated()
                .anyRequest().authenticated())
            .addFilterBefore(jwtRequestFilter, UsernamePasswordAuthenticationFilter.class);
        
        return http.build();
    }
}