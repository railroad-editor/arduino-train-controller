#include "Switcher4D.h"
#include "Arduino.h"

int PIN_STATES[3][4] = {
        { HIGH, LOW, HIGH, LOW },
        { LOW, HIGH, HIGH, LOW },
        { HIGH, LOW, LOW, HIGH }
};


Switcher4D::Switcher4D(int dPin1, int dPin2, int dPin3, int dPin4) {

    dPins[0] = dPin1;
    dPins[1] = dPin2;
    dPins[2] = dPin3;
    dPins[3] = dPin4;

    for (int i = 0 ; i < 4 ; i++) {
        pinMode(dPins[i], OUTPUT);
    }
    direction = 0;
}

void Switcher4D::setDirection(int direction) {
    Serial.println("Switcher4D::setDirection(" + String(direction) + ")");
    this->direction = constrain(direction, 0, 2);

    for (int i = 0 ; i < 3 ; ++i) {
        digitalWrite(dPins[i], PIN_STATES[this->direction][i]);
        Serial.println("pin " + String(dPins[this->direction]) + ": " + PIN_STATES[this->direction][i]);
    }

    delay(15);

    for (int i = 0 ; i < 3 ; ++i) {
        digitalWrite(dPins[i], LOW);
    }
}

void Switcher4D::toggleDirection() {
    int nextDirection;
    if (this->direction >= 2) {
        nextDirection = 0;
    } else {
        nextDirection = this->direction + 1;
    }
    this->setDirection(nextDirection);
}
