#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "data.h"
#include "set.h"
#include "hashmap.h"

vector<string> readCSVLine(string &line) {
    size_t index = 0;
    vector<string> output;
    while (true) {
        size_t endIndex = index;
        string nextToAdd = "";
        if (line[index] == '"') {
            endIndex = line.find('"', index + 1);
            output.push_back(line.substr(index + 1, (endIndex - index - 1)));
            if (endIndex == string::npos) {
                break;
            }
            index = endIndex + 2;
            continue;
        }
        endIndex = line.find(',', index + 1);
        if (endIndex == string::npos) {
            break;
        }
        output.push_back(line.substr(index, (endIndex - index)));
        index = endIndex + 1;
    }
    return output;
}

using namespace std; // certfied std'er B)

int main() {
    std::cout << "Hello world!" << std::endl;

    // this is just a starting file.
    ifstream file("Trimmed_Crime_Data_from_2020_to_Present.csv");
    string line;
    getline(file, line); // Clear header
    int cnt = 0;

    HashMap<Data> newMap;
    Set newSet;
    // testing set and map

    while (getline(file, line))
    {
        vector<string> vect = readCSVLine(line);

        string caseNum = vect[0];
        //cout << caseNum << " ";

        // Date reported
        string dateRptd = vect[1].substr(0, 10); // just get date info
        cout << dateRptd << " ";

        // Date Occurred
        string dateOCC = vect[2].substr(0, 10); // just get date info
        cout << dateOCC << " ";
        // Time Occurred
        string timeOCC = vect[3];
        cout << timeOCC << " ";
        // Area Name
        string areaName = vect[5];
        cout << areaName << " ";

        string crimeType = vect[9];
        cout << crimeType << endl;
        /*
        if (cnt < 100) {
            Data data(caseNum, dateOCC, timeOCC, areaName);
            newSet.insert(caseNum, dateOCC, timeOCC, areaName);
            newMap.insert(data.caseNum, data);
            cnt++;
        }
        else {
            break;
        }
        */
    }
    /*
    cout << "Set:" << endl;
    newSet.printTree();
    cout << "Total entries: " << newSet.size << endl;
    cout << endl << "Map:" << endl;
    for (HashMap<Data>::ItemPair pair : newMap.getIterable()) {
        Data data = pair.value;
        cout << data.caseNum << " " << data.dateOCC << " " << data.timeOCC << " " << data.areaName << endl;
    }
    cout << "Total entries: " << newMap.getSize() << endl;
    */

    // create initial welcome window ! 
    sf::RenderWindow welcomeWindow(sf::VideoMode::getDesktopMode(), "Los Angeles Crime Visualizer");
    ::ShowWindow(welcomeWindow.getSystemHandle(), SW_MAXIMIZE);

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
    sf::RectangleShape track(sf::Vector2f(1300, 10));
    track.setPosition(500, 1495); // temp position for testing 
    track.setFillColor(sf::Color::White);

    // handle for the slider
    sf::CircleShape handle1(10); // radius of 15px
    handle1.setPosition(500, 1490); // set initial position to start of the track
    handle1.setFillColor(sf::Color::Black);

    // handle for the slider
    sf::CircleShape handle2(10); // radius of 15px
    handle2.setPosition(1800, 1490); // set initial position to start of the track
    handle2.setFillColor(sf::Color::Black);

    bool isDraggingHandle1 = false;
    bool isDraggingHandle2 = false;


    sf::Text y1;
    y1.setFont(font);
    y1.setFillColor(sf::Color::White);
    y1.setCharacterSize(38);
    y1.setString("2020");
    y1.setPosition(500, 1510);

    sf::Text y2;
    y2.setFont(font);
    y2.setFillColor(sf::Color::White);
    y2.setCharacterSize(38);
    y2.setString("2021");
    y2.setPosition(900, 1510);

    sf::Text y3;
    y3.setFont(font);
    y3.setFillColor(sf::Color::White);
    y3.setCharacterSize(38);
    y3.setString("2022");
    y3.setPosition(1300, 1510);

    sf::Text y4;
    y4.setFont(font);
    y4.setFillColor(sf::Color::White);
    y4.setCharacterSize(38);
    y4.setString("2023");
    y4.setPosition(1700, 1510);

    //======================menu select==============================

    // drop down button
    sf::RectangleShape dropdownButton(sf::Vector2f(500.f, 200.f)); // size of the dropdown button
    dropdownButton.setPosition(50, 300); // position of the dropdown button
    //dropdownButton.setOutlineColor(sf::Color::White);

    sf::Text dropdownButtonText;
    dropdownButtonText.setFont(font);
    dropdownButtonText.setString("Select a Crime Type");
    dropdownButtonText.setCharacterSize(80);
    dropdownButtonText.setFillColor(sf::Color::Black);
    sf::FloatRect dropdownButtonBounds = dropdownButton.getGlobalBounds();
    dropdownButtonText.setPosition(
        dropdownButtonBounds.left + (dropdownButtonBounds.width - dropdownButtonText.getLocalBounds().width) / 2,
        dropdownButtonBounds.top + (dropdownButtonBounds.height - dropdownButtonText.getLocalBounds().height) / 2
    );

    // menu items
    sf::Text option1;
    // set the font to the text
    option1.setFont(font);
    // set the string to display
    option1.setString("Murder");
    // set the character size
    option1.setCharacterSize(70); // in pixels
    // set the color of the text
    option1.setFillColor(sf::Color::White);
    // set the position of the text
    option1.setPosition(50, 450); // x and y coordinates on the window


    sf::Text option2;
    // set the font to the text
    option2.setFont(font);
    // set the string to display
    option2.setString("Theft");
    // set the character size
    option2.setCharacterSize(70); // in pixels
    // set the color of the text
    option2.setFillColor(sf::Color::White);
    // set the position of the text
    option2.setPosition(50, 550); // x and y coordinates on the window

    sf::Text option3;
    // set the font to the text
    option3.setFont(font);
    // set the string to display
    option3.setString("Assault");
    // set the character size
    option3.setCharacterSize(70); // in pixels
    // set the color of the text
    option3.setFillColor(sf::Color::White);
    // set the position of the text
    option3.setPosition(50, 650); // x and y coordinates on the window

    bool isDropdownVisible = false; // tracks visibility of dropdown items



    //================================= START MAIN LOOP =======================================


    while (welcomeWindow.isOpen()) {

        if (clock.getElapsedTime().asMilliseconds() >= 25 && !isSubHeaderComplete) { // CLOCK FOR TEXT ANIMATION
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

                        sf::RenderWindow launch(sf::VideoMode(2400, 1800), "Comparator"); // create launch window here 

                        while (launch.isOpen()) { // launch window main loop 

                            sf::Event launchEvent;

                            while (launch.pollEvent(launchEvent)) {
                                if (launchEvent.type == sf::Event::Closed) {
                                    launch.close();
                                    welcomeWindow.close(); // close both windows when closing the comparator
                                }

                                if (launchEvent.type == sf::Event::MouseButtonPressed) {

                                    // check if the click is on handle1
                                    if (handle1.getGlobalBounds().contains(launchEvent.mouseButton.x, launchEvent.mouseButton.y)) {
                                        isDraggingHandle1 = true;
                                    }
                                    // check if the click is on handle2
                                    if (handle2.getGlobalBounds().contains(launchEvent.mouseButton.x, launchEvent.mouseButton.y)) {
                                        isDraggingHandle2 = true;
                                    }

                                    if (launchEvent.mouseButton.button == sf::Mouse::Left) {
                                        //::Vector2i mousePos = sf::Mouse::getPosition(launch);

                                        // toggle drop menu visibility 
                                        if (dropdownButton.getGlobalBounds().contains(launchEvent.mouseButton.x, launchEvent.mouseButton.y)) {
                                            isDropdownVisible = !isDropdownVisible;
                                        }
                                    }
                                }

                                if (launchEvent.type == sf::Event::MouseButtonReleased) {
                                    isDraggingHandle1 = false;
                                    isDraggingHandle2 = false;
                                }

                                // handles mouse movement
                                if (launchEvent.type == sf::Event::MouseMoved) {
                                    if (isDraggingHandle1 || isDraggingHandle2) {
                                        float newX = launchEvent.mouseMove.x - (isDraggingHandle1 ? handle1.getRadius() : handle2.getRadius());
                                        newX = max(newX, track.getPosition().x);
                                        newX = min(newX, track.getPosition().x + track.getSize().x - 2 * (isDraggingHandle1 ? handle1.getRadius() : handle2.getRadius()));

                                        if (isDraggingHandle1) {
                                            handle1.setPosition(newX, handle1.getPosition().y);
                                        }
                                        if (isDraggingHandle2) {
                                            handle2.setPosition(newX, handle2.getPosition().y);
                                        }
                                    }
                                }
                            }

                            launch.clear(pink);

                            mapSprite.setScale(1.5f, 1.5f);

                            sf::Vector2u windowSize = welcomeWindow.getSize();
                            sf::FloatRect spriteBounds = mapSprite.getGlobalBounds();
                            mapSprite.setPosition((windowSize.x - spriteBounds.width) - 45, 45);

                            //launch.draw(dropdownButton);
                            launch.draw(dropdownButtonText);

                            if (isDropdownVisible) {
                                launch.draw(option1);
                                launch.draw(option2);
                                launch.draw(option3);
                            }

                            launch.draw(track);
                            launch.draw(handle1);
                            launch.draw(handle2);
                            launch.draw(y1);
                            launch.draw(y2);
                            launch.draw(y3);
                            launch.draw(y4);
                            launch.draw(mapSprite);
                            launch.display();
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

        welcomeWindow.display();

    }

    return 0;
}