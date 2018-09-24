#pragma once

#include "PowerPack.h"

class PowerPack1D1P : public PowerPack {
public:
    PowerPack1D1P(int dPin, int pPin);

    void setValue(int value);

    void changeValueBy(int value);

    void setDirection(int direction);

    void toggleDirection();

private:
    int dPin;
    int pPin;
    int value;
    int direction;
};
