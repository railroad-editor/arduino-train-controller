#pragma once

class Turnout {
public:
    virtual void setDirection(int direction) = 0;

    virtual void toggleDirection() = 0;
};
