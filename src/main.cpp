#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_AIP31068_I2C.h>
#include <RTClib.h>
#include "time.h"
#include "input.h"
#include "output.h"
RTC_DS3231 rtc;
DateTime now;
state prevState = state::clock;
state currentState = state::clock;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    Wire.setWireTimeout(3000, true);

    buttonSetup();

    delay(100);
    lcd.init();

    if (!rtc.begin())
    {
        lcd.clear();
        lcd.print("RTC Error!");
        while (1);
    }

    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Run this the first time you upload the code!
    now = rtc.now();

    displayMode(currentState);
}


void loop()
{
    
    /* COLOUR RGB VALUES
    red: 255, 0, 0
    yellow: 255, 25, 0
    green: 0, 50, 0 */
    
    
    now = rtc.now();

    readButtons();
    stateMachine();
    stopwatch();
    countdown();

    if (currentState != prevState) 
    {
        lcd.clear();
        displayMode(currentState);
        prevState = currentState;
    }
    else if (now.second() != prevSecond)
    {
        prevSecond = now.second();
        displayMode(currentState);
    }
}