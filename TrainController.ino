#include "LayoutManager.h"
#include "utils.h"

// reserved buffer size for the inputString:
#define INPUT_BUFFER_SIZE 500
#define MAX_TOKEN_NUM 10

// 4番ピンは周波数を変えられないので、ON／OFFスイッチとして活用する
LayoutManager manager(4);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

/**
 * PWMの周波数を変更する (490Hz -> 31000Hz)。
 * Arduino MEGAは5つのタイマーを持ち、それぞれが対応するピンのPWM周波数を制御している。
 *
 *  - timer 0 (controls pin 13, 4)
 *  - timer 1 (controls pin 12, 11)
 *  - timer 2 (controls pin 10, 9)
 *  - timer 3 (controls pin 5, 3, 2)
 *  - timer 4 (controls pin 8, 7, 6)
 *
 *  なお、timer 0 はArduino全体の動作に影響する特別なタイマーなので変更しない。
 *  参考: https://forum.arduino.cc/index.php?topic=72092.0
 */
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

    inputString.reserve(INPUT_BUFFER_SIZE);

    configure_pwm_freq();
}

void loop() {
    // print the string when a newline arrives:
    if (stringComplete) {

        String splitstring[MAX_TOKEN_NUM] = {"\0"};                        //分割された文字列を格納する配列
        size_t arraysize = SIZE_OF_ARRAY(splitstring);          //配列の要素数
        char delimiter = ' ';                                   //区切り文字
        int index = split(splitstring, arraysize, inputString, delimiter);
        Serial.println("index = " + String(index));
        for (int i = 0; i < index; i++) {
            Serial.println(splitstring[i]);
        }

        String command = splitstring[0];

        // config <config-json> Feeder/Turnoutの初期設定を行う
        if (command == "config") {
            manager.configure();
        }

        if (! manager.isConfigured) {
            Serial.println("Not configured");
        }

        // f <feeder-id> v <value>  スピードを設定する
        // f <feeder-id> d          方向を反転
        if (command == "f") {
            int number = splitstring[1].toInt();
            String subcommand = splitstring[2];
            if (subcommand == "v") {
                int value = splitstring[3].toInt();
                Serial.println("feeder " + String(number) + " set value " + String(value));
                manager.getFeeder(number).setValue(value);
            }
            if (subcommand == "c") {
                int value = splitstring[3].toInt();
                Serial.println("feeder " + String(number) + " change value by " + String(value));
                manager.getFeeder(number).changeValueBy(value);
            }
            if (subcommand == "d") {
                Serial.println("feeder " + String(number) + " toggled");
                manager.getFeeder(number).toggleDirection();
            }
        }

        // t <turnout-id>   ポイントを切り替える
        if (command == "t") {
            int number = splitstring[1].toInt();
            Serial.println("turnout " + String(number) + " toggled");
            manager.getTurnout(number).toggleDirection();
        }

        // clear the string:
        inputString = "";
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
        inputString += inChar;
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '\n') {
            stringComplete = true;
        }
    }
}


