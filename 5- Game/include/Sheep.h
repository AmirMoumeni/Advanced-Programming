#ifndef SHEEP_H
#define SHEEP_H

#include "Character.h"

class Sheep : public Character {
private:
     static constexpr float displayProb = 0.5f;
public:
    Sheep(float x, float y);
    ~Sheep() = default;
    static float getdispProb() {return displayProb;}

};

#endif
