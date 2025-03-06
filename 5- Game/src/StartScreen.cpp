#include "StartScreen.h"
#include <iostream>

const string BACKGROUND_IMAGE_PATH = "Files/background.jpg";
const string CALIBRI_FONT_PATH = "Files/calibri.ttf";
const string BLOCK_FONT_PATH = "Files/BLOCK-FD-ROUND.ttf";
const string MUSIC_PATH = "Files/Music.mp3";
const string CLOUD_PATH = "Files/cloud.png";
const string CLOUD2_PATH = "Files/cloud_in_white.png";
const string PLAY_PATH = "Files/Play.png";
const string LAMB_BAH_PATH = "Files/lamb-bah.mp3";
const string MUTE_PATH = "Files/mute.png";
const string UNMUTE_PATH = "Files/mute.png";

const string FONT_LOAD_ERROR = "Error loading font!" ;
const string BACKGROUND_LOAD_ERROR = "Error loading background image!" ;
const string MUSIC_LOAD_ERROR = "Unable to load music file!";
const string IMAGE_LOAD_ERROR = "Error loading start image!";

StartScreen::StartScreen(RenderWindow& win) : window(win) {
    if (!music.openFromFile(MUSIC_PATH)) {
        cerr << MUSIC_LOAD_ERROR << endl;
    } else {
        music.setLoop(true);  
        music.setVolume(50);
        music.play();  
    }
    if (!Lamb.loadFromFile(LAMB_BAH_PATH)) {
        cerr << MUSIC_LOAD_ERROR << endl;
    }
    lamb.setVolume(150);
    lamb.setBuffer(Lamb);
    if (!backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH)) {
        cerr << BACKGROUND_LOAD_ERROR << endl;
    }
    background.setTexture(backgroundTexture);

    if (!calibri.loadFromFile(CALIBRI_FONT_PATH)) {
        cerr << FONT_LOAD_ERROR << endl;
    }
    if (!Block.loadFromFile(BLOCK_FONT_PATH)) {
        cerr << FONT_LOAD_ERROR << endl;
    }
    if (!startButton.loadFromFile(PLAY_PATH)){
        cerr << IMAGE_LOAD_ERROR <<endl;
    }
    if (!cloud.loadFromFile(CLOUD2_PATH)){
        cerr << IMAGE_LOAD_ERROR <<endl;
    }
    if (!mute.loadFromFile(MUTE_PATH)){
        cerr << IMAGE_LOAD_ERROR <<endl;
    }
    if (!unmute.loadFromFile(UNMUTE_PATH)){
        cerr << IMAGE_LOAD_ERROR <<endl;
    }
    muteSP.setScale(0.10f , 0.10f);
    muteSP.setTexture(mute);
    muteSP.setPosition(50.0f , 874.0f);
    
    startButtonSP.setTexture(startButton);
    startButtonSP.setOrigin(startButton.getSize().x / 2.0f, startButton.getSize().y / 2.0f);
    startButtonSP.setPosition(1792/2.0f- 10, 1024/2.0f- 60);
    
    cloudSP.setTexture(cloud);
    cloudSP.setOrigin(cloud.getSize().x / 2.0f, cloud.getSize().y / 2.0f);  
    cloudSP.setPosition(1792/2.0f- 10, 1024/2.0f- 60) ;
    
    LeftText.setFont(Block);
    LeftText.setString("SHEEP ");
    LeftText.setCharacterSize(200);
    LeftText.setFillColor(Color::White);
    LeftText.setPosition(-LeftText.getGlobalBounds().width, 40);

    RightText.setFont(Block);
    RightText.setString("Battle");
    RightText.setCharacterSize(200);
    RightText.setFillColor(Color::White);
    RightText.setPosition(1792, 40);
}

void StartScreen::stopMusic(){
    music.stop();
}

bool StartScreen::run() {
    float rotationSpeed = 35.0f; 
    Clock clock;

    Clock delayClock; 
    const float delayDuration = 2.0f;

    float centerX = 1792/2; 
    float speed = 700.0f;

    float startButtonCurrentScale = 1.0f; 
    float startButtonTargetScale = 1.0f;  
    float startButtonSpeed = 0.1f;

    bool soundPlayed = false; 

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds(); 
        float elapsedTime = delayClock.getElapsedTime().asSeconds();
        
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    FloatRect buttonBounds = startButtonSP.getGlobalBounds();
                    FloatRect muteButtonBounds = muteSP.getGlobalBounds();
                    if (buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        lamb.play();
                        return true; 
                    }
                    else if (muteButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        if(musicIsPlaying){
                            music.setVolume(0);
                            musicIsPlaying = false;
                        }
                        else if(!musicIsPlaying){
                            music.setVolume(50);
                            musicIsPlaying = true;
                        }
                }
                }
            }
            
        }
        Vector2i mousePos = Mouse::getPosition(window);

        if (startButtonSP.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            startButtonTargetScale = 1.2f; 
            if (!soundPlayed) {
                // lamb.play();  
                // soundPlayed = true;  
            }
        
            else {
                soundPlayed = false;  
            }
        }

        else {
            startButtonTargetScale = 1.0f; 
        }
        startButtonCurrentScale += (startButtonTargetScale - startButtonCurrentScale) * startButtonSpeed;
        startButtonSP.setScale(startButtonCurrentScale, startButtonCurrentScale);
        cloudSP.rotate(rotationSpeed * deltaTime);

        if (elapsedTime > delayDuration) {
            if (LeftText.getPosition().x + LeftText.getGlobalBounds().width < centerX - 10) {
                LeftText.move(speed * deltaTime, 0);
    }
            if (RightText.getPosition().x > centerX + 10) {
                RightText.move(-speed * deltaTime, 0);
    }
}     
        window.clear();
        window.draw(background);
        window.draw(muteSP);
        window.draw(RightText);
        window.draw(LeftText);
        window.draw(cloudSP);
        window.draw(startButtonSP);
        window.display();
    }
    return false; 
}

