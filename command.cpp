#include <Arduino.h>
#include "LayoutManager.h"
#include "utils.h"

LayoutManager manager(4);

void executeCommand(std::vector<String> tokens) {

    String command = tokens[0];
    int numTokens = tokens.size();

    // config <config-json> PowerPack/Turnoutの初期設定を行う
    if (command == "config") {
        manager.configure(tokens[1]);
    }

    if (!manager.isConfigured) {
        Serial.println("Not configured");
    }

    // p <power-pack-id> v <value>      電流の大きさを設定する
    // p <power-pack-id> c <value>      電流の大きさを相対値で設定する
    // p <power-pack-id> d <direction>  電流の方向を設定する
    // p <power-pack-id> d              電流の方向をトグルする
    if (command == "p") {
        int id = tokens[1].toInt() - 1;
        if (id < 0) {
            Serial.println("[Error] Invalid PowerPack ID: " + (id + 1));
            return;
        }
        String subcommand = tokens[2];
        if (subcommand == "v") {
            int value = tokens[3].toInt();
            Serial.println("PowerPack " + String(id) + " set value " + String(value));
            manager.getPowerPack(id).setValue(value);
        }
        if (subcommand == "c") {
            int value = tokens[3].toInt();
            Serial.println("PowerPack " + String(id) + " change value by " + String(value));
            manager.getPowerPack(id).changeValueBy(value);
        }
        if (subcommand == "d") {
            if (numTokens == 3) {
                manager.getPowerPack(id).toggleDirection();
                Serial.println("PowerPack " + String(id) + " direction toggled");
            }
            if (numTokens == 4) {
                int direction = tokens[3].toInt();
                manager.getPowerPack(id).setDirection(direction);
                Serial.println("PowerPack " + String(id) + " set direction to " + String(direction));
            }
        }
    }

    // s <switcher-id> <switcher-direction> スイッチの方向を設定する
    // s <switcher-id>                  スイッチの方向をトグルする
    if (command == "s") {
        int id = tokens[1].toInt() - 1;
        if (id < 0) {
            Serial.println("[Error] Invalid Switcher ID: " + (id + 1));
            return;
        }
        String subcommand = tokens[2];
        if (subcommand == "d") {
            if (numTokens == 3) {
                manager.getSwitcher(id).toggleDirection();
                Serial.println("Switcher " + String(id) + " direction toggled");
            }
            if (numTokens == 4) {
                int direction = tokens[3].toInt();
                manager.getSwitcher(id).setDirection(direction);
                Serial.println("Switcher " + String(id) + " set direction to " + String(direction));
            }
        }
    }
}
