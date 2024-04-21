#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "set.h"


using namespace std; // certfied std'er B)

int main() {
    std::cout << "Hello world!" << std::endl;

    // this is just a starting file.
    ifstream file("Trimmed_Crime_Data_from_2020_to_Present.csv");
    string line;
    getline(file, line); // Clear header
    Set crimeSet; // Main set
    vector<Set> monthSets(12);
    vector<Set> areaSets(1);
    vector<string> areas;
    while (getline(file, line))
    {
        // Case number
        size_t firstDelim = line.find(',');
        string caseNum = line.substr(0, firstDelim);
        //cout << caseNum << " ";
        // Date Occurred
        size_t secondDelim = line.find(',', firstDelim + 1);
        string dateOCC = line.substr(secondDelim + 1, 10);
        //cout << dateOCC << " ";
        // Time Occurred
        size_t thirdDelim = line.find(',', secondDelim + 1);
        string timeOCC = line.substr(thirdDelim + 1, 4);
        //cout << timeOCC << " ";
        // Area Name
        size_t fifthDelim = line.find(',', line.find(',', thirdDelim + 1) + 1);
        size_t sixthDelim = line.find(',', fifthDelim + 1);
        string areaName = line.substr(fifthDelim + 1, (sixthDelim - (fifthDelim + 1)));
        //cout << areaName << endl;
        switch (stoi(dateOCC.substr(0, 2)))
        {
        case 1:
            monthSets[0].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        case 2:
            monthSets[1].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        case 3:
            monthSets[2].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        case 4:
            monthSets[3].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        case 5:
            monthSets[4].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        case 6:
            monthSets[5].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        case 7:
            monthSets[6].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        case 8:
            monthSets[7].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        case 9:
            monthSets[8].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        case 10:
            monthSets[9].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        case 11:
            monthSets[10].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        case 12:
            monthSets[11].insert(caseNum, dateOCC, timeOCC, areaName);
            break;
        }
        if (areas.size() == 0)
        {
            areaSets[0].insert(caseNum, dateOCC, timeOCC, areaName);
            areas.push_back(areaName);
        }
        for (int i = 0; i < areas.size(); i++)
        {
            if (areaName == areas[i])
            {
                areaSets[i].insert(caseNum, dateOCC, timeOCC, areaName);
                break;
            }
            else if (i == areas.size() - 1)
            {
                areaSets.resize(areaSets.size() + 1);
                areaSets[i + 1].insert(caseNum, dateOCC, timeOCC, areaName);
                areas.push_back(areaName);
                break;
            }
        }
    }
    // Example uses
    cout << "Number of crimes by month" << endl;
    string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < monthSets.size(); i++)
    {
        cout << months[i] << ": " << monthSets[i].size << endl;
    }
    cout << "Number of crimes by area" << endl;
    for (int i = 0; i < monthSets.size(); i++)
    {
        cout << areas[i] << ": " << areaSets[i].size << endl;
    }
	// create initial welcome window ! 
    sf::RenderWindow welcomeWindow(sf::VideoMode(1920, 1080), "Los Angeles Crime Visualizer");

    // start the initial window loop
    // this will be the "home base" window.
    // it will have information about the project and us
    // and it will link to the two visualizers and the data algorithms in the background. 
    sf::Color pink(240, 128, 168);

    // load a font
    sf::Font font;
    if (!font.loadFromFile("Dash-Horizon-Demo.otf"))
    {
        // add error handling later 
    }

    // create a text object
    sf::Text header;
    // set the font to the text
    header.setFont(font);
    // set the string to display
    header.setString("Los Angeles Crime Visualizer");
    // set the character size
    header.setCharacterSize(100); // in pixels
    // set the color of the text
    header.setFillColor(sf::Color::White);
    // set the position of the text
    header.setPosition(50, 50); // x and y coordinates on the window


    sf::Text subHeader;
    subHeader.setFont(font);
    subHeader.setCharacterSize(38);
    subHeader.setFillColor(sf::Color::White);
    subHeader.setPosition(50, 250);

    sf::Clock clock; // Starts the clock
    string fullText = "Welcome to the Los Angeles Crime Visualizer.\n\nIn this application, you will have the ability to compare and contrast the safety of\ndifferent areas in LA based off their reported crime rates and aggregated data over the past 20 years.\n";
    string displayedText;
    size_t textIndex = 0;
    bool isSubHeaderComplete = false;


    // change this so that it only displays once the subheader text is done typing
    sf::Text begin;
    begin.setFont(font);
    begin.setCharacterSize(46);
    begin.setFillColor(sf::Color::Black);
    begin.setPosition(50, 475);
    begin.setString("Begin");


    sf::RectangleShape beginButton(sf::Vector2f(135.f, 60.f));
    beginButton.setPosition(45, 470);
    beginButton.setFillColor(sf::Color::White);
    //beginButton.setOutlineColor(sf::Color::Black); 
    //beginButton.setOutlineThickness(0.5f); 

    sf::RectangleShape curtain(sf::Vector2f(2400, 1800));
    curtain.setFillColor(pink);


    sf::RectangleShape setButton(sf::Vector2f(250.f, 50.f)); // size of the first button
    setButton.setPosition(900, 200); // position of the button
    setButton.setFillColor(sf::Color::White);// fill color 
    setButton.setOutlineColor(sf::Color::Black); // outline color 
    setButton.setOutlineThickness(2.f); // outline weight 

    sf::RectangleShape hashButton(sf::Vector2f(300.f, 50.f)); // size of the second button
    hashButton.setPosition(900, 300); // posiiton of the button
    hashButton.setFillColor(sf::Color::White);
    hashButton.setOutlineColor(sf::Color::Black);
    hashButton.setOutlineThickness(2.f);

    // create text labels for buttons
    sf::Text label1, label2;
    label1.setFont(font);
    label1.setString("Run Set Visualizer");
    label1.setCharacterSize(32);
    label1.setFillColor(sf::Color::Black);
    label1.setPosition(110, 210); // adjust position to fit within button1

    label2.setFont(font);
    label2.setString("Run HashMap Visualizer");
    label2.setCharacterSize(32);
    label2.setFillColor(sf::Color::Black);
    label2.setPosition(110, 310); // adjust position to fit within button2


    //center text onto the buttons so it looks prettier <3 

    sf::FloatRect setButtonBounds = setButton.getGlobalBounds();
    sf::FloatRect label1Bounds = label1.getGlobalBounds();
    label1.setPosition(
        setButtonBounds.left + (setButtonBounds.width - label1Bounds.width) / 2,
        setButtonBounds.top + (setButtonBounds.height - label1Bounds.height) / 2
    );

    // Center text on hashButton
    sf::FloatRect hashButtonBounds = hashButton.getGlobalBounds();
    sf::FloatRect label2Bounds = label2.getGlobalBounds();
    label2.setPosition(
        hashButtonBounds.left + (hashButtonBounds.width - label2Bounds.width) / 2,
        hashButtonBounds.top + (hashButtonBounds.height - label2Bounds.height) / 2
    );

    // This circle setup should be outside the loop, so it's only created once
    sf::CircleShape circle(100.f); // circle with a radius of 100 pixels
    circle.setFillColor(sf::Color::Magenta); // fill color green
    circle.setPosition(150, 100); // position of the circle in the window
    circle.setOutlineThickness(3.f); // thickness of circle's outline
    circle.setOutlineColor(sf::Color::White); // outline color white


    sf::CircleShape circle2(50.f);
    circle2.setFillColor(sf::Color::Cyan);
    circle2.setPosition(20, 45);
    circle2.setOutlineThickness(3.f);
    circle2.setOutlineColor(sf::Color::White);

    //bool beggining = false;
    // ================================ sprites ==================================

    sf::Texture laMap;
    if (!laMap.loadFromFile("los angeles counties.png")) {
        cout << "map broken" << endl;
    }

    sf::Sprite mapSprite;
    mapSprite.setTexture(laMap);

    sf::Texture a1;
    if (!a1.loadFromFile("los angeles counties a1.png")) {
        cout << "a broken" << endl;
    }
    sf::Sprite a1sprite;
    a1sprite.setTexture(a1);

    sf::Texture b2;
    if (!b2.loadFromFile("los angeles counties b2.png")) {
        cout << "b broken" << endl;
    }
    sf::Sprite b2sprite;
    b2sprite.setTexture(b2);

    sf::Texture m2;
    if (!m2.loadFromFile("los angeles counties 2.png")) {
        cout << "2 broken" << endl;
    }
    sf::Sprite m2sprite;
    m2sprite.setTexture(m2);

    sf::Texture m3;
    if (!m3.loadFromFile("los angeles counties 3.png")) {
        cout << "3 broken" << endl;
    }
    sf::Sprite m3sprite;
    m3sprite.setTexture(m3);

    sf::Texture m4;
    if (!m4.loadFromFile("los angeles counties 4.png")) {
        cout << "4 broken" << endl;
    }
    sf::Sprite m4sprite;
    m4sprite.setTexture(m4);

    sf::Texture m5;
    if (!m5.loadFromFile("los angeles counties 5.png")) {
        cout << "5 broken" << endl;
    }
    sf::Sprite m5sprite;
    m5sprite.setTexture(m5);

    sf::Texture m6;
    if (!m6.loadFromFile("los angeles counties 6.png")) {
        cout << "6 broken" << endl;
    }
    sf::Sprite m6sprite;
    m6sprite.setTexture(m6);

    sf::Texture m7;
    if (!m7.loadFromFile("los angeles counties 7.png")) {
        cout << "7 broken" << endl;
    }
    sf::Sprite m7sprite;
    m7sprite.setTexture(m7);

    sf::Texture m9;
    if (!m9.loadFromFile("los angeles counties 9.png")) {
        cout << "9 broken" << endl;
    }
    sf::Sprite m9sprite;
    m9sprite.setTexture(m9);

    sf::Texture m10;
    if (!m10.loadFromFile("los angeles counties 10.png")) {
        cout << "10 broken" << endl;
    }
    sf::Sprite m10sprite;
    m10sprite.setTexture(m10);

    sf::Texture m11;
    if (!m11.loadFromFile("los angeles counties 11.png")) {
        cout << "11 broken" << endl;
    }
    sf::Sprite m11sprite;
    m11sprite.setTexture(m11);

    sf::Texture m12;
    if (!m12.loadFromFile("los angeles counties 12.png")) {
        cout << "12 broken" << endl;
    }
    sf::Sprite m12sprite;
    m12sprite.setTexture(m12);

    sf::Texture m14;
    if (!m14.loadFromFile("los angeles counties 14.png")) {
        cout << "14 broken" << endl;
    }
    sf::Sprite m14sprite;
    m14sprite.setTexture(m14);


    //=================end sprites ========================================


    // track for the slider
    sf::RectangleShape track(sf::Vector2f(300, 10));
    track.setPosition(250, 295); // temp position for testing 
    track.setFillColor(sf::Color::White);

    // handle for the slider
    sf::CircleShape handle(15); // radius of 15px
    handle.setPosition(250, 285); // set initial position to start of the track
    handle.setFillColor(sf::Color::Red);

    bool isDragging = false; // tracks whether the handle is being dragged


    while (welcomeWindow.isOpen()) {

        if (clock.getElapsedTime().asMilliseconds() >= 25 && !isSubHeaderComplete) {
            if (textIndex < fullText.length()) {
                displayedText += fullText[textIndex++];
                subHeader.setString(displayedText);
                clock.restart();
            }
            else {
                isSubHeaderComplete = true; // set flag to true when animation is complete so we can draw the begin button 
            }
        }

        sf::Event event;
        while (welcomeWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                welcomeWindow.close();



            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // get the position of the click
                    sf::Vector2i mousePos = sf::Mouse::getPosition(welcomeWindow);


                    if (beginButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

                        sf::RenderWindow launch(sf::VideoMode(2400, 1800), "Comparator");

                        while (launch.isOpen()) {
                            sf::Event launchEvent;
                            while (launch.pollEvent(launchEvent)) {
                                if (launchEvent.type == sf::Event::Closed) {
                                    launch.close();
                                    welcomeWindow.close(); // close both windows when closing the comparator
                                }

                                if (launchEvent.type == sf::Event::MouseButtonPressed) {
                                    if (handle.getGlobalBounds().contains(launchEvent.mouseButton.x, launchEvent.mouseButton.y)) {
                                        isDragging = true; // begin dragging the handle
                                    }
                                }


                                if (launchEvent.type == sf::Event::MouseButtonReleased) {
                                    isDragging = false; // stop dragging the handle
                                }

                                // handles mouse movement
                                if (launchEvent.type == sf::Event::MouseMoved) {
                                    if (isDragging) {
                                        float newX = launchEvent.mouseMove.x - handle.getRadius();
                                        // make sure that the handle stays within the track's bounds 
                                        if (newX < track.getPosition().x) {
                                            newX = track.getPosition().x;
                                        }
                                        else if (newX > track.getPosition().x + track.getSize().x - 2 * handle.getRadius()) {
                                            newX = track.getPosition().x + track.getSize().x - 2 * handle.getRadius();
                                        }
                                        handle.setPosition(newX, handle.getPosition().y);
                                    }
                                }

                            }



                            // calculate the center position
                            float x = (launch.getSize().x - mapSprite.getGlobalBounds().width) / 2;
                            float y = (launch.getSize().y - mapSprite.getGlobalBounds().height) / 2;
                            mapSprite.setPosition(x, y);


                            launch.clear(pink);
                            launch.draw(track);
                            launch.draw(handle);
                            launch.draw(mapSprite);
                            launch.display();
                        }
                    }
                    // check if click is within button1 bounds
                    if (setButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        sf::RenderWindow setVisualizer(sf::VideoMode(1600, 1200), "Set Visualizer");

                        // The new window's loop
                        while (setVisualizer.isOpen()) {
                            sf::Event setVisEvent;
                            while (setVisualizer.pollEvent(setVisEvent)) {
                                if (setVisEvent.type == sf::Event::Closed)
                                    setVisualizer.close();
                            }

                            setVisualizer.clear(); // clear with default color (black)

                            // Draw the circle here
                            setVisualizer.draw(circle);
                            setVisualizer.draw(circle2);

                            setVisualizer.display(); // end the current frame
                        }
                    }

                    // check if click is within button2 bounds
                    if (hashButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // open new window or perform action for button2
                        sf::RenderWindow hashMapVisualizer(sf::VideoMode(1600, 1200), "Window 2");

                        // the hasmap window's loop
                        while (hashMapVisualizer.isOpen()) {
                            sf::Event hashVisEvent;
                            while (hashMapVisualizer.pollEvent(hashVisEvent)) {
                                if (hashVisEvent.type == sf::Event::Closed)
                                    hashMapVisualizer.close();
                            }

                            hashMapVisualizer.clear(); // clear with default color (black)

                            // draw the circle here
                            hashMapVisualizer.draw(circle);
                            hashMapVisualizer.draw(circle2);

                            hashMapVisualizer.display(); // end the current frame
                        }
                    }
                }
            }
        }

        // clear screen
        welcomeWindow.clear(pink);


        // draw the window contents here
        welcomeWindow.draw(header);
        welcomeWindow.draw(subHeader);
        if (isSubHeaderComplete) { // Check if the subHeader text animation is complete
            welcomeWindow.draw(beginButton);
            welcomeWindow.draw(begin);
        }
        // welcomeWindow.draw(setButton);
        // welcomeWindow.draw(hashButton);
        // welcomeWindow.draw(label1);
        // welcomeWindow.draw(label2);

        // update the window and display it

        //if (beggining = true) {
        //    welcomeWindow.draw(curtain); 
        //}

        welcomeWindow.display();

    }

    return 0;
}