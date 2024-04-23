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

    // Constructor that takes window size
    Buttons(const sf::Font& font, const sf::Color& dropBgColor, sf::Vector2u windowSize) {
        setupButtons(windowSize);
    }

    void setupButtons(sf::Vector2u windowSize) {
        // Set up each element with initial positions and sizes relative to the window size
        beginButton.setSize(sf::Vector2f(windowSize.x * 0.15f, 60.f));
        beginButton.setPosition(windowSize.x * 0.05f, windowSize.y * 0.85f);
        beginButton.setFillColor(sf::Color::White);

        track.setSize(sf::Vector2f(windowSize.x * 0.6f, 10.f));
        track.setPosition(windowSize.x * 0.1f, windowSize.y - 50);
        track.setFillColor(sf::Color::White);

        handle1.setRadius(30.f);
        handle1.setPosition(track.getPosition().x, track.getPosition().y - handle1.getRadius()/2);
        handle1.setFillColor(sf::Color::Black);

        handle2.setRadius(30.f);
        handle2.setPosition(sf::Vector2f(windowSize.x * 0.87f, track.getPosition().y - handle2.getRadius()/2));
        handle2.setFillColor(sf::Color::Black);

        dropdownButton.setSize(sf::Vector2f(windowSize.x * 0.25f, 50.f));
        dropdownButton.setPosition(windowSize.x * 0.05f, windowSize.y * 0.1f);
        dropdownButton.setFillColor(sf::Color::White);

        dropbg.setSize(sf::Vector2f(windowSize.x * 0.25f, 125.f));
        dropbg.setPosition(windowSize.x * 0.05f, windowSize.y * 0.15f);
        dropbg.setFillColor(sf::Color::White);
        dropbg.setOutlineThickness(3.0f);
        dropbg.setOutlineColor(sf::Color::Black);

        triangle.setPointCount(3);
        float triangleBaseWidth = 30.f;
        float triangleBaseHeight = 15.f;
        triangle.setPoint(0, sf::Vector2f(0, 0));
        triangle.setPoint(1, sf::Vector2f(triangleBaseWidth, 0));
        triangle.setPoint(2, sf::Vector2f(triangleBaseWidth / 2, triangleBaseHeight));
        triangle.setPosition(dropbg.getPosition().x + dropbg.getSize().x + 5, dropbg.getPosition().y + (dropbg.getSize().y - triangleBaseHeight) / 2);
        triangle.setFillColor(sf::Color::White);
        triangle.setOutlineThickness(2.f);
        triangle.setOutlineColor(sf::Color::White);
    }

    void updatePositions(sf::Vector2u windowSize) {
        // Update positions based on new window size
        setupButtons(windowSize);
    }

    void draw(sf::RenderWindow& window) {
        // Draw all buttons
        window.draw(beginButton);
        window.draw(track);
        window.draw(handle1);
        window.draw(handle2);
        window.draw(dropdownButton);
        window.draw(dropbg);
        window.draw(triangle);
    }
};
