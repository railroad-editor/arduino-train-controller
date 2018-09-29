#include "LayoutManager.h"
#include "PowerPack1D1P.h"
#include "Switcher2D.h"
#include "Switcher4D.h"
#include <Arduino.h>

// 開発用の仮の設定。
// TODO: Productionでは削除
String LAYOUT_CONFIG = R"({"powerPacks":[{"pPin":5,"dPin":34}],"switchers":[{"dPins":[28,29]},{"dPins":[30,31,32,33]}]})";


/**
 *
 * @param _dPin 電源ピン
 */
LayoutManager::LayoutManager(int _dPin) {
    dPin = _dPin;

    pinMode(dPin, OUTPUT);
    digitalWrite(dPin, LOW);
}

void LayoutManager::configure(String configJson) {

    Serial.println("Configuration start");

    // 開発用の仮の設定。
    // TODO: Productionでは削除
    if (configJson.length() == 0) {
        configJson = LAYOUT_CONFIG;
        Serial.println("Using default configuration");
    }

    StaticJsonBuffer<300> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(configJson);
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
        this->powerPacks.push_back(new PowerPack1D1P(dPin, pPin));
    }

    Serial.println("Switchers:");
    for (JsonArray::iterator it = turnouts.begin(); it != turnouts.end(); ++it) {
        // *it contains the JsonVariant which can be casted as usuals
        JsonObject &turnout = *it;
        int pin1 = turnout["dPins"][0];
        int pin2 = turnout["dPins"][1];

        if (turnout["dPins"].size() == 2) {
            Serial.println("(" + String(pin1) + ", " + String(pin2) + ")");
            this->switchers.push_back(new Switcher2D(pin1, pin2));
        }
        if (turnout["dPins"].size() == 4) {
            int pin3 = turnout["dPins"][2];
            int pin4 = turnout["dPins"][3];
            Serial.println("(" + String(pin1) + ", " + String(pin2) + ")");
            this->switchers.push_back(new Switcher4D(pin1, pin2, pin3, pin4));
        }
    }

    digitalWrite(dPin, HIGH);
    isConfigured = true;
}

PowerPack &LayoutManager::getPowerPack(int id) {
    return *powerPacks.at(id);
}

Switcher &LayoutManager::getSwitcher(int id) {
    return *switchers.at(id);
}
