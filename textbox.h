#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Text {
    sf::Font font;
    sf::Text header, subHeader, begin, y1, y2, y3, y4, dropdownButtonText, option1, option2, option3;

    Text() {
        // Load the font
        if (!font.loadFromFile("Dash-Horizon-Demo.otf")) {
            std::cerr << "Failed to load font." << std::endl;
            return;  // Optionally, handle the error more gracefully
        }

        // Setup each text object
        setupText(header, "Los Angeles Crime Visualizer", 100, sf::Color::White, { 50, 50 });
        setupText(subHeader, "", 38, sf::Color::White, { 50, 250 });  // Text to be set later
        setupText(begin, "Begin", 46, sf::Color::Black, { 50, 475 });
        setupText(y1, "2020", 38, sf::Color::White, { 500, 1510 });
        setupText(y2, "2021", 38, sf::Color::White, { 900, 1510 });
        setupText(y3, "2022", 38, sf::Color::White, { 1300, 1510 });
        setupText(y4, "2023", 38, sf::Color::White, { 1700, 1510 });
        setupText(dropdownButtonText, "Select a Crime Type", 80, sf::Color::Black, { 50, 300 });  // Adjusted position
        setupText(option1, "Murder", 70, sf::Color::White, { 50, 450 });
        setupText(option2, "Theft", 70, sf::Color::White, { 50, 550 });
        setupText(option3, "Assault", 70, sf::Color::White, { 50, 650 });
    }

    // Helper function to configure text objects
    void setupText(sf::Text& text, const std::string& str, unsigned int charSize, sf::Color color, sf::Vector2f pos) {
        text.setFont(font);  // Set the font
        text.setString(str);  // Set the string
        text.setCharacterSize(charSize);  // Set character size
        text.setFillColor(color);  // Set color
        text.setPosition(pos);  // Set position
    }
};