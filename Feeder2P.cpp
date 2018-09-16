#include "Feeder2P.h"
#include "Arduino.h"

Feeder2P::Feeder2P(int pin1, int pin2) {

    pins[0] = pin1;
    pins[1] = pin2;

    pinMode(pins[0], OUTPUT);
    pinMode(pins[1], OUTPUT);
    value = 0;
    direction = 0;
}

void Feeder2P::setValue(int value) {
    Serial.println("dir " + String(this->direction));
    this->value = constrain(value, 0, 255);
    analogWrite(pins[this->direction], 255 - this->value);
    Serial.println("pin " + String(pins[this->direction]) + ": " + String(255 - this->value));
    analogWrite(pins[this->direction ^ 1], 255);
    Serial.println("pin " + String(pins[this->direction ^ 1]) + ": " + String(255));
}

void Feeder2P::changeValueBy(int value) {
    this->value += constrain(value, 0, 255);
    this->setValue(this->value);
}

void Feeder2P::setDirection(int direction) {
    Serial.println("dir updated raw" + String(direction));
    this->direction = constrain(direction, 0, 1);
    Serial.println("dir updated " + String(this->direction));
    this->setValue(0);
}

void Feeder2P::toggleDirection() {
    setDirection(1 - this->direction);
}
