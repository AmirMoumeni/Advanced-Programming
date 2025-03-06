#include "Character.h"

Character::Character(float x, float y, const string& texturePath,float strength, float speed)
    : speed(speed),strength(strength), isMoving(false) , movingRight(true) , addedToTeamStrength(false) , removedStrenght(false) {
    if (!texture.loadFromFile(texturePath)) {
        cerr << "Error loading texture from " << texturePath << "!" << endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(0.8f, 0.8f); 
    if(startingPoint == Vector2f (0.0f,0.0f)){
        startingPoint = sprite.getPosition();
    }
}
void Character::setMoveDirection (bool isRight){
    movingRight = isRight;
}

void Character::move(float deltaTime) {
    if (isMoving) {
        float moveDirection = movingRight ?1.0f:-1.0f;
        sprite.move(speed * deltaTime* moveDirection, 0.0f); 
    }
}

// void Character::decreaseHealth(float amount){
//     health -=amount;
//     if(health<0) health =0;
// }

void Character::draw(RenderWindow& window) {
    window.draw(sprite);
}

void Character::startMoving() {
    isMoving = true;
}

void Character::stopMoving() {
    isMoving = false;
}

bool Character::getRightDir(){
    return movingRight;
}
