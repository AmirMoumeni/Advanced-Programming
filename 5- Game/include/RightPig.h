#ifndef RightPig_H
#define RightPig_H

#include "Character.h"

class RightPig : public Character{
private:
    static constexpr float displayProb = 0.2f;
public:
    RightPig(float x, float y);
    ~RightPig() = default;
    static float getdispProb() {return displayProb;}

};

#endif