#include "LayoutManager.h"
#include "Feeder1D1P.h"
#include "Turnout2D.h"
#include "Arduino.h"

// 仮の設定値。本来はサーバーに問い合わせて設定を取得する。
String LAYOUT_CONFIG = "{\"powerPacks\": [ {\"pPin\": 5, \"dPin\": 32 } ], \"switchers\": [ {\"dPins\": [28,29] } ] }";


LayoutManager::LayoutManager(int _dPin) {
    dPin = _dPin;

    pinMode(dPin, OUTPUT);
    digitalWrite(dPin, LOW);
}

void LayoutManager::configure() {

    Serial.println("Configuration start");

    StaticJsonBuffer<300> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(LAYOUT_CONFIG);
    if (!root.success()) {
        Serial.println("parseObject() failed");
        return;
    }
    JsonArray &feeders = root["powerPacks"];
    JsonArray &turnouts = root["switchers"];

    Serial.println("PowerPacks:");
    for (JsonArray::iterator it = feeders.begin(); it != feeders.end(); ++it) {
        // *it contains the JsonVariant which can be casted as usuals
        JsonObject &feeder = *it;
        int dPin = feeder["dPin"];
        int pPin = feeder["pPin"];
        Serial.println("(" + String(dPin) + ", " + String(pPin) + ")");;;
        this->feeders.push_back(new Feeder1D1P(dPin, pPin));
    }

    Serial.println("Switchers:");
    for (JsonArray::iterator it = turnouts.begin(); it != turnouts.end(); ++it) {
        // *it contains the JsonVariant which can be casted as usuals
        JsonObject &turnout = *it;
        int pin1 = turnout["dPins"][0];
        int pin2 = turnout["dPins"][1];
        Serial.println("(" + String(pin1) + ", " + String(pin2) + ")");
        this->turnouts.push_back(new Turnout2D(pin1, pin2));
    }

    digitalWrite(dPin, HIGH);
    isConfigured = true;
}

Feeder &LayoutManager::getFeeder(int id) {
    return *feeders.at(id);
}

Turnout &LayoutManager::getTurnout(int id) {
    return *turnouts.at(id);
}
