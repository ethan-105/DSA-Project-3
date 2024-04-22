#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Sprites {
    sf::Texture laMap, a1, b2, m2, m3, m4, m5, m6, m7, m9, m10, m11, m12, m14;
    sf::Sprite mapSprite, a1sprite, b2sprite, m2sprite, m3sprite, m4sprite, m5sprite, m6sprite, m7sprite, m9sprite, m10sprite, m11sprite, m12sprite, m14sprite;

    Sprites() {
        if (!laMap.loadFromFile("los angeles counties.png"))
            cout << "map broken" << endl;
        mapSprite.setTexture(laMap);
        mapSprite.setScale(1.5f, 1.5f);

        if (!a1.loadFromFile("los angeles counties a1.png"))
            cout << "a1 texture broken" << endl;
        a1sprite.setTexture(a1);

        if (!b2.loadFromFile("los angeles counties b2.png"))
            cout << "b2 texture broken" << endl;
        b2sprite.setTexture(b2);

        if (!m2.loadFromFile("los angeles counties 2.png")) {
            cout << "2 broken" << endl;
        }
        m2sprite.setTexture(m2);

        if (!m3.loadFromFile("los angeles counties 3.png")) {
            cout << "3 broken" << endl;
        }
        m3sprite.setTexture(m3);

        if (!m4.loadFromFile("los angeles counties 4.png")) {
            cout << "4 broken" << endl;
        }
        m4sprite.setTexture(m4);

        if (!m5.loadFromFile("los angeles counties 5.png")) {
            cout << "5 broken" << endl;
        }
        m5sprite.setTexture(m5);
        
        if (!m6.loadFromFile("los angeles counties 6.png")) {
            cout << "6 broken" << endl;
        }
        m6sprite.setTexture(m6);

        if (!m7.loadFromFile("los angeles counties 7.png")) {
            cout << "7 broken" << endl;
        }
        m7sprite.setTexture(m7);


        if (!m9.loadFromFile("los angeles counties 9.png")) {
            cout << "9 broken" << endl;
        }
        m9sprite.setTexture(m9);

        if (!m10.loadFromFile("los angeles counties 10.png")) {
            cout << "10 broken" << endl;
        }
        m10sprite.setTexture(m10);

        if (!m11.loadFromFile("los angeles counties 11.png")) {
            cout << "11 broken" << endl;
        }
        m11sprite.setTexture(m11);

        if (!m12.loadFromFile("los angeles counties 12.png")) {
            cout << "12 broken" << endl;
        }
        m12sprite.setTexture(m12);

        if (!m14.loadFromFile("los angeles counties 14.png"))
           cout << "m14 texture broken" << endl;
        m14sprite.setTexture(m14);


        
    }
};
