#include "WinnerDisplay.h"
#include <iostream>

using namespace std;
using namespace sf;

WinnerDisplay::WinnerDisplay() : isDisplaying(false) {}

void WinnerDisplay::loadWinnerImage(const string& imagePath) {
    if (!winnerTexture.loadFromFile(imagePath)) {
        cerr << "Error loading winner image!" << endl;
    }
    winnerSprite.setTexture(winnerTexture);
}

void WinnerDisplay::startDisplay() {
    isDisplaying = true;
    displayClock.restart();
}

bool WinnerDisplay::update() {
    if (isDisplaying && displayClock.getElapsedTime().asSeconds() >= 3) {
        isDisplaying = false; 
        return true;          
    }
    return false;
}

void WinnerDisplay::draw(RenderWindow& window) {
    if (isDisplaying) {
        window.draw(winnerSprite);
    }
}
