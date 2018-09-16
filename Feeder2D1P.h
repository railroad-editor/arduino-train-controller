#pragma once

#include "Feeder.h"

class Feeder2D1P : public Feeder {
public:
    Feeder2D1P(int dPin1, int dPin2, int pPin);

    void setValue(int value);

    void changeValueBy(int value);

    void setDirection(int direction);

    void toggleDirection();

private:
    int dPins[2];
    int pPin;
    int value;
    int direction;
};
