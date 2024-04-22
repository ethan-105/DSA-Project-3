#pragma once
#include <SFML/Graphics.hpp>

struct Buttons {
    // Member variables for buttons and shapes
    sf::RectangleShape beginButton;
    sf::RectangleShape track;
    sf::CircleShape handle1;
    sf::CircleShape handle2;
    sf::RectangleShape dropdownButton;
    sf::RectangleShape dropbg;  // Background for dropdown
    sf::ConvexShape triangle;   // Indicator triangle for dropdown

    // Constructor
    Buttons(const sf::Font& font, const sf::Color& dropBgColor) :
        beginButton(sf::Vector2f(135.f, 60.f)),
        track(sf::Vector2f(300.f, 10.f)), // defualt size, will adjust later
        handle1(10.f), // radius
        handle2(10.f), // radius
        dropdownButton(sf::Vector2f(500.f, 200.f)),
        dropbg(sf::Vector2f(870.f, 125.f)) // Initializing dropbg here
    {
        // Setup for beginButton
        beginButton.setPosition(45.f, 470.f);
        beginButton.setFillColor(sf::Color::White);

        // Setup for track
        track.setPosition(500.f, 1495.f);
        track.setFillColor(sf::Color::White);

        // Setup for handles
        handle1.setPosition(500.f, 1490.f);
        handle1.setFillColor(sf::Color::Black);
        handle2.setPosition(1800.f, 1490.f);
        handle2.setFillColor(sf::Color::Black);

        // Setup for dropdownButton
        dropdownButton.setPosition(50.f, 300.f);

        // Setup for dropbg
        dropbg.setFillColor(dropBgColor);
        dropbg.setOutlineThickness(3.0f);
        dropbg.setOutlineColor(sf::Color::Black);
        dropbg.setPosition(50, 250);

        // Setup for triangle
        sf::FloatRect textBounds = dropbg.getGlobalBounds(); // Adjust based on actual dropdown text position
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