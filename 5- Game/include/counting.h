#ifndef INTROSCREEN_H
#define INTROSCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class IntroScreen {
private:
    RenderWindow& window;           
    Texture backgroundTexture;      
    Sprite background;              
    Font font;                      
    Text countdownText;             
    Text readyText;                 
    Clock clock;          
    SoundBuffer beepBuffer;
    Sound beep;
    int countdownValue;             
    bool isCountdownFinished;       

public:
    IntroScreen(RenderWindow& win); 
    void run();                     
};

#endif // INTROSCREEN_H
