#include "Turnout2D.h"
#include "Arduino.h"

/**
 *
 * @param pin1
 * @param pin2
 */
Turnout2D::Turnout2D(int dPin1, int dPin2) {

    dPins[0] = dPin1;
    dPins[1] = dPin2;

    pinMode(dPins[0], OUTPUT);
    pinMode(dPins[1], OUTPUT);
    direction = 0;
}

void Turnout2D::setDirection(int direction) {
    // Serial.println("dir updated raw" + String(direction));
    this->direction = constrain(direction, 0, 1);
    Serial.println("dir:" + String(this->direction));
    digitalWrite(dPins[this->direction], HIGH);
    Serial.println("pin " + String(dPins[this->direction]) + "HIGH");
    delay(15);
    digitalWrite(dPins[this->direction], LOW);
    Serial.println("pin " + String(dPins[this->direction]) + "LOW");
}

void Turnout2D::toggleDirection() {
    this->setDirection(this->direction ^ 1);
}
