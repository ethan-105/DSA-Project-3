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
#include <chrono>
#include <climits>

using namespace std; // certfied std'er B)

int main() {

    sf::Font myFont;
    if (!myFont.loadFromFile("Dash-Horizon-Demo.otf")) {
        cerr << "Failed to load font" << endl;
        return -1;
    }
    sf::Color dropBgColor = sf::Color::White; // or any color you prefer

    
    Sprites sprites; // instantiate the structs
    //Text text;

    HashMap<HashMap<list<Data>*>*> theMap; // map of (region: (year: (caseNum: data)))
    map<int, Set> yearSets;
    Set set2020;
    yearSets.insert(pair<int, Set>(2020, set2020));
    Set set2021;
    yearSets.insert(pair<int, Set>(2021, set2021));
    Set set2022;
    yearSets.insert(pair<int, Set>(2022, set2022));
    Set set2023;
    yearSets.insert(pair<int, Set>(2023, set2023));
    vector<Set> regionSet(1);
    vector<string> regionsKnown;
    // testing set and map
    ParsedCSV CSVFile;
    CSVFile.parseFile("Trimmed_Crime_Data_from_2020_to_Present.csv");
    
    chrono::time_point<chrono::steady_clock> test = chrono::high_resolution_clock::now();
    int total = CSVFile.csvData.size();
    int count = 0;
    int percent = 0;
    cout << "Set loading:" << endl;
    cout << "[----------] " << count << "/" << total;
    for (unordered_map<string, string> datapoint : CSVFile.csvData)
    {
        count++;
        if (((float)count / total >= (float)(percent) / 10))
        {
            if (((float)count / total >= (float)(percent + 1) / 10))
            {
                percent++; 
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
            }
        }

        string caseNum = datapoint["DR_NO"];
        string dateOCC = datapoint["DATE OCC"];
        string crimeCode = datapoint["Crm Cd Desc"];
        string areaName = datapoint["AREA NAME"];
        Data data = Data(caseNum, dateOCC, crimeCode, areaName);

        // Add to set map by year
        if (dateOCC.substr(6, 4) == "2020")
        {
            yearSets.at(2020).insert(data);
        }
        else if (dateOCC.substr(6, 4) == "2021")
        {
            yearSets.at(2021).insert(data);
        }
        else if (dateOCC.substr(6, 4) == "2022")
        {
            yearSets.at(2022).insert(data);
        }
        else if (dateOCC.substr(6, 4) == "2023")
        {
            yearSets.at(2023).insert(data);
        }

        // Add to a regions map
        if (regionsKnown.size() == 0)
        {
            regionSet[0].insert(data);
            regionsKnown.push_back(areaName);
        }
        for (int i = 0; i < regionsKnown.size(); i++)
        {
            if (areaName == regionsKnown[i])
            {
                regionSet[i].insert(data);
                break;
            }
            else if (i == regionsKnown.size() - 1)
            {
                regionSet.resize(regionSet.size() + 1);
                regionSet[i + 1].insert(data);
                regionsKnown.push_back(areaName);
                break;
            }
        }
    }
    cout << endl;
    int maxRegionCrime = 0;
    for (int i = 0; i < regionSet.size(); i++)
    {
        if (regionSet[i].size > maxRegionCrime) maxRegionCrime = regionSet[i].size;
    }

    chrono::time_point<chrono::steady_clock> testFinal = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedTime{ testFinal - test };
    cout << "Time taken for Set Init: " << elapsedTime.count() << endl;
    /*Set newSet = setIntersect(set, set2);
    cout << newSet.size << endl;*/

    test = chrono::high_resolution_clock::now();
    count = 0;
    percent = 0;
    cout << "Unordered Map loading:" << endl;
    cout << "[----------] " << count << "/" << total;
    for (unordered_map<string, string> datapoint : CSVFile.csvData)
    {
        count++;
        if (((float)count / total >= (float)(percent) / 10))
        {
            if (((float)count / total >= (float)(percent + 1) / 10))
            {
                percent++;
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
            }
        }

        string caseNum = datapoint["DR_NO"];
        string dateOCC = datapoint["DATE OCC"];
        string YEAR = dateOCC.substr(6, 4);
        string crimeCode = datapoint["Crm Cd Desc"];
        string areaName = datapoint["AREA NAME"];
        Data data(caseNum, dateOCC, crimeCode, areaName);
        bool hasYear = theMap.has(YEAR); 
        if (!hasYear) {
            HashMap<list<Data>*>* toEmplace= new HashMap<list<Data>*>{};
            list<Data>* toEmplaceSub = new list<Data>{};
            toEmplaceSub->push_back(data);
            toEmplace->emplace(areaName, toEmplaceSub);
            theMap.emplace(YEAR, toEmplace);
        }
        else {
            bool hasArea = theMap.at(YEAR)->has(areaName);
            if (!hasArea) {
                list<Data>* toEmplaceSub = new list<Data>{};
                toEmplaceSub->push_back(data);
                theMap.at(YEAR)->emplace(areaName, toEmplaceSub);
            }
            else {
                theMap.at(YEAR)->at(areaName)->push_back(data);
            }
        }
    }
    cout << endl;

    testFinal = chrono::high_resolution_clock::now();
    elapsedTime = testFinal - test ;
    cout << "Time taken for Unordered Map Init: " << elapsedTime.count() << endl;

    int leftDate = 2020;
    int rightDate = 2024;
    int minDate = min(leftDate, rightDate);
    int maxDate = max(leftDate, rightDate);
    bool dateRangeUpdated = false;
    vector<Set> tempSets = regionSet;

    // create initial welcome window ! 
    sf::RenderWindow welcomeWindow(sf::VideoMode::getDesktopMode(), "Los Angeles Crime Visualizer");
    ::ShowWindow(welcomeWindow.getSystemHandle(), SW_MAXIMIZE);
   
    sf::Vector2u windowSize = welcomeWindow.getSize();  // Get the size of the window
    Buttons buttons(myFont, dropBgColor, windowSize);  // pass window size

    // start the initial window loop
    // this will be the "home base" window.
    // it will have information about the project and us
    // and it will link to the two visualizers and the data algorithms in the background. 
    sf::Color pink(240, 128, 168);

    
    sf::Clock clock; // starts the clock
    string fullText = "Welcome. In this application, you will be able\nto compare and contrast different crime statistics\nin LA over the years 2020 - 2024.\nClick below to launch the visualizer."; 
    string displayedText;
    size_t textIndex = 0;
    bool isSubHeaderComplete = false;



    bool isDraggingHandle1 = false;
    bool isDraggingHandle2 = false;
    bool isDropdownVisible = false; // tracks visibility of dropdown items


    //================================= START MAIN LOOP =======================================
    //sf::Vector2u windowSize = welcomeWindow.getSize();  // Get the size of the window
    Text text(windowSize);  // Pass window size
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
            else if (event.type == sf::Event::Resized) {
                // Update the window view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                welcomeWindow.setView(sf::View(visibleArea));

                // Recalculate the positions and sizes of buttons
                buttons.updatePositions(sf::Vector2u(event.size.width, event.size.height)); // Changed line
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(welcomeWindow);
                    if (text.begin.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "Begin text clicked, attempting to open launch window..." << std::endl;
                        welcomeWindow.close();
                        sf::RenderWindow launch(sf::VideoMode::getDesktopMode(), "Comparator");
                        
                        // create launch window here 
                        // get window size to make positions proportional to the window
                        sf::Vector2u size = launch.getSize();
                        sf::Vector2f center(size.x / 2.f, size.y / 2.f);

                        buttons.track.setSize(sf::Vector2f(size.x * 0.8f, 10.f));  // Making track width 80% of window width
                        buttons.track.setPosition(size.x * 0.1f, size.y - 100);  // Centering track horizontally and 50px from the bottom
                        buttons.track.setFillColor(sf::Color::White); // Ensuring the track is visible, set a contrasting color
                       
                        sprites.a1sprite.setOrigin(sprites.a1sprite.getLocalBounds().width / 2, sprites.a1sprite.getLocalBounds().height / 2);
                        sprites.a1sprite.setPosition(center);
                        sprites.a1sprite.setColor(sf::Color(255 * ((float)tempSets[11].size / maxRegionCrime), 0, 0));

                        sprites.b2sprite.setOrigin(sprites.b2sprite.getLocalBounds().width / 2, sprites.b2sprite.getLocalBounds().height / 2);
                        sprites.b2sprite.setPosition(center);
                        sprites.b2sprite.setColor(sf::Color(255 * ((float)tempSets[12].size / maxRegionCrime), 0, 0));

                        sprites.m2sprite.setOrigin(sprites.m2sprite.getLocalBounds().width / 2, sprites.m2sprite.getLocalBounds().height / 2);
                        sprites.m2sprite.setPosition(center);
                        sprites.m2sprite.setColor(sf::Color(255 * ((float)tempSets[0].size / maxRegionCrime), 0, 0));

                        sprites.m3sprite.setOrigin(sprites.m3sprite.getLocalBounds().width / 2, sprites.m3sprite.getLocalBounds().height / 2);
                        sprites.m3sprite.setPosition(center);
                        sprites.m3sprite.setColor(sf::Color(255 * ((float)tempSets[1].size / maxRegionCrime), 0, 0));

                        sprites.m4sprite.setOrigin(sprites.m4sprite.getLocalBounds().width / 2, sprites.m4sprite.getLocalBounds().height / 2);
                        sprites.m4sprite.setPosition(center);
                        sprites.m4sprite.setColor(sf::Color(255 * ((float)tempSets[2].size / maxRegionCrime), 0, 0));

                        sprites.m5sprite.setOrigin(sprites.m5sprite.getLocalBounds().width / 2, sprites.m5sprite.getLocalBounds().height / 2);
                        sprites.m5sprite.setPosition(center);
                        sprites.m5sprite.setColor(sf::Color(255 * ((float)tempSets[3].size / maxRegionCrime), 0, 0));

                        sprites.m6sprite.setOrigin(sprites.m6sprite.getLocalBounds().width / 2, sprites.m6sprite.getLocalBounds().height / 2);
                        sprites.m6sprite.setPosition(center);
                        sprites.m6sprite.setColor(sf::Color(255 * ((float)tempSets[4].size / maxRegionCrime), 0, 0));

                        sprites.m7sprite.setOrigin(sprites.m7sprite.getLocalBounds().width / 2, sprites.m7sprite.getLocalBounds().height / 2);
                        sprites.m7sprite.setPosition(center);
                        sprites.m7sprite.setColor(sf::Color(255 * ((float)tempSets[5].size / maxRegionCrime), 0, 0));

                        sprites.m9sprite.setOrigin(sprites.m9sprite.getLocalBounds().width / 2, sprites.m9sprite.getLocalBounds().height / 2);
                        sprites.m9sprite.setPosition(center);
                        sprites.m9sprite.setColor(sf::Color(255 * ((float)tempSets[6].size / maxRegionCrime), 0, 0));

                        sprites.m10sprite.setOrigin(sprites.m10sprite.getLocalBounds().width / 2, sprites.m10sprite.getLocalBounds().height / 2);
                        sprites.m10sprite.setPosition(center);
                        sprites.m10sprite.setColor(sf::Color(255 * ((float)tempSets[7].size / maxRegionCrime), 0, 0));

                        sprites.m11sprite.setOrigin(sprites.m11sprite.getLocalBounds().width / 2, sprites.m11sprite.getLocalBounds().height / 2);
                        sprites.m11sprite.setPosition(center);
                        sprites.m11sprite.setColor(sf::Color(255 * ((float)tempSets[8].size / maxRegionCrime), 0, 0));

                        sprites.m12sprite.setOrigin(sprites.m12sprite.getLocalBounds().width / 2, sprites.m12sprite.getLocalBounds().height / 2);
                        sprites.m12sprite.setPosition(center);
                        sprites.m12sprite.setColor(sf::Color(255 * ((float)tempSets[9].size / maxRegionCrime), 0, 0));

                        sprites.m14sprite.setOrigin(sprites.m14sprite.getLocalBounds().width / 2, sprites.m14sprite.getLocalBounds().height / 2);
                        sprites.m14sprite.setPosition(center);
                        sprites.m14sprite.setColor(sf::Color(255 * ((float)tempSets[10].size / maxRegionCrime), 0, 0));


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
                                    if (text.option1.getGlobalBounds().contains(launchEvent.mouseButton.x, launchEvent.mouseButton.y)) {
                                        text.option1.setFillColor(sf::Color::Black);
                                    }
                                    if (text.option2.getGlobalBounds().contains(launchEvent.mouseButton.x, launchEvent.mouseButton.y)) {
                                        text.option2.setFillColor(sf::Color::Black);
                                    }
                                    if (text.option3.getGlobalBounds().contains(launchEvent.mouseButton.x, launchEvent.mouseButton.y)) {
                                        text.option3.setFillColor(sf::Color::Black);
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
                                            if (newX >= size.x * 0.1f && newX <= size.x * 0.22f)
                                            {
                                                buttons.handle1.setPosition(size.x * 0.1f, buttons.handle1.getPosition().y);
                                                leftDate = 2020;
                                            }
                                            if (newX > size.x * 0.22f && newX <= size.x * 0.49f)
                                            {
                                                buttons.handle1.setPosition(size.x * 0.3666f, buttons.handle1.getPosition().y);
                                                leftDate = 2021;
                                            }
                                            if (newX > size.x * 0.49f && newX <= size.x * 0.76f)
                                            {
                                                buttons.handle1.setPosition(size.x * 0.6333f, buttons.handle1.getPosition().y);
                                                leftDate = 2022;
                                            }
                                            if (newX > size.x * 0.76f && newX <= size.x * 0.9f)
                                            {
                                                buttons.handle1.setPosition(size.x * 0.87f, buttons.handle1.getPosition().y);
                                                leftDate = 2023;
                                            }
                                            if (buttons.handle2.getPosition().x == buttons.handle1.getPosition().x // Overlapping 
                                                && (buttons.handle2.getPosition().y == buttons.handle1.getPosition().y || isDraggingHandle1)) // But prevent infinite movement
                                            {
                                                buttons.handle2.setPosition(buttons.handle2.getPosition().x, buttons.handle1.getPosition().y - 64);
                                            }
                                            else // Reset y to base level (1)
                                            {
                                                buttons.handle2.setPosition(buttons.handle2.getPosition().x, buttons.handle1.getPosition().y);
                                            }
                                        }
                                        else if (isDraggingHandle2) { // else if should prevent stuck overlapping
                                            buttons.handle2.setPosition(newX, buttons.handle2.getPosition().y);
                                            if (newX >= size.x * 0.1f && newX <= size.x * 0.22f)
                                            {
                                                buttons.handle2.setPosition(size.x * 0.1f, buttons.handle2.getPosition().y);
                                                rightDate = 2020;
                                            }
                                            if (newX > size.x * 0.22f && newX <= size.x * 0.49f)
                                            {
                                                buttons.handle2.setPosition(size.x * 0.3666f, buttons.handle2.getPosition().y);
                                                rightDate = 2021;
                                            }
                                            if (newX > size.x * 0.49f && newX <= size.x * 0.76f)
                                            {
                                                buttons.handle2.setPosition(size.x * 0.6333f, buttons.handle2.getPosition().y);
                                                rightDate = 2022;
                                            }
                                            if (newX > size.x * 0.76f && newX <= size.x * 0.9f)
                                            {
                                                buttons.handle2.setPosition(size.x * 0.87f, buttons.handle2.getPosition().y);
                                                rightDate = 2023;
                                            }
                                            if (buttons.handle2.getPosition().x == buttons.handle1.getPosition().x // Overlapping 
                                                && (buttons.handle2.getPosition().y == buttons.handle1.getPosition().y || isDraggingHandle2)) // But prevent infinite movement
                                            {
                                                buttons.handle2.setPosition(buttons.handle2.getPosition().x, buttons.handle1.getPosition().y - 64);
                                            }
                                            else // Reset y to base level (1)
                                            {
                                                buttons.handle2.setPosition(buttons.handle2.getPosition().x, buttons.handle1.getPosition().y);
                                            }
                                        }
                                        int tempMin = minDate;
                                        int tempMax = maxDate;
                                        minDate = min(leftDate, rightDate);
                                        maxDate = max(leftDate, rightDate);
                                        dateRangeUpdated == true;
                                        
                                        if (dateRangeUpdated)
                                        {
                                            cout << "In this block" << endl;
                                            vector<int> dateRange;
                                            maxRegionCrime = 0;
                                            tempSets.clear();
                                            for (int i = 2020; i < 2024; i++)
                                            {
                                                if (i >= minDate && i <= maxDate)
                                                {
                                                    dateRange.push_back(i);
                                                }
                                            }
                                            for (int i = 0; i < regionSet.size(); i++)
                                            {
                                                Set tempSet;
                                                for (int j = 0; j < dateRange.size(); j++)
                                                {
                                                    setUnion(tempSet, setIntersect(yearSets.at(dateRange[j]), regionSet[i]));
                                                }
                                                tempSets.push_back(tempSet);
                                                if (tempSets[i].size > maxRegionCrime) maxRegionCrime = tempSets[i].size;
                                            }
                                            sprites.a1sprite.setColor(sf::Color(255 * ((float)tempSets[11].size / maxRegionCrime), 0, 0));
                                            sprites.b2sprite.setColor(sf::Color(255 * ((float)tempSets[12].size / maxRegionCrime), 0, 0));
                                            sprites.m2sprite.setColor(sf::Color(255 * ((float)tempSets[0].size / maxRegionCrime), 0, 0));
                                            sprites.m3sprite.setColor(sf::Color(255 * ((float)tempSets[1].size / maxRegionCrime), 0, 0));
                                            sprites.m4sprite.setColor(sf::Color(255 * ((float)tempSets[2].size / maxRegionCrime), 0, 0));
                                            sprites.m5sprite.setColor(sf::Color(255 * ((float)tempSets[3].size / maxRegionCrime), 0, 0));
                                            sprites.m6sprite.setColor(sf::Color(255 * ((float)tempSets[4].size / maxRegionCrime), 0, 0));
                                            sprites.m7sprite.setColor(sf::Color(255 * ((float)tempSets[5].size / maxRegionCrime), 0, 0));
                                            sprites.m9sprite.setColor(sf::Color(255 * ((float)tempSets[6].size / maxRegionCrime), 0, 0));
                                            sprites.m10sprite.setColor(sf::Color(255 * ((float)tempSets[7].size / maxRegionCrime), 0, 0));
                                            sprites.m11sprite.setColor(sf::Color(255 * ((float)tempSets[8].size / maxRegionCrime), 0, 0));
                                            sprites.m12sprite.setColor(sf::Color(255 * ((float)tempSets[9].size / maxRegionCrime), 0, 0));
                                            sprites.m14sprite.setColor(sf::Color(255 * ((float)tempSets[10].size / maxRegionCrime), 0, 0));
                                            launch.draw(sprites.a1sprite);
                                            launch.draw(sprites.b2sprite);
                                            launch.draw(sprites.m2sprite);
                                            launch.draw(sprites.m3sprite);
                                            launch.draw(sprites.m4sprite);
                                            launch.draw(sprites.m5sprite);
                                            launch.draw(sprites.m6sprite);
                                            launch.draw(sprites.m7sprite);
                                            launch.draw(sprites.m9sprite);
                                            launch.draw(sprites.m10sprite);
                                            launch.draw(sprites.m11sprite);
                                            launch.draw(sprites.m12sprite);
                                            launch.draw(sprites.m14sprite);
                                            launch.display();
                                        }

                                    }
                                }
                            }

                            launch.clear(pink);

                            sf::Vector2u windowSize = welcomeWindow.getSize();
                            sf::FloatRect spriteBounds = sprites.mapSprite.getGlobalBounds();
                            sprites.mapSprite.setPosition((windowSize.x - spriteBounds.width), 45);

                            launch.draw(buttons.dropbg); // Assuming this should also appear in the launch window
                            launch.draw(text.dropdownButtonText); // Ensure this text is drawn in the launch window

                            if (isDropdownVisible) {
                                launch.draw(text.option1);
                                launch.draw(text.option2);
                                launch.draw(text.option3);
                            }

                            launch.draw(buttons.triangle); 
                            launch.draw(buttons.track);
                            launch.draw(buttons.handle1);
                            launch.draw(buttons.handle2);
                            launch.draw(text.y1);
                            launch.draw(text.y2);
                            launch.draw(text.y3);
                            launch.draw(text.y4);
                            //launch.draw(sprites.mapSprite);
                            launch.draw(sprites.a1sprite); 
                            launch.draw(sprites.b2sprite);
                            launch.draw(sprites.m2sprite); 
                            launch.draw(sprites.m3sprite); 
                            launch.draw(sprites.m4sprite); 
                            launch.draw(sprites.m5sprite); 
                            launch.draw(sprites.m6sprite); 
                            launch.draw(sprites.m7sprite); 
                            launch.draw(sprites.m9sprite); 
                            launch.draw(sprites.m10sprite);
                            launch.draw(sprites.m11sprite); 
                            launch.draw(sprites.m12sprite); 
                            launch.draw(sprites.m14sprite); 
                  

                            launch.display();
                            
                        }
                    }
                }
            }
        }

        // clear screen
        welcomeWindow.clear(pink);
        //buttons.draw(welcomeWindow);
        // draw the window contents here
        welcomeWindow.draw(text.header);
        welcomeWindow.draw(text.subHeader);
        if (isSubHeaderComplete) { // Check if the subHeader text animation is complete
            //welcomeWindow.draw(buttons.beginButton);
            welcomeWindow.draw(text.begin);
        }

        welcomeWindow.display();
    }

    return 0;
}