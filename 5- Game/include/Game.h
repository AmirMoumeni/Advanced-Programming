#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Character.h"

using namespace sf;
using namespace std;

class Game {
private:
    RenderWindow& window;
    
    bool GameOver;
    
    Font font;
    
    int rightHealth;
    Text rightHealthText;

    int leftHealth;
    Text leftHealthText;
    
    Texture backgroundTexture;     
    Sprite background;

    Texture RightWinnerTexture;     
    Sprite RightWinner; 

    Texture LeftWinnerTexture;     
    Sprite LeftWinner; 

    Texture borderTexture;
    Sprite border;

    Texture leftSelectorTexture;     
    Sprite leftSelector;
    bool leftSelectorIsVisible;

    Texture rightSelectorTexture;     
    Sprite rightSelector;
    bool rightSelectorIsVisible;

    vector <unique_ptr<Character>> characterVector;
    vector <unique_ptr<Character>> characterVector2;
   
    Clock leftPlayerClock;
    Clock rightPlayerClock;
    const float coolDown = 2.0f;

    private:
    vector<Character*> leftwar1;
    vector<Character*> rightwar1;

    vector<Character*> leftwar2;
    vector<Character*> rightwar2;
    
    vector<Character*> leftwar3;
    vector<Character*> rightwar3;
    
    vector<Character*> leftwar4;
    vector<Character*> rightwar4;

    void updateCharacters(float deltaTime);
    void updateCharacters2(float deltaTime);
    void drawCharacters();
    void drawCharacters2();
    void addCharacter(unique_ptr<Character> character);
    void addCharacter2(unique_ptr<Character>character2);
    void randomlyAdder();
    void randomlyAdder2();

    void checkCollision();
    void checkTeamCollision();

    void checkCollision2();
    void checkTeamCollision2();

    void checkCollision3();
    void checkTeamCollision3();

    void checkCollision4();
    void checkTeamCollision4();

    void decreaseRightHealth(float amount);
    void decreaseLeftHealth(float amount);
    float spawnY; 

    int leftTeamStrength;
    int rightTeamStrength;

    int leftTeamStrength2;
    int rightTeamStrength2;

    int leftTeamStrength3;
    int rightTeamStrength3;

    int leftTeamStrength4;
    int rightTeamStrength4;
public:
    Game(RenderWindow& win);
    void leftSelectorHandle(Event event , Sprite& selector);
    void rightSelectorHandle(Event event , Sprite& selector);
   
    void run(); 
    ~Game();
};

#endif 
