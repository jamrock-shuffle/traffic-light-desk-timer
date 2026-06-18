#include <Arduino.h>

const int redButtonPin = 12;
const int yellowButtonPin = 11;
const int greenButtonPin = 10;
int redButtonValue;
int yellowButtonValue;
int greenButtonValue;
int mode;

void cycleMode() { /* advances mode when yellow button is pressed, 
    rolling over when mode 2 is reached
    TO-DO: make this conditional on device not being in [EXAM MODE] - [EXAM MODE] should 
    temporarily override all other buttons' functions*/
    if (yellowButtonValue == LOW && mode < 2) {
        mode += 1;
    } else if (yellowButtonValue == LOW) {
        mode = 0;
    }
}

void listenForExamMode() { // forces [EXAM MODE] when red button is pressed
    if (redButtonValue == LOW) {
        mode = 3;
    }
}

void listenForActiveFocusMode() { /* forces [ACTIVE FOCUS] when green button is pressed 
    TO-DO: start stopwatch at the same time*/
    if (greenButtonValue == LOW) {
        mode = 1;
    }
}

void displayMode() {
    switch (mode) {
        case 0:
            Serial.println("[CURRENT TIME]");
            delay(250);
            break;

        case 1:
            Serial.println("[ACTIVE FOCUS]"); // time accumulated this session (essentially a stopwatch)
            delay(250);
            break;

        case 2: 
            Serial.println("[TIME TODAY]"); // time accumulated today
            delay(250);
            break;

        case 3:
            Serial.println("[EXAM MODE]"); // countdown timer
            delay(250);
            break;
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(redButtonPin, INPUT_PULLUP);
    pinMode(yellowButtonPin, INPUT_PULLUP);
    pinMode(greenButtonPin, INPUT_PULLUP);
    mode = 0;
}

void loop() {
    /* COLOUR RGB VALUES
    red: 255, 0, 0
    yellow: 255, 25, 0
    green: 0, 50, 0
    */
    redButtonValue = digitalRead(redButtonPin); // links variable colourButtonValue to pin
    yellowButtonValue = digitalRead(yellowButtonPin);
    greenButtonValue = digitalRead(greenButtonPin);
    cycleMode();
    listenForExamMode();
    listenForActiveFocusMode();
    displayMode();
}