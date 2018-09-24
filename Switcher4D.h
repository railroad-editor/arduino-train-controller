#pragma once

#include "Switcher.h"

class Switcher4D : public Switcher {
public:
    Switcher4D(int dPin1, int dPin2, int dPin3, int dPin4);

    void setDirection(int direction);

    void toggleDirection();

private:
    int dPins[4];
    int direction;
};