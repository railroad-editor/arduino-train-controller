#include "utils.h"
#include "command.h"

// reserved buffer size for the inputString:
#define INPUT_BUFFER_SIZE 500
#define MAX_TOKEN_NUM 10

String inputSting = "";         // a string to hold incoming data
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

    inputSting.reserve(INPUT_BUFFER_SIZE);

    configure_pwm_freq();
}


void loop() {
    // print the string when a newline arrives:
    if (stringComplete) {

        char delimiter = ' ';
        std::vector<String> tokens = split(inputSting, delimiter, MAX_TOKEN_NUM);
        int numTokens = tokens.size();
        Serial.println("numTokens = " + String(numTokens));
        Serial.print("tokens: ");
        for (int i = 0; i < numTokens; i++) {
            Serial.print(tokens[i]);
            Serial.print(", ");
        }
        Serial.println();

        executeCommand(tokens);

        // clear the string:
        inputSting = "";
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
        inputSting += inChar;
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '\n') {
            stringComplete = true;
        }
    }
}


