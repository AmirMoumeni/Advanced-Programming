#ifndef Pig_H
#define Pig_H

#include "Character.h"

class Pig : public Character{
private:
static constexpr float displayProb = 0.2f;
public:
    Pig(float x, float y);
    ~Pig() = default;
    static float getdispProb() {return displayProb;}

};
#endif