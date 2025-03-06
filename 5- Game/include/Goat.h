#ifndef Goat_H
#define Goat_H

#include "Character.h"

class Goat : public Character{
private:
    static constexpr float displayProb = 0.3f;
public:
    Goat(float x, float y);
    ~Goat() = default;
    static float getdispProb() {return displayProb;}

};

#endif
