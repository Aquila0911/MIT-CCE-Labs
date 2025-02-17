package com.example.sportsapp.models;

public class Sport {
    private String name;
    private String description;
    private String imageUrl;

    // Constructor
    public Sport(String name, String description, String imageUrl) {
        this.name = name;
        this.description = description;
        this.imageUrl = imageUrl;
    }

    // Getters
    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    public String getImageUrl() {
        return imageUrl;
    }
}
