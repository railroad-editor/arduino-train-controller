#pragma once

#include "Switcher.h"

class Switcher2D : public Switcher {
public:
    Switcher2D(int dPin1, int dPin2);

    void setDirection(int direction);

    void toggleDirection();

private:
    int dPins[2];
    int direction;
};