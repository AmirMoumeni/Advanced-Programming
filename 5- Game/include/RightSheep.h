#ifndef RightSHEEP_H
#define RightSHEEP_H

#include "Character.h"

class RightSheep : public Character {
private:
     static constexpr float displayProb = 0.5f;
public:
    RightSheep(float x, float y);
    ~RightSheep() = default;
    static float getdispProb() {return displayProb;}

};

#endif
