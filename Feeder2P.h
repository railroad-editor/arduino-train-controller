#pragma once

#include "Feeder.h"

class Feeder2P : public Feeder {
public:
    Feeder2P(int pin1, int pin2);

    void setValue(int value);

    void changeValueBy(int value);

    void setDirection(int direction);

    void toggleDirection();

private:
    int pins[2];
    int value;
    int direction;
};
