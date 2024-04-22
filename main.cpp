#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "data.h"
#include "set.h"
#include "hashmap.h"
#include "spritebox.h"
#include "textbox.h"
#include "buttonbox.h"
#include "parsedcsv.h"
#include <climits>

using namespace std; // certfied std'er B)

int main() {

    sf::Font myFont;
    if (!myFont.loadFromFile("Dash-Horizon-Demo.otf")) {
        cerr << "Failed to load font" << endl;
        return -1;
    }
    sf::Color dropBgColor = sf::Color::White; // or any color you prefer

    // Now pass these to the Buttons constructor
    Buttons buttons(myFont, dropBgColor);
    Sprites sprites; // instantiate the structs
    Text text;

    HashMap<Data> newMap;
    Set set;
    // testing set and map

    ParsedCSV CSVFile;
    CSVFile.parseFile("Trimmed_Crime_Data_from_2020_to_Present.csv");
    
    int total = CSVFile.csvData.size();
    int count = 0;
    cout << "Set loading:" << endl;
    cout << "[----------] " << count << "/" << total;
    for (unordered_map<string, string> datapoint : CSVFile.csvData)
    {
        count++;
        cout << "\r";
        cout << "[";
        for (int i = 0; i < 10; i++)
        {
            if ((float)count / total >= (float)(i + 1) / 10)
            {
                cout << "=";
            }
            else
            {
                cout << "-";
            }
        }
        cout << "]" << count << "/" << total;

        string caseNum = datapoint["DR_NO"];
        string dateOCC = datapoint["DATE OCC"];
        string crimeCode = datapoint["Crm Cd Desc"];
        string areaName = datapoint["AREA NAME"];
        set.insert(caseNum, dateOCC, crimeCode, areaName);
    }

    // create initial welcome window ! 
    sf::RenderWindow welcomeWindow(sf::VideoMode::getDesktopMode(), "Los Angeles Crime Visualizer");
    ::ShowWindow(welcomeWindow.getSystemHandle(), SW_MAXIMIZE);

    // start the initial window loop
    // this will be the "home base" window.
    // it will have information about the project and us
    // and it will link to the two visualizers and the data algorithms in the background. 
    sf::Color pink(240, 128, 168);

    
    sf::Clock clock; // starts the clock
    string fullText = "Welcome to the Los Angeles Crime Visualizer.\n\nIn this application, you will have the ability to compare and contrast the safety of\ndifferent areas in LA based off their reported crime rates and aggregated data over the past 4 years.\n";
    string displayedText;
    size_t textIndex = 0;
    bool isSubHeaderComplete = false;



    bool isDraggingHandle1 = false;
    bool isDraggingHandle2 = false;
    bool isDropdownVisible = false; // tracks visibility of dropdown items


    //================================= START MAIN LOOP =======================================

    while (welcomeWindow.isOpen()) {

        if (clock.getElapsedTime().asMilliseconds() >= 25 && !isSubHeaderComplete) { // CLOCK FOR TEXT ANIMATION
            if (textIndex < fullText.length()) {
                displayedText += fullText[textIndex++];
                text.subHeader.setString(displayedText);
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

                    if (buttons.beginButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        welcomeWindow.close();

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
                                    if (buttons.handle1.getGlobalBounds().contains(launchEvent.mouseButton.x, launchEvent.mouseButton.y)) {
                                        isDraggingHandle1 = true;
                                    }
                                    // check if the click is on handle2
                                    if (buttons.handle2.getGlobalBounds().contains(launchEvent.mouseButton.x, launchEvent.mouseButton.y)) {
                                        isDraggingHandle2 = true;
                                    }

                                    if (launchEvent.mouseButton.button == sf::Mouse::Left) {
                                        //::Vector2i mousePos = sf::Mouse::getPosition(launch);

                                        // toggle drop menu visibility 
                                        if (buttons.triangle.getGlobalBounds().contains(launchEvent.mouseButton.x, launchEvent.mouseButton.y)) {
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
                                        float newX = launchEvent.mouseMove.x - (isDraggingHandle1 ? buttons.handle1.getRadius() : buttons.handle2.getRadius());
                                        newX = max(newX, buttons.track.getPosition().x);
                                        newX = min(newX, buttons.track.getPosition().x + buttons.track.getSize().x - 2 * (isDraggingHandle1 ? buttons.handle1.getRadius() : buttons.handle2.getRadius()));

                                        if (isDraggingHandle1) {
                                            buttons.handle1.setPosition(newX, buttons.handle1.getPosition().y);
                                        }
                                        if (isDraggingHandle2) {
                                            buttons.handle2.setPosition(newX, buttons.handle2.getPosition().y);
                                        }
                                    }
                                }
                            }

                            launch.clear(pink);

                            sf::Vector2u windowSize = welcomeWindow.getSize();
                            sf::FloatRect spriteBounds = sprites.mapSprite.getGlobalBounds();
                            sprites.mapSprite.setPosition((windowSize.x - spriteBounds.width), 45);

                            launch.draw(buttons.dropbg);
                            //launch.draw(buttons.dropdownButton);
                            launch.draw(text.dropdownButtonText);
                            launch.draw(buttons.triangle);

                            if (isDropdownVisible) {
                                launch.draw(text.option1);
                                launch.draw(text.option2);
                                launch.draw(text.option3);
                            }

                            launch.draw(buttons.track);
                            launch.draw(buttons.handle1);
                            launch.draw(buttons.handle2);
                            launch.draw(text.y1);
                            launch.draw(text.y2);
                            launch.draw(text.y3);
                            launch.draw(text.y4);
                            launch.draw(sprites.mapSprite);
                            launch.display();
                        }
                    }
                }
            }
        }

        // clear screen
        welcomeWindow.clear(pink);

        // draw the window contents here
        welcomeWindow.draw(text.header);
        welcomeWindow.draw(text.subHeader);
        if (isSubHeaderComplete) { // Check if the subHeader text animation is complete
            welcomeWindow.draw(buttons.beginButton);
            welcomeWindow.draw(text.begin);
        }

        welcomeWindow.display();
    }

    return 0;
}