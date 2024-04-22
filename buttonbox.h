#pragma once
#include <SFML/Graphics.hpp>

struct Buttons {
    sf::RectangleShape beginButton;
    sf::RectangleShape track;
    sf::CircleShape handle1;
    sf::CircleShape handle2;
    sf::RectangleShape dropdownButton;
    sf::RectangleShape dropbg;  // Background for dropdown
    sf::ConvexShape triangle;   // Indicator triangle for dropdown

    // Constructor modified to take window size
    Buttons(const sf::Font& font, const sf::Color& dropBgColor, sf::Vector2u windowSize) :
        beginButton(sf::Vector2f(135.f, 60.f)), // Size relative to design preference
        track(sf::Vector2f(windowSize.x * 0.8f, 10.f)),  // Width is 80% of window width
        handle1(15.f), // Radius in pixels, static size
        handle2(15.f), // Radius in pixels, static size
        dropdownButton(sf::Vector2f(windowSize.x * 0.5f, 200.f)),  // Width is 50% of window width
        dropbg(sf::Vector2f(windowSize.x * 0.9f, 125.f)) // Width is 90% of window width
    {
        // Setup for beginButton
        beginButton.setPosition(windowSize.x * 0.05f, windowSize.y * 0.9f); // Position at 5% from the left and 90% from the top
        beginButton.setFillColor(sf::Color::White);

        // Setup for track
        track.setPosition(windowSize.x * 0.1f, windowSize.y - 50); // Center horizontally and 50 pixels from the bottom
        track.setFillColor(sf::Color::White);

        // Setup for handles
        handle1.setPosition(track.getPosition().x, track.getPosition().y + track.getSize().y / 2); // Starting point of the track
        handle2.setPosition(track.getPosition().x + track.getSize().x - handle2.getRadius() * 2, track.getPosition().y + track.getSize().y / 2); // End point of the track
        handle1.setFillColor(sf::Color::Black);
        handle2.setFillColor(sf::Color::Black);

        // Setup for dropdownButton
        dropdownButton.setPosition(windowSize.x * 0.25f, windowSize.y * 0.1f); // Center horizontally and 10% from the top

        // Setup for dropbg
        dropbg.setFillColor(dropBgColor);
        dropbg.setOutlineThickness(3.0f);
        dropbg.setOutlineColor(sf::Color::Black);
        dropbg.setPosition(windowSize.x * 0.05f, windowSize.y * 0.2f); // 5% from left and 20% from top

        // Setup for triangle
        sf::FloatRect textBounds = dropbg.getGlobalBounds(); // Adjust based on dropbg position
        triangle.setPointCount(3);
        float triangleBaseHeight = 60.f;  // Height of the triangle
        float triangleBaseWidth = 60.f;   // Width of the triangle base
        float triangleX = textBounds.left + textBounds.width + 10;  // 10 pixels padding from text
        float triangleY = dropbg.getPosition().y + (dropbg.getSize().y / 2) - (triangleBaseHeight / 2);
        triangle.setPoint(0, sf::Vector2f(triangleX, triangleY));
        triangle.setPoint(1, sf::Vector2f(triangleX + triangleBaseWidth, triangleY));
        triangle.setPoint(2, sf::Vector2f(triangleX + triangleBaseWidth / 2, triangleY + triangleBaseHeight));
        triangle.setFillColor(sf::Color::White);
        triangle.setOutlineThickness(2.f);
        triangle.setOutlineColor(sf::Color::White);
    }
};
