#include "time.h"
#include "output.h"
#include "input.h"
#include <LiquidCrystal_AIP31068_I2C.h>

const int buzzerPin = 6;
const int redButtonPin = 12;
const int yellowButtonPin = 11;
const int greenButtonPin = 10;

int redButtonValue;
int yellowButtonValue;
int greenButtonValue;

/*const int buzzerPin = 6;
const int redButtonPin = 12;
const int yellowButtonPin = 11;
const int greenButtonPin = 10;*/

void buttonSetup() {
    pinMode(redButtonPin, INPUT_PULLUP);
    pinMode(yellowButtonPin, INPUT_PULLUP);
    pinMode(greenButtonPin, INPUT_PULLUP);
    pinMode(buzzerPin, OUTPUT);
}

void readButtons() {
    redButtonValue = digitalRead(redButtonPin); // links variable colourButtonValue to pin
    yellowButtonValue = digitalRead(yellowButtonPin);
    greenButtonValue = digitalRead(greenButtonPin);
}

void stateMachine() {
    static unsigned long lastPressed;

    if (millis() - lastPressed > 150) // button debouncing
    {
        switch (currentState) {
            case state::clock:
                if (redButtonValue == LOW)
                    {
                        currentState = state::examSetup;
                        lastPressed = millis();
                        break;
                    }
                else if (yellowButtonValue == LOW)
                {
                    lastPressed = millis();
                    if (stopwatchActive)
                    {
                        currentState = state::currentSession;
                        break;
                    }
                    else
                    {
                        currentState = state::timeToday;
                        break;
                    }
                }
                else if (greenButtonValue == LOW)
                {
                    lastPressed = millis();
                    currentState = state::currentSession;
                    stopwatchActive = true;
                    break;
                }

            case state::currentSession:
                if (yellowButtonValue == LOW)
                {
                    currentState = state::timeToday;
                    lastPressed = millis();
                    break;
                }
                else if (greenButtonValue == LOW)
                {
                    currentState = state::timeToday;
                    stopwatchActive = false;
                    lastPressed = millis();
                    break;
                }

            case state::timeToday:
                if (yellowButtonValue == LOW)
                {
                    currentState = state::clock;
                    lastPressed = millis();
                    break;
                }
                else if (greenButtonValue == LOW)
                {
                    lastPressed = millis();
                    if (!stopwatchActive)
                    {
                        currentState = state::currentSession;
                        stopwatchActive = true;
                        break;
                    }
                    else
                    {
                        stopwatchActive = false;
                        break;
                    }
                }

            case state::examSetup:
                if (redButtonValue == LOW)
                {
                    countdownActive = true;
                    currentState = state::examRunning;
                    lastPressed = millis();
                    break;
                }
                else if (yellowButtonValue == LOW)
                {
                    examTime-=5;
                    lastPressed = millis();
                    break;
                }
                else if (greenButtonValue == LOW)
                {
                    examTime+=5;
                    lastPressed = millis();
                    break;
                }
            
            case state::examRunning:
                break;
        }
    }
}