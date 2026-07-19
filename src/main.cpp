#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_AIP31068_I2C.h>
#include <RTClib.h>
LiquidCrystal_AIP31068_I2C lcd(0x3E,16,2);
RTC_DS3231 rtc;
DateTime now;

const int redButtonPin = 12;
const int yellowButtonPin = 11;
const int greenButtonPin = 10;
int redButtonValue;
int yellowButtonValue;
int greenButtonValue;
int mode;

const char* months[] = {"ERR", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

void displayMode() {
    switch (mode) {
        case 0:
        lcd.setCursor(3,1);
            if(now.day() < 10) lcd.print('0'); // print day
            lcd.print(now.day(), DEC);
            lcd.print(' ');
            
            lcd.print(months[now.month()]); // print month
            lcd.print(' ');

            lcd.print(now.year() % 100, DEC); // print year
            
            lcd.setCursor(5,0); // print time
            if(now.hour() < 10) lcd.print('0');
            lcd.print(now.hour(), DEC);
            lcd.print(':');
            if(now.minute() < 10) lcd.print('0');
            lcd.print(now.minute(), DEC);
            break;

        case 1:
            lcd.setCursor(0,0);
            lcd.print("current session"); // time accumulated this session (essentially a stopwatch)
            lcd.setCursor(4,1);
            lcd.print("00:00:00");
            break;

        case 2: 
            lcd.setCursor(3,0);
            lcd.print("time today"); // time accumulated today
            lcd.setCursor(4,1);
            lcd.print("00:00:00");
            break;

        case 3:
            lcd.setCursor(2,0);
            lcd.print("[EXAM MODE]"); // countdown timer
            lcd.setCursor(4,1);
            lcd.print("00:00:00");
            break;
    }
}

void cycleMode() { /* advances mode when yellow button is pressed, 
    rolling over when mode 2 is reached
    TO-DO: make this conditional on device not being in [EXAM MODE] - [EXAM MODE] should 
    temporarily override all other buttons' functions*/
    if (yellowButtonValue == LOW && mode < 2) {
        lcd.clear();
        mode += 1;
        delay(200);
    } else if (yellowButtonValue == LOW) {
        lcd.clear();
        mode = 0;
        delay(200);
    }
}

void listenForExamMode() { // forces [EXAM MODE] when red button is pressed
    if (redButtonValue == LOW) {
        lcd.clear();
        mode = 3;
        delay(200);
    }
}

void listenForActiveFocusMode() { /* forces [ACTIVE FOCUS] when green button is pressed 
    TO-DO: start stopwatch at the same time*/
    if (greenButtonValue == LOW) {
        lcd.clear();
        mode = 1;
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
    mode = 0;

    if (!rtc.begin()) {
    lcd.clear();
    lcd.print("RTC Error!");
    while (1);
    }

    now = rtc.now();

    displayMode();
}

void loop() {
    /* COLOUR RGB VALUES
    red: 255, 0, 0
    yellow: 255, 25, 0
    green: 0, 50, 0
    */
    now = rtc.now();
    
    redButtonValue = digitalRead(redButtonPin); // links variable colourButtonValue to pin
    yellowButtonValue = digitalRead(yellowButtonPin);
    greenButtonValue = digitalRead(greenButtonPin);

    cycleMode();
    listenForExamMode();
    listenForActiveFocusMode();
    displayMode();
}