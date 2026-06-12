#include <Arduino.h>

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int buttonPin = 2;
int buttonValue;
int state;

void setup() {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    state = 0;
}

void loop() {
    /* COLOUR RGB VALUES
    red: 255, 0, 0
    yellow: 255, 25, 0
    green: 0, 50, 0
    */
    buttonValue = digitalRead(buttonPin); // links variable buttonValue (ON/OFF) to pin
    if (buttonValue == LOW && state < 3) { // state advances upon button press
        state += 1;
        delay(500);
    } else if (buttonValue == LOW) {
        state = 0;
        delay (500);
    }

    if (state == 0) {
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    } else if (state == 1) {
        analogWrite(redPin, 255);
        analogWrite(greenPin, 25);
        analogWrite(bluePin, 0);
    } else if (state == 2) {
        analogWrite(redPin, 0);
        analogWrite(greenPin, 50);
        analogWrite(bluePin, 0);
    } else if (state == 3) {
        analogWrite(redPin, 0);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 255);
    }
}