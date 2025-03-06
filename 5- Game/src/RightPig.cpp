#include "RightPig.h"

RightPig::RightPig(float x, float y)
    : Character(x, y, "Files/blackPig.png", 210.0f,100.0f) {
        setMoveDirection(false);
}