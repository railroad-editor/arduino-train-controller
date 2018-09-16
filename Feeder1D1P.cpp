#include "Feeder1D1P.h"
#include "Arduino.h"

Feeder1D1P::Feeder1D1P(int _dPin, int _pPin) {

    dPin = _dPin;
    pPin = _pPin;

    pinMode(dPin, OUTPUT);
    pinMode(pPin, OUTPUT);
    value = 0;
    analogWrite(pPin, 255);
    direction = 0;
}

void Feeder1D1P::setValue(int value) {
    Serial.println("dir " + String(this->direction));
    this->value = constrain(value, 0, 255);
    analogWrite(pPin, 255 - this->value);
    Serial.println("pin " + String(pPin) + ": " + String(255 - this->value));
}

void Feeder1D1P::changeValueBy(int value) {
    this->value += constrain(value, 0, 255);
    this->setValue(this->value);
}

void Feeder1D1P::setDirection(int direction) {
    this->direction = constrain(direction, 0, 1);
    this->setValue(0);
    digitalWrite(dPin, this->direction);
    Serial.println("pin " + String(dPin) + ": " + String(this->direction));
    Serial.println("dir updated: " + String(this->direction));
}

void Feeder1D1P::toggleDirection() {
    setDirection(1 - this->direction);
}
