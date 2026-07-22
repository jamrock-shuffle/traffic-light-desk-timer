#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_AIP31068_I2C.h>
#include <RTClib.h>
#include "time.h"
#include "input.h"
#include "output.h"
RTC_DS3231 rtc;
DateTime now;
int mode = 0;


void setup()
{
    Serial.begin(9600);
    Wire.begin();

    buttonSetup();

    lcd.init();

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

    readButtons();
    listenForButtons();
    stopwatch();
    countdown();
    displayMode(mode);
}