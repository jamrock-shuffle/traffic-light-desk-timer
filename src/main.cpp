#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_AIP31068_I2C.h>
LiquidCrystal_AIP31068_I2C lcd(0x3E,16,2);

const int redButtonPin = 12;
const int yellowButtonPin = 11;
const int greenButtonPin = 10;
int redButtonValue;
int yellowButtonValue;
int greenButtonValue;
int mode;

void displayMode() {
    lcd.clear();
    lcd.setCursor(0,0);
    switch (mode) {
        case 0:
            lcd.print("[CURRENT TIME]");
            break;

        case 1:
            lcd.print("[ACTIVE FOCUS]"); // time accumulated this session (essentially a stopwatch)
            break;

        case 2: 
            lcd.print("[TIME TODAY]"); // time accumulated today
            break;

        case 3:
            lcd.print("[EXAM MODE]"); // countdown timer
            break;
    }
}

void cycleMode() { /* advances mode when yellow button is pressed, 
    rolling over when mode 2 is reached
    TO-DO: make this conditional on device not being in [EXAM MODE] - [EXAM MODE] should 
    temporarily override all other buttons' functions*/
    if (yellowButtonValue == LOW && mode < 2) {
        mode += 1;
        displayMode();
        delay(200);
    } else if (yellowButtonValue == LOW) {
        mode = 0;
        displayMode();
        delay(200);
    }
}

void listenForExamMode() { // forces [EXAM MODE] when red button is pressed
    if (redButtonValue == LOW) {
        mode = 3;
        displayMode();
        delay(200);
    }
}

void listenForActiveFocusMode() { /* forces [ACTIVE FOCUS] when green button is pressed 
    TO-DO: start stopwatch at the same time*/
    if (greenButtonValue == LOW) {
        mode = 1;
        displayMode();
        delay(200);
    }
}


void setup() {
    Serial.begin(9600);
    Wire.begin();

    pinMode(redButtonPin, INPUT_PULLUP);
    pinMode(yellowButtonPin, INPUT_PULLUP);
    pinMode(greenButtonPin, INPUT_PULLUP);

    lcd.init();
    lcd.setCursor(0, 0);
    mode = 0;
    lcd.print("[CURRENT TIME]");
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
}