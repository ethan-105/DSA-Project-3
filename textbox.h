#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "buttonbox.h"

struct Text {
    sf::Font font;
    sf::Text header, subHeader, begin, y1, y2, y3, y4, dropdownButtonText, option1, option2, option3;

    Text(sf::Vector2u windowSize) {  // Add window size parameter to constructor
        // Load the font here instead of in main
        if (!font.loadFromFile("Dash-Horizon-Demo.otf")) {
            std::cerr << "Failed to load font\n";
        }

        // Setup texts with window size
        setupText(header, "Los Angeles Crime Visualizer", 100, sf::Color::White, sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.3f));
        setupText(subHeader, "Welcome. In this application, you will be able\nto compare and contrast different crime statistics\nin LA over the years 2020-2024.\nClick below to launch the visualizer.", 60, sf::Color::White, sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.15f));
        setupText(begin, "Begin", 46, sf::Color::Black, sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.85f));
        setupText(y1, "2020", 38, sf::Color::White, sf::Vector2f(windowSize.x * 0.30f, windowSize.y * 0.95f));
        setupText(y2, "2021", 38, sf::Color::White, sf::Vector2f(windowSize.x * 0.40f, windowSize.y * 0.95f));
        setupText(y3, "2022", 38, sf::Color::White, sf::Vector2f(windowSize.x * 0.50f, windowSize.y * 0.95f));
        setupText(y4, "2023", 38, sf::Color::White, sf::Vector2f(windowSize.x * 0.60f, windowSize.y * 0.95f));
        setupText(option1, "Murder", 70, sf::Color::White, sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.25f));
        setupText(option2, "Theft", 70, sf::Color::White, sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.35f));
        setupText(option3, "Assault", 70, sf::Color::White, sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.45f));
        setupText(dropdownButtonText, "Select a Crime Type", 100, sf::Color::Black, sf::Vector2f(windowSize.x * 0.05f, windowSize.y * 0.55f));
    }

    void setupText(sf::Text& text, const std::string& str, unsigned int charSize, sf::Color color, sf::Vector2f pos) {
        text.setFont(font);  // set the font
        text.setString(str);  // set the string
        text.setCharacterSize(charSize);  // set character size
        text.setFillColor(color);  // set color
        text.setPosition(pos);  // set position relative to the window size
    }
};
