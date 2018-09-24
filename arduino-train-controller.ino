#include "LayoutManager.h"
#include "utils.h"
#include <Arduino.h>

// reserved buffer size for the inputString:
#define INPUT_BUFFER_SIZE 500
#define MAX_TOKEN_NUM 10

LayoutManager manager(4);

String inputSing = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void configure_pwm_freq() {
    int myEraser = 7;
    TCCR1B &= ~myEraser;
    TCCR2B &= ~myEraser;
    TCCR3B &= ~myEraser;
    TCCR4B &= ~myEraser;

    int myPrescaler = 1;         // this could be a number in [1 , 6]. In this case, 3 corresponds in binary to 011.
    TCCR1B |= myPrescaler;
    TCCR2B |= myPrescaler;
    TCCR3B |= myPrescaler;
    TCCR4B |= myPrescaler;
}


void setup() {
    // initialize serial:
    Serial.begin(9600);

    inputSing.reserve(INPUT_BUFFER_SIZE);

    configure_pwm_freq();
}

void loop() {
    // print the string when a newline arrives:
    if (stringComplete) {

        String tokens[MAX_TOKEN_NUM] = {"\0"};
        size_t arraysize = SIZE_OF_ARRAY(tokens);
        char delimiter = ' ';
        int numTokens = split(tokens, arraysize, inputSing, delimiter);
        Serial.println("numTokens = " + String(numTokens));
        for (int i = 0; i < numTokens; i++) {
            Serial.println(tokens[i]);
        }

        String command = tokens[0];

        // config <config-json> PowerPack/Turnoutの初期設定を行う
        if (command == "config") {
            manager.configure();
        }

        if (! manager.isConfigured) {
            Serial.println("Not configured");
        }

        // p <power-pack-id> v <value>      電流の大きさを設定する
        // p <power-pack-id> c <value>      電流の大きさを相対値で設定する
        // p <power-pack-id> d <direction>  電流の方向を設定する
        // p <power-pack-id> d              電流の方向をトグルする
        // TODO: 実装
        if (command == "p") {
            int id = tokens[1].toInt();
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
                    manager.getSwitcher(id).toggleDirection();
                    Serial.println("PowerPack " + String(id) + "direction toggled");
                }
                if (numTokens == 4) {
                    int direction = tokens[3].toInt();
                    manager.getSwitcher(id).setDirection(direction);
                    Serial.println("PowerPack " + String(id) + "set direction to " + String(direction));
                }
                Serial.println("PowerPack " + String(id) + "direction toggled");
                manager.getPowerPack(id).toggleDirection();
            }
        }

        // s <switcher-id> <switcher-state> スイッチの状態を設定する
        // s <switcher-id>                  スイッチの状態をトグルする
        if (command == "s") {
            int id = tokens[1].toInt();
            if (numTokens == 2) {
                manager.getSwitcher(id).toggleDirection();
                Serial.println("Switcher " + String(id) + "state toggled");
            }
            if (numTokens == 3) {
                int state = tokens[2].toInt();
                manager.getSwitcher(id).setDirection(state);
                Serial.println("Switcher " + String(id) + "set state to" + String(state));
            }
        }

        // clear the string:
        inputSing = "";
        stringComplete = false;
    }
}



/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char) Serial.read();
        // add it to the inputString:
        inputSing += inChar;
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '\n') {
            stringComplete = true;
        }
    }
}


