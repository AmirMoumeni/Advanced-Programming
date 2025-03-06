#include <iostream>
#include "Game.h"
#include "Character.h"
#include "Sheep.h"
#include "Goat.h"
#include "Pig.h"
#include "RightPig.h"
#include "RightSheep.h"
#include "RightGoat.h"

using namespace sf;
using namespace std;

const string BACKGROUND_IMAGE_PATH = "Files/grass.png";
const string LEFT_SELECTOR_IMAGE_PATH = "Files/left.png";
const string RIGHT_SELECTOR_IMAGE_PATH = "Files/right.png";
const string BORDER_IMAGE_PATH = "Files/border2.png";
const string CAMBRIAB_FONT_PATH = "Files/cambriab.ttf";
const string RIGHT_WINNER_PATH = "Files/blue_winner.jpg";
const string LEFT_WINNER_PATH = "Files/red_winner.jpg";

const string BACKGROUND_LOAD_ERROR = "Error loading game background image!";

Game::Game(RenderWindow& win) : window(win) , spawnY(160.0f) {
    rightHealth = 20.0f;
    leftHealth = 20.0f;
    leftTeamStrength = 0;
    rightTeamStrength= 0;

    leftTeamStrength2 = 0;
    rightTeamStrength2= 0;

    leftTeamStrength3 = 0;
    rightTeamStrength3 = 0;

    leftTeamStrength4 = 0;
    rightTeamStrength4 = 0;

    GameOver = false;
    if(!RightWinnerTexture.loadFromFile(RIGHT_WINNER_PATH)){
        cerr << BACKGROUND_LOAD_ERROR << endl;
    }
    RightWinner.setTexture(RightWinnerTexture);

    if(!LeftWinnerTexture.loadFromFile(LEFT_WINNER_PATH)){
        cerr << BACKGROUND_LOAD_ERROR << endl;
    }
    LeftWinner.setTexture(LeftWinnerTexture);

    if (!backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH)) {
        cerr << BACKGROUND_LOAD_ERROR << endl;
    }
    background.setTexture(backgroundTexture);
    background.setScale(0.95f , 0.9f);

    if (!borderTexture.loadFromFile(BORDER_IMAGE_PATH)){
        cerr << BACKGROUND_LOAD_ERROR << endl;
    }
    border.setTexture(borderTexture);
    border.setScale(0.95f , 0.9f);

    if (!leftSelectorTexture.loadFromFile(LEFT_SELECTOR_IMAGE_PATH)) {
        cerr << BACKGROUND_LOAD_ERROR << endl;
    }  
    leftSelector.setTexture(leftSelectorTexture);
    leftSelector.setPosition(146.0f , 130.0f);
    leftSelector.setColor(Color(255,255,255,0));
    leftSelectorIsVisible = false;

    if (!rightSelectorTexture.loadFromFile(RIGHT_SELECTOR_IMAGE_PATH)) {
        cerr << BACKGROUND_LOAD_ERROR << endl;
    }  
    rightSelector.setTexture(rightSelectorTexture);
    rightSelector.setPosition(71.0f , 130.0f);
    rightSelector.setColor(Color(255,255,255,0));
    rightSelectorIsVisible = false;

    if (!font.loadFromFile(CAMBRIAB_FONT_PATH)) {
        cerr << "Error loading font!" << endl;
        exit(EXIT_FAILURE);
    }

    rightHealthText.setFont(font);
    rightHealthText.setCharacterSize(40);
    rightHealthText.setFillColor(Color::White);
    rightHealthText.setPosition(window.getSize().x / 2 + 40, 60);

    leftHealthText.setFont(font);
    leftHealthText.setCharacterSize(40);
    leftHealthText.setFillColor(Color::White);
    leftHealthText.setPosition(window.getSize().x / 2 - 90, 60);

}

void Game::leftSelectorHandle(Event event , Sprite& selector){
    float timeSinceLastAction = leftPlayerClock.getElapsedTime().asSeconds();
    if (timeSinceLastAction >= coolDown){
    if((event.key.code == Keyboard::S || event.key.code == Keyboard::W) && !leftSelectorIsVisible){
            selector.setColor(Color(255,255,255,255));
            leftSelectorIsVisible = true;
    }
    else if(event.key.code == Keyboard::S && leftSelectorIsVisible){
        if(selector.getPosition().y == 130){
            selector.setPosition(146.0f , 337.0f);
            spawnY = 360.0f;
                    }
        else if(selector.getPosition().y == 337){
            selector.setPosition(146.0f , 528.0f);
            spawnY = 550.0f;
        }
        else if(selector.getPosition().y == 528){
            selector.setPosition(146.0f , 740.0f);
            spawnY = 760.0f;
        }
    }
    else if(event.key.code == Keyboard::W && leftSelectorIsVisible){
        if(selector.getPosition().y == 337){
            selector.setPosition(146.0f , 130.0f);
            spawnY = 160.0f;
        }
        else if(selector.getPosition().y == 528){
            selector.setPosition(146.0f , 337.0f);
            spawnY = 360.0f;
        }
        else if(selector.getPosition().y == 740){
            selector.setPosition(146.0f , 528.0f);
            spawnY = 550.0f;
        }
    }
    if((event.key.code == Keyboard::Space) && leftSelectorIsVisible){
            selector.setColor(Color(255,255,255,0));
            leftSelectorIsVisible = false;
            randomlyAdder();
            leftPlayerClock.restart();
        }
            
    }
}

void Game::rightSelectorHandle(Event event , Sprite& selector){
    float timeSinceLastAction = rightPlayerClock.getElapsedTime().asSeconds();
    if(timeSinceLastAction >= coolDown){
    if((event.key.code == Keyboard::Up || event.key.code == Keyboard::Down) && !rightSelectorIsVisible){
            selector.setColor(Color(255,255,255,255));
            rightSelectorIsVisible = true;
    }
    else if(event.key.code == Keyboard::Down && rightSelectorIsVisible){
        if(selector.getPosition().y == 130){
            selector.setPosition(71.0f , 337.0f);
            spawnY = 360.0f;
        }
        else if(selector.getPosition().y == 337){
            selector.setPosition(71.0f , 528.0f);
            spawnY=550.0f;
        }
        else if(selector.getPosition().y == 528){
            selector.setPosition(71.0f , 740.0f);
            spawnY = 760.0f;
        }
    }
    else if(event.key.code == Keyboard::Up && rightSelectorIsVisible){
        if(selector.getPosition().y == 337){
            selector.setPosition(71.0f , 130.0f);
            spawnY = 160.0f;
        }
        else if(selector.getPosition().y == 528){
            selector.setPosition(71.0f , 337.0f);
            spawnY = 360.0f;
        }
        else if(selector.getPosition().y == 740){
            selector.setPosition(71.0f , 528.0f);
            spawnY = 550.0f;
        }
    }
    if((event.key.code == Keyboard::Enter) && rightSelectorIsVisible){
            selector.setColor(Color(255,255,255,0));
            rightSelectorIsVisible = false;
            randomlyAdder2();
            rightPlayerClock.restart();
        }
    }

}

void Game::addCharacter(unique_ptr<Character> character) {
    characterVector.push_back(move(character));
}

void Game::addCharacter2(unique_ptr<Character> character2){
    characterVector2.push_back(move(character2));
}

void Game::updateCharacters(float deltaTime) {
    for (auto it=characterVector.begin(); it!=characterVector.end();){
        (*it)->move(deltaTime);
        if((*it)->getPosition().x>1752){
            decreaseRightHealth((*it)->getStrength()/20.0f);
            // cout << "Erased a left character : Winner"<<endl;
            // cout << "Right Health Decresead " << (*it)->getStrength()/20.0f <<endl;
            it=characterVector.erase(it);

        }else if ((*it)->getPosition().x<40){
            it=characterVector.erase(it);
            // cout << "Erased a left character : Loser"<<endl;

        }
        else{
            ++it;
        }

        
    }
}

void Game::updateCharacters2(float deltaTime) {
    for (auto it = characterVector2.begin(); it!=characterVector2.end();){
        (*it)->move(deltaTime);
        if((*it)->getPosition().x<40 ){
            decreaseLeftHealth((*it)->getStrength()/20.0f);
            // cout << "Erased a Right character : Winner"<<endl;
            // cout << "Left Health Decresead " << (*it)->getStrength()/20.0f <<endl;
            it=characterVector2.erase(it);
        }else if ((*it)->getPosition().x>1752){
            it=characterVector2.erase(it);
            // cout << "Erased a Right character : Loser"<<endl;
        }
        else{
            ++it;
        }
}
}

void Game::drawCharacters() {
    for (const auto& character : characterVector) {
        character->draw(window);
    }
}

void Game::drawCharacters2() {
    for (const auto& character2 : characterVector2) {
        character2->draw(window);
    }
}

void Game::randomlyAdder() {
    unique_ptr<Character> character;
    float randValue = static_cast<float>(rand())/RAND_MAX;
    if (randValue < Sheep::getdispProb()){
        character = make_unique<Sheep>(100.0f,spawnY);
    }
    else if(randValue < Sheep::getdispProb()+ Goat::getdispProb()){
        character = make_unique<Goat>(100.0f,spawnY);
    }
    else{
        character = make_unique<Pig>(100.0f,spawnY);
    }
    character->startMoving();
    addCharacter(move(character));
}

void Game::randomlyAdder2() {
    unique_ptr<Character> character2;
    float randValue = static_cast<float>(rand())/RAND_MAX;
    if (randValue < RightSheep::getdispProb()){
        character2 = make_unique<RightSheep>(1500.0f,spawnY);
    }
    else if(randValue < RightSheep::getdispProb()+ RightGoat::getdispProb()){
        character2 = make_unique<RightGoat>(1500.0f,spawnY);
    }
    else{
        character2 = make_unique<RightPig>(1500.0f,spawnY);
    }
    character2->startMoving();
    addCharacter2(move(character2));
}

void Game::checkCollision() { 

    for (size_t i = 0; i < characterVector.size(); ++i) { 
        for (size_t j = 0; j < characterVector2.size(); ++j) {           
            Sprite& sprite1 = characterVector[i]->getSprite();
            Sprite& sprite2 = characterVector2[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 160) {
                if( !characterVector[i]->isAddedToTeamStrength() && !characterVector2[j]->isAddedToTeamStrength()){
                    leftwar1.push_back(characterVector[i].get());
                    rightwar1.push_back(characterVector2[j].get());
                    leftTeamStrength += characterVector[i]->getStrength();
                    rightTeamStrength += characterVector2[j]->getStrength();
                    characterVector[i]->setAddedToTeamStrength(true);
                    characterVector2[j]->setAddedToTeamStrength(true);
                }
                

                if (leftTeamStrength > rightTeamStrength) {
                    for (auto& character : rightwar1) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(true);
                    }
                    for (auto& character : leftwar1) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(true);
                    }
                } else if (rightTeamStrength > leftTeamStrength) {
                    for (auto& character : leftwar1) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(false);
                    }
                    for (auto& character : rightwar1) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(false);
                    }
                } else {
                    for (auto& character : leftwar1) {
                        character->setSpeed(0);
                    }
                    for (auto& character : rightwar1) {
                        character->setSpeed(0);
                    }
                }
            }
        }
    }
}

void Game::checkCollision2() { 

    for (size_t i = 0; i < characterVector.size(); ++i) { 
        for (size_t j = 0; j < characterVector2.size(); ++j) {           
            Sprite& sprite1 = characterVector[i]->getSprite();
            Sprite& sprite2 = characterVector2[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 360) {
                if( !characterVector[i]->isAddedToTeamStrength() && !characterVector2[j]->isAddedToTeamStrength()){
                    leftwar2.push_back(characterVector[i].get());
                    rightwar2.push_back(characterVector2[j].get());
                    leftTeamStrength2 += characterVector[i]->getStrength();
                    rightTeamStrength2 += characterVector2[j]->getStrength();
                    characterVector[i]->setAddedToTeamStrength(true);
                    characterVector2[j]->setAddedToTeamStrength(true);
                }
                

                if (leftTeamStrength2 > rightTeamStrength2) {
                    for (auto& character : rightwar2) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(true);
                    }
                    for (auto& character : leftwar2) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(true);
                    }
                } else if (rightTeamStrength2 > leftTeamStrength2) {
                    for (auto& character : leftwar2) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(false);
                    }
                    for (auto& character : rightwar2) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(false);
                    }
                } else {
                    for (auto& character : leftwar2) {
                        character->setSpeed(0);
                    }
                    for (auto& character : rightwar2) {
                        character->setSpeed(0);
                    }
                }
            }
        }
    }
}

void Game::checkCollision3() { 

    for (size_t i = 0; i < characterVector.size(); ++i) { 
        for (size_t j = 0; j < characterVector2.size(); ++j) {           
            Sprite& sprite1 = characterVector[i]->getSprite();
            Sprite& sprite2 = characterVector2[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 550) {
                if( !characterVector[i]->isAddedToTeamStrength() && !characterVector2[j]->isAddedToTeamStrength()){
                    leftwar3.push_back(characterVector[i].get());
                    rightwar3.push_back(characterVector2[j].get());
                    leftTeamStrength3 += characterVector[i]->getStrength();
                    rightTeamStrength3 += characterVector2[j]->getStrength();
                    characterVector[i]->setAddedToTeamStrength(true);
                    characterVector2[j]->setAddedToTeamStrength(true);
                }
                

                if (leftTeamStrength3 > rightTeamStrength3) {
                    for (auto& character : rightwar3) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(true);
                    }
                    for (auto& character : leftwar3) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(true);
                    }
                } else if (rightTeamStrength3 > leftTeamStrength3) {
                    for (auto& character : leftwar3) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(false);
                    }
                    for (auto& character : rightwar3) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(false);
                    }
                } else {
                    for (auto& character : leftwar3) {
                        character->setSpeed(0);
                    }
                    for (auto& character : rightwar3) {
                        character->setSpeed(0);
                    }
                }
            }
        }
    }
}

void Game::checkCollision4() { 

    for (size_t i = 0; i < characterVector.size(); ++i) { 
        for (size_t j = 0; j < characterVector2.size(); ++j) {           
            Sprite& sprite1 = characterVector[i]->getSprite();
            Sprite& sprite2 = characterVector2[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 760) {
                if( !characterVector[i]->isAddedToTeamStrength() && !characterVector2[j]->isAddedToTeamStrength()){
                    leftwar4.push_back(characterVector[i].get());
                    rightwar4.push_back(characterVector2[j].get());
                    leftTeamStrength4 += characterVector[i]->getStrength();
                    rightTeamStrength4 += characterVector2[j]->getStrength();
                    characterVector[i]->setAddedToTeamStrength(true);
                    characterVector2[j]->setAddedToTeamStrength(true);
                }
                

                if (leftTeamStrength4 > rightTeamStrength4) {
                    for (auto& character : rightwar4) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(true);
                    }
                    for (auto& character : leftwar4) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(true);
                    }
                } else if (rightTeamStrength4 > leftTeamStrength4) {
                    for (auto& character : leftwar4) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(false);
                    }
                    for (auto& character : rightwar4) {
                        character->setSpeed(80.0f);
                        character->setMoveDirection(false);
                    }
                } else {
                    for (auto& character : leftwar4) {
                        character->setSpeed(0);
                    }
                    for (auto& character : rightwar4) {
                        character->setSpeed(0);
                    }
                }
            }
        }
    }
}

void Game::checkTeamCollision() {

    for (size_t i = 0; i < characterVector.size(); ++i) {
        for (size_t j = i + 1; j < characterVector.size(); ++j) {
            Sprite& sprite1 = characterVector[i]->getSprite();
            Sprite& sprite2 = characterVector[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 160) {
                if (!characterVector[j]->isAddedToTeamStrength()) {
                    leftwar1.push_back(characterVector[j].get());
                    leftTeamStrength += characterVector[j]->getStrength();
                    characterVector[j]->setAddedToTeamStrength(true); 
                }
            }

            if (leftTeamStrength > rightTeamStrength) {
                for (auto& character : rightwar1) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
                for (auto& character : leftwar1) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
            } else if (rightTeamStrength > leftTeamStrength) {
                for (auto& character : leftwar1) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
                for (auto& character : rightwar1) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
            } else {
                for (auto& character : leftwar1) {
                    character->setSpeed(0);
                }
                for (auto& character : rightwar1) {
                    character->setSpeed(0);
                }
            }
        }
    }

    for (size_t i = 0; i < characterVector2.size(); ++i) {
        for (size_t j = i + 1; j < characterVector2.size(); ++j) {
            Sprite& sprite1 = characterVector2[i]->getSprite();
            Sprite& sprite2 = characterVector2[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 160 ) {
                if (!characterVector2[j]->isAddedToTeamStrength()) {
                    rightwar1.push_back(characterVector2[j].get());
                    rightTeamStrength += characterVector2[j]->getStrength();
                    characterVector2[j]->setAddedToTeamStrength(true); 
                }
            }

            if (leftTeamStrength > rightTeamStrength) {
                for (auto& character : rightwar1) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
                for (auto& character : leftwar1) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
            } else if (rightTeamStrength > leftTeamStrength) {
                for (auto& character : leftwar1) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
                for (auto& character : rightwar1) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
            } else {
                for (auto& character : leftwar1) {
                    character->setSpeed(0);
                }
                for (auto& character : rightwar1) {
                    character->setSpeed(0);
                }
            }
        }
    }
}

void Game::checkTeamCollision2() {

    for (size_t i = 0; i < characterVector.size(); ++i) {
        for (size_t j = i + 1; j < characterVector.size(); ++j) {
            Sprite& sprite1 = characterVector[i]->getSprite();
            Sprite& sprite2 = characterVector[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 360) {
                if (!characterVector[j]->isAddedToTeamStrength()) {
                    leftwar2.push_back(characterVector[j].get());
                    leftTeamStrength2 += characterVector[j]->getStrength();
                    characterVector[j]->setAddedToTeamStrength(true); 
                }
            }

            if (leftTeamStrength2 > rightTeamStrength2) {
                for (auto& character : rightwar2) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
                for (auto& character : leftwar2) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
            } else if (rightTeamStrength2 > leftTeamStrength2) {
                for (auto& character : leftwar2) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
                for (auto& character : rightwar2) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
            } else {
                for (auto& character : leftwar2) {
                    character->setSpeed(0);
                }
                for (auto& character : rightwar2) {
                    character->setSpeed(0);
                }
            }
        }
    }

    for (size_t i = 0; i < characterVector2.size(); ++i) {
        for (size_t j = i + 1; j < characterVector2.size(); ++j) {
            Sprite& sprite1 = characterVector2[i]->getSprite();
            Sprite& sprite2 = characterVector2[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 360 ) {
                if (!characterVector2[j]->isAddedToTeamStrength()) {
                    rightwar2.push_back(characterVector2[j].get());
                    rightTeamStrength2 += characterVector2[j]->getStrength();
                    characterVector2[j]->setAddedToTeamStrength(true); 
                }
            }

            if (leftTeamStrength2 > rightTeamStrength2) {
                for (auto& character : rightwar2) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
                for (auto& character : leftwar2) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
            } else if (rightTeamStrength2 > leftTeamStrength2) {
                for (auto& character : leftwar2) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
                for (auto& character : rightwar2) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
            } else {
                for (auto& character : leftwar2) {
                    character->setSpeed(0);
                }
                for (auto& character : rightwar2) {
                    character->setSpeed(0);
                }
            }
        }
    }
}

void Game::checkTeamCollision3() {

    for (size_t i = 0; i < characterVector.size(); ++i) {
        for (size_t j = i + 1; j < characterVector.size(); ++j) {
            Sprite& sprite1 = characterVector[i]->getSprite();
            Sprite& sprite2 = characterVector[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 550) {
                if (!characterVector[j]->isAddedToTeamStrength()) {
                    leftwar3.push_back(characterVector[j].get());
                    leftTeamStrength3 += characterVector[j]->getStrength();
                    characterVector[j]->setAddedToTeamStrength(true); 
                }
            }

            if (leftTeamStrength3 > rightTeamStrength3) {
                for (auto& character : rightwar3) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
                for (auto& character : leftwar3) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
            } else if (rightTeamStrength3 > leftTeamStrength3) {
                for (auto& character : leftwar3) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
                for (auto& character : rightwar3) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
            } else {
                for (auto& character : leftwar3) {
                    character->setSpeed(0);
                }
                for (auto& character : rightwar3) {
                    character->setSpeed(0);
                }
            }
        }
    }

    for (size_t i = 0; i < characterVector2.size(); ++i) {
        for (size_t j = i + 1; j < characterVector2.size(); ++j) {
            Sprite& sprite1 = characterVector2[i]->getSprite();
            Sprite& sprite2 = characterVector2[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 550 ) {
                if (!characterVector2[j]->isAddedToTeamStrength()) {
                    rightwar3.push_back(characterVector2[j].get());
                    rightTeamStrength3 += characterVector2[j]->getStrength();
                    characterVector2[j]->setAddedToTeamStrength(true); 
                }
            }

            if (leftTeamStrength3 > rightTeamStrength3) {
                for (auto& character : rightwar3) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
                for (auto& character : leftwar3) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
            } else if (rightTeamStrength3 > leftTeamStrength3) {
                for (auto& character : leftwar3) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
                for (auto& character : rightwar3) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
            } else {
                for (auto& character : leftwar3) {
                    character->setSpeed(0);
                }
                for (auto& character : rightwar3) {
                    character->setSpeed(0);
                }
            }
        }
    }
}

void Game::checkTeamCollision4() {

    for (size_t i = 0; i < characterVector.size(); ++i) {
        for (size_t j = i + 1; j < characterVector.size(); ++j) {
            Sprite& sprite1 = characterVector[i]->getSprite();
            Sprite& sprite2 = characterVector[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 760) {
                if (!characterVector[j]->isAddedToTeamStrength()) {
                    leftwar4.push_back(characterVector[j].get());
                    leftTeamStrength4 += characterVector[j]->getStrength();
                    characterVector[j]->setAddedToTeamStrength(true); 
                }
            }

            if (leftTeamStrength4 > rightTeamStrength4) {
                for (auto& character : rightwar4) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
                for (auto& character : leftwar4) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
            } else if (rightTeamStrength4 > leftTeamStrength4) {
                for (auto& character : leftwar4) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
                for (auto& character : rightwar4) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
            } else {
                for (auto& character : leftwar4) {
                    character->setSpeed(0);
                }
                for (auto& character : rightwar4) {
                    character->setSpeed(0);
                }
            }
        }
    }

    for (size_t i = 0; i < characterVector2.size(); ++i) {
        for (size_t j = i + 1; j < characterVector2.size(); ++j) {
            Sprite& sprite1 = characterVector2[i]->getSprite();
            Sprite& sprite2 = characterVector2[j]->getSprite();

            if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()) && sprite1.getPosition().y == 760 ) {
                if (!characterVector2[j]->isAddedToTeamStrength()) {
                    rightwar4.push_back(characterVector2[j].get());
                    rightTeamStrength4 += characterVector2[j]->getStrength();
                    characterVector2[j]->setAddedToTeamStrength(true); 
                }
            }

            if (leftTeamStrength4 > rightTeamStrength4) {
                for (auto& character : rightwar4) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
                for (auto& character : leftwar4) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(true);
                }
            } else if (rightTeamStrength4 > leftTeamStrength4) {
                for (auto& character : leftwar4) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
                for (auto& character : rightwar4) {
                    character->setSpeed(80.0f);
                    character->setMoveDirection(false);
                }
            } else {
                for (auto& character : leftwar4) {
                    character->setSpeed(0);
                }
                for (auto& character : rightwar4) {
                    character->setSpeed(0);
                }
            }
        }
    }
}


void Game::decreaseRightHealth(float amount){
    rightHealth -=amount;
    if(rightHealth<0) rightHealth =0;
}

void Game::decreaseLeftHealth(float amount){
    leftHealth -=amount;
    if(leftHealth<0) leftHealth =0;
}

void Game::run() {
    Clock clock;
    while (window.isOpen()) {
        Event event;
        rightHealthText.setString(to_string(rightHealth));
        leftHealthText.setString(to_string(leftHealth));

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed){
                leftSelectorHandle(event , leftSelector);
                rightSelectorHandle(event , rightSelector);
            }
            
        }
        float deltaTime = clock.restart().asSeconds();
        checkTeamCollision();
        checkCollision();
        checkTeamCollision2();
        checkCollision2();
        checkTeamCollision3();
        checkCollision3();
        checkTeamCollision4();
        checkCollision4();
        
        if(!GameOver){
            window.clear();
            window.draw(background);
            window.draw(rightSelector);
            window.draw(leftSelector);
            updateCharacters(deltaTime);
            this->drawCharacters();
            updateCharacters2(deltaTime);
            this->drawCharacters2();
            window.draw(border);
            window.draw(rightHealthText);
            window.draw(leftHealthText);
            window.display();
            window.clear();
        }
        
        if(rightHealth == 0 || leftHealth == 0){
            Clock winnerClock;
            GameOver = true;
            winnerClock.restart(); 
            float winnerShowTime = winnerClock.getElapsedTime().asSeconds();
            if(rightHealth == 0){
                window.draw(LeftWinner);              
            }
            else if(leftHealth == 0){
                window.draw(RightWinner);
            }
            window.display();
            if(winnerShowTime > 3){
                break;
            }
        }
    }

    if(rightHealth == 0){
        cout << "Player 1 Won The Game!" << endl;
        window.draw(LeftWinner);              
    }
    else if(leftHealth == 0){
        cout << "Player 2 Won The Game!" << endl;
        window.draw(RightWinner);
    }
}

Game::~Game() {
}

