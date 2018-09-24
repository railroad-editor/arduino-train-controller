#include "Switcher2D.h"
#include "Arduino.h"

/**
 *
 * @param pin1
 * @param pin2
 */
Switcher2D::Switcher2D(int dPin1, int dPin2) {

    dPins[0] = dPin1;
    dPins[1] = dPin2;

    pinMode(dPins[0], OUTPUT);
    pinMode(dPins[1], OUTPUT);
    direction = 0;
}

void Switcher2D::setDirection(int direction) {
    this->direction = constrain(direction, 0, 1);
    Serial.println("dir:" + String(this->direction));
    digitalWrite(dPins[this->direction], HIGH);
    Serial.println("pin " + String(dPins[this->direction]) + "HIGH");
    delay(15);
    digitalWrite(dPins[this->direction], LOW);
    Serial.println("pin " + String(dPins[this->direction]) + "LOW");
}

void Switcher2D::toggleDirection() {
    this->setDirection(this->direction ^ 1);
}
