#include "Feeder2D1P.h"
#include "Arduino.h"

Feeder2D1P::Feeder2D1P(int dPin1, int dPin2, int _pPin) {

    dPins[0] = dPin1;
    dPins[1] = dPin2;
    pPin = _pPin;

    pinMode(dPins[0], OUTPUT);
    pinMode(dPins[1], OUTPUT);
    pinMode(pPin, OUTPUT);
    value = 0;
    direction = 0;
}

void Feeder2D1P::setValue(int value) {
    Serial.println("dir " + String(this->direction));
    this->value = constrain(value, 0, 255);
    analogWrite(pPin, 255 - this->value);
    Serial.println("pin " + String(pPin) + ": " + String(255 - this->value));
}

void Feeder2D1P::changeValueBy(int value) {
    this->value += constrain(value, 0, 255);
    this->setValue(this->value);
}

void Feeder2D1P::setDirection(int direction) {
    this->direction = constrain(direction, 0, 1);
    this->setValue(0);
    digitalWrite(dPins[this->direction], HIGH);
    digitalWrite(dPins[this->direction ^ 1], LOW);
    Serial.println("pin " + String(dPins[this->direction]) + ": HIGH");
    Serial.println("pin " + String(dPins[this->direction ^ 1]) + ": LOW");
    Serial.println("dir updated: " + String(this->direction));
}

void Feeder2D1P::toggleDirection() {
    setDirection(1 - this->direction);
}
