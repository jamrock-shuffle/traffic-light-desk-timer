#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_AIP31068_I2C.h>
#include <RTClib.h>
#include "time.h"
#include "output.h"
RTC_DS3231 rtc;
DateTime now;

const int buzzerPin = 6;
const int redButtonPin = 12;
const int yellowButtonPin = 11;
const int greenButtonPin = 10;
int redButtonValue;
int yellowButtonValue;
int greenButtonValue;
int mode;

void listenForButtons()
{
    static unsigned long lastPressed;

    if (millis() - lastPressed > 150)
    { // button debouncing
        if (countdownActive)
        {
            if (redButtonValue == LOW)
            {
                if (timesUp)
                {
                    timesUp = false;
                }
                countdownActive = false;
                examTime = 5; // CHANGE
                lastPressed = millis();
            }
        }
        else if (mode == 3)
        { // exam mode setup
            if (redButtonValue == LOW)
            { // start countdown
                countdownActive = true;
                lastPressed = millis();
            }

            if (yellowButtonValue == LOW)
            { // -5min
                examTime = (examTime >= 300) ? (examTime - 300) : 0;
                Serial.print(examTime);
                lastPressed = millis();
            }

            if (greenButtonValue == LOW)
            { // +5min
                examTime = examTime + 300;
                Serial.print(examTime);
                lastPressed = millis();
            }
        }
        else
        {
            if (redButtonValue == LOW)
            { // forces exam mode
                lcd.clear();
                mode = 3;
                if (timesUp)
                    timesUp = false;
                lastPressed = millis();
            }

            if (yellowButtonValue == LOW && mode < 2)
            {                // advances mode when yellow button is pressed,
                lcd.clear(); // rolling over when mode 2 is reached
                mode += 1;
                lastPressed = millis();
            }
            else if (yellowButtonValue == LOW)
            {
                lcd.clear();
                mode = 0;
                lastPressed = millis();
            }

            if (greenButtonValue == LOW)
            { // forces mode 1
                lcd.clear();
                mode = 1;
                stopwatchActive = !stopwatchActive; // toggles stopwatch
                lastPressed = millis();
            }
        }
    }
}

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    pinMode(redButtonPin, INPUT_PULLUP);
    pinMode(yellowButtonPin, INPUT_PULLUP);
    pinMode(greenButtonPin, INPUT_PULLUP);
    pinMode(buzzerPin, OUTPUT);

    lcd.init();
    mode = 0;

    if (!rtc.begin())
    {
        lcd.clear();
        lcd.print("RTC Error!");
        while (1)
            ;
    }

    now = rtc.now();

    displayMode(mode);
}

void loop()
{
    /* COLOUR RGB VALUES
    red: 255, 0, 0
    yellow: 255, 25, 0
    green: 0, 50, 0
    */
    now = rtc.now();

    redButtonValue = digitalRead(redButtonPin); // links variable colourButtonValue to pin
    yellowButtonValue = digitalRead(yellowButtonPin);
    greenButtonValue = digitalRead(greenButtonPin);

    listenForButtons();
    stopwatch();
    countdown();
    displayMode(mode);
}