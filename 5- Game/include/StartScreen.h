#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class StartScreen {
private:
    RenderWindow& window;          
    Texture backgroundTexture;     
    Sprite background;             
    Font calibri;    
    Font Block;              
    Texture startButton; 
    Sprite startButtonSP;
    Texture cloud;
    Sprite cloudSP;
    Text LeftText;
    Text RightText;
    SoundBuffer Lamb;
    Sound lamb;
    Music music;
    Clock clock;
    Texture mute;
    Sprite muteSP;
    Texture unmute;
    Sprite unmuteSP;
    bool musicIsPlaying;
public:
    StartScreen(RenderWindow& win);
    void stopMusic();
    bool run(); 
};

#endif // STARTSCREEN_H
