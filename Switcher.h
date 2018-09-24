#pragma once

class Switcher {
public:
    virtual void setDirection(int direction) = 0;

    virtual void toggleDirection() = 0;
};
