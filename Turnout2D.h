#pragma once

#include "Turnout.h"

class Turnout2D : public Turnout {
public:
    Turnout2D(int dPin1, int dPin2);

    void setDirection(int direction);

    void toggleDirection();

private:
    int dPins[2];
    int direction;
};