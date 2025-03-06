#ifndef RightGoat_H
#define RightGoat_H

#include "Character.h"

class RightGoat : public Character{
private:
    static constexpr float displayProb = 0.3f;
public:
    RightGoat(float x, float y);
    ~RightGoat() = default;
    static float getdispProb() {return displayProb;}

};

#endif