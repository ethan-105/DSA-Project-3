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

Sprites sprites; // instantiate the sprites class 

Text text; 

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

    
    sf::Clock clock; // starts the clock
    string fullText = "Welcome to the Los Angeles Crime Visualizer.\n\nIn this application, you will have the ability to compare and contrast the safety of\ndifferent areas in LA based off their reported crime rates and aggregated data over the past 20 years.\n";
    string displayedText;
    size_t textIndex = 0;
    bool isSubHeaderComplete = false;


    sf::RectangleShape beginButton(sf::Vector2f(135.f, 60.f));
    beginButton.setPosition(45, 470);
    beginButton.setFillColor(sf::Color::White);


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

    

    //======================menu select==============================

    // drop down button
    sf::RectangleShape dropdownButton(sf::Vector2f(500.f, 200.f)); // size of the dropdown button
    dropdownButton.setPosition(50, 300); // position of the dropdown button
    //dropdownButton.setOutlineColor(sf::Color::White);


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

                            sf::Vector2u windowSize = welcomeWindow.getSize();
                            sf::FloatRect spriteBounds = sprites.mapSprite.getGlobalBounds();
                            sprites.mapSprite.setPosition((windowSize.x - spriteBounds.width) - 45, 45);

                            //launch.draw(dropdownButton);
                            launch.draw(text.dropdownButtonText);

                            if (isDropdownVisible) {
                                launch.draw(text.option1);
                                launch.draw(text.option2);
                                launch.draw(text.option3);
                            }

                            launch.draw(track);
                            launch.draw(handle1);
                            launch.draw(handle2);
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
            welcomeWindow.draw(beginButton);
            welcomeWindow.draw(text.begin);
        }

        welcomeWindow.display();

    }

    return 0;
}