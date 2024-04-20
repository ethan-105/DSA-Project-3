#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <set.h>


using namespace std; // certfied std'er B)

int main() {
    std::cout << "Hello world!" << std::endl;

    // this is just a starting file.
    ifstream file("Trimmed_Crime_Data_from_2020_to_Present.csv");
    string line;
    getline(file, line); // Clear header
    while (getline(file, line))
    {
        // Case number
        size_t firstDelim = line.find(',');
        string caseNum = line.substr(0, firstDelim);
        //cout << caseNum << " ";
        // Date reported
        size_t secondDelim = line.find(',', firstDelim + 1);
        string dateRptd = line.substr(firstDelim + 1, 10);
        //cout << dateRptd << " ";
        // Date Occurred
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

    while (welcomeWindow.isOpen()) {
        sf::Event event;
        while (welcomeWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                welcomeWindow.close();

            if (clock.getElapsedTime().asMilliseconds() >= 10 && !isSubHeaderComplete) {
                if (textIndex < fullText.length()) {
                    displayedText += fullText[textIndex++];
                    subHeader.setString(displayedText);
                    clock.restart();
                }
                else {
                    isSubHeaderComplete = true; // set flag to true when animation is complete so we can draw the begin button 
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // get the position of the click
                    sf::Vector2i mousePos = sf::Mouse::getPosition(welcomeWindow);


                    if (beginButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

                        //beggining = true; 
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