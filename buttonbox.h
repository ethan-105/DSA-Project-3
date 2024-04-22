#pragma once
#include <SFML/Graphics.hpp>

struct Buttons {

    sf::RectangleShape beginButton;
    sf::RectangleShape track;
    sf::CircleShape handle1;
    sf::CircleShape handle2;
    sf::RectangleShape dropdownButton;

    Buttons() :
        beginButton(sf::Vector2f(135.f, 60.f)),
        track(sf::Vector2f(1300.f, 10.f)),
        handle1(10.f), // radius
        handle2(10.f), // radius
        dropdownButton(sf::Vector2f(500.f, 200.f))
    {
        beginButton.setPosition(45.f, 470.f);
        beginButton.setFillColor(sf::Color::White);

        track.setPosition(500.f, 1495.f); // temp position for testing 
        track.setFillColor(sf::Color::White);

        handle1.setPosition(500.f, 1490.f); // set initial position to start of the track
        handle1.setFillColor(sf::Color::Black);

        handle2.setPosition(1800.f, 1490.f); // set initial position to start of the track
        handle2.setFillColor(sf::Color::Black);

        dropdownButton.setPosition(50.f, 300.f); // position of the dropdown button
    }
};
