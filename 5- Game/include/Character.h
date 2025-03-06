#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Character {
protected:
    Sprite sprite;
    Texture texture;
    float speed;
    float strength;
    bool isMoving;
    bool movingRight;
    // float health;
    Vector2f startingPoint;
    bool addedToTeamStrength;
    bool removedStrenght;
public:
    Character(float x, float y, const string& texturePath, float speed, float strength);
    virtual ~Character() = default;

    virtual void move(float deltaTime);
    virtual void draw(RenderWindow& window);
    void setMoveDirection (bool isRight);
    float getStrength() const {return strength;}
    void setStrength(float value){strength = value;}
    void increaseStrength(float value){strength += value;}
    Vector2f getPosition() const {return sprite.getPosition();}
    Sprite& getSprite()  {return sprite;}
    void startMoving();
    void stopMoving();
    bool getRightDir();
    void setSpeed(float newSpeed){speed = newSpeed;}

    Vector2f getStartingPos() const{return startingPoint;}
    bool isAddedToTeamStrength() const { return addedToTeamStrength; }
    void setAddedToTeamStrength(bool value) { addedToTeamStrength = value; }
    bool isRemovedToTeamStrength() const { return removedStrenght; }
    void setRemoved(bool value) {removedStrenght = value; }
    
};

#endif
