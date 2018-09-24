#pragma once

class PowerPack {
public:
    virtual void setValue(int value) = 0;

    virtual void changeValueBy(int value) = 0;

    virtual void setDirection(int direction) = 0;

    virtual void toggleDirection() = 0;
};
