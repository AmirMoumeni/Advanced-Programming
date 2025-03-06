#include "counting.h"
#include <iostream>

using namespace std;
const string CAMBRIAB_FONT_PATH = "Files/cambriab.ttf";
const string BAKCGROUND_PATH = "Files/backintro.png";
const string BEEP_BAH_PATH = "Files/beep.mp3";
const string MUSIC_LOAD_ERROR = "Unable to load music file!";


IntroScreen::IntroScreen(RenderWindow& win) 
    : window(win), countdownValue(4), isCountdownFinished(false) {

    if (!backgroundTexture.loadFromFile(BAKCGROUND_PATH)) {
        cerr << "Error loading intro background image!" << endl;
        exit(EXIT_FAILURE);
    }
    background.setTexture(backgroundTexture);
    background.setScale(0.95f, 0.90f); 

    if (!font.loadFromFile(CAMBRIAB_FONT_PATH)) {
        cerr << "Error loading font!" << endl;
        exit(EXIT_FAILURE);
    }
    if (!beepBuffer.loadFromFile(BEEP_BAH_PATH)) {
        cerr << MUSIC_LOAD_ERROR << endl;
    }
    beep.setVolume(150);
    beep.setBuffer(beepBuffer);

    countdownText.setFont(font);
    countdownText.setCharacterSize(200);
    countdownText.setFillColor(Color::White);
    countdownText.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2 -150);

    readyText.setFont(font);
    readyText.setCharacterSize(200);
    readyText.setFillColor(Color::Green);
    readyText.setPosition(window.getSize().x / 2 - 350, window.getSize().y / 2 -150);
    readyText.setString("READY??");
}

void IntroScreen::run() {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.getElapsedTime().asSeconds();

        if (!isCountdownFinished) {
            if (deltaTime >= 1.0f) { 
                countdownValue--;
                if(countdownValue > 0){
                    beep.play();
                }
                clock.restart(); 

                if (countdownValue == 0) {
                    isCountdownFinished = true; 
                }
            }

            if( countdownValue !=4 ){
                countdownText.setString(std::to_string(countdownValue));
            }
        }

        window.clear();
        window.draw(background);

        if (!isCountdownFinished) {
            window.draw(countdownText); 
            
        } else {
            window.draw(readyText); 
        }

        window.display();

        if (isCountdownFinished && deltaTime >= 4.0f) {
            break;
        }
    }
}
