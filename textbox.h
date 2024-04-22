#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "buttonbox.h"

//Buttons buttons; 

struct Text {
    sf::Font font;
    sf::Text header, subHeader, begin, y1, y2, y3, y4, dropdownButtonText, option1, option2, option3;

    Text() {
        // load the font here instead of in main 
        if (!font.loadFromFile("Dash-Horizon-Demo.otf")) {
        }

        setupText(header, "Los Angeles Crime Visualizer", 100, sf::Color::White, { 50, 50 });
        setupText(subHeader, "Welcome. In this application, you will be able to compare and constrast different\ncrime statistics in LA over the years 2020-2024.\nClick below to launch the visualizer.", 60, sf::Color::White, { 50, 200 }); 
        setupText(begin, "Begin", 46, sf::Color::Black, { 50, 475 });
        setupText(y1, "2020", 38, sf::Color::White, { 500, 1510 });
        setupText(y2, "2021", 38, sf::Color::White, { 900, 1510 });
        setupText(y3, "2022", 38, sf::Color::White, { 1300, 1510 });
        setupText(y4, "2023", 38, sf::Color::White, { 1700, 1510 });
        setupText(option1, "Murder", 70, sf::Color::White, { 50, 450 });
        setupText(option2, "Theft", 70, sf::Color::White, { 50, 550 });
        setupText(option3, "Assault", 70, sf::Color::White, { 50, 650 });
    }

    void setupText(sf::Text& text, const std::string& str, unsigned int charSize, sf::Color color, sf::Vector2f pos) {
        text.setFont(font);  // set the font
        text.setString(str);  // set the string
        text.setCharacterSize(charSize);  // set character size
        text.setFillColor(color);  // set color
        text.setPosition(pos);  // set position
    }
};