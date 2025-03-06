#include "RightGoat.h"

RightGoat::RightGoat(float x, float y)
    : Character(x, y, "Files/GoatBlue.png", 160.0f,100.0f) {
        setMoveDirection(false);
}
