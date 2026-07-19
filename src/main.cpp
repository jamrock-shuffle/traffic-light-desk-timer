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
bool stopwatchActive = false;
int timeSession = 0;
int timeToday = 0;
int prevSecond = -1;

const char* months[] = {"ERR", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

void displayClock() {
    lcd.setCursor(3,1);
    
    if(now.day() < 10) lcd.print('0'); // print day
    lcd.print(now.day());
    lcd.print(' ');
            
    lcd.print(months[now.month()]); // print month
    lcd.print(' ');

    lcd.print(now.year() % 100); // print year
            
    lcd.setCursor(5,0); // print time
    if(now.hour() < 10) lcd.print('0');
    lcd.print(now.hour());
    lcd.print(':');
    if(now.minute() < 10) lcd.print('0');
    lcd.print(now.minute());
}

void displaySession() {
    int hours = timeSession/3600;
    int minutes = (timeSession%3600) / 60;
    int seconds = timeSession%60;

    if (hours < 10) lcd.print('0');
    lcd.print(hours);
    lcd.print(':');
    if (minutes < 10) lcd.print('0');
    lcd.print(minutes);
    lcd.print(':');
    if (seconds < 10) lcd.print('0');
    lcd.print(seconds);
}

void stopwatch() {
    if (stopwatchActive) {
        if (now.second() != prevSecond) {
            timeSession++;
            timeToday++;
            prevSecond = now.second();
        }
    } else timeSession = 0;
}

void displayMode() {
    switch (mode) {
        case 0:
            displayClock();
            break;

        case 1:
            lcd.setCursor(0,0);
            lcd.print("current session"); // time accumulated this session (essentially a stopwatch)
            lcd.setCursor(4,1);
            displaySession();
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

void listenForButtons() {
    static unsigned long lastPressed;

    if (millis() - lastPressed > 150) { // button debouncing

        if (redButtonValue == LOW) { // forces exam mode
            lcd.clear();
            mode = 3;
            lastPressed = millis();
        }

        if (yellowButtonValue == LOW && mode < 2) { // advances mode when yellow button is pressed,
            lcd.clear(); // rolling over when mode 2 is reached
            mode += 1;
            lastPressed = millis();
        } else if (yellowButtonValue == LOW) {
            lcd.clear();
            mode = 0;
            lastPressed = millis();
        }

        if (greenButtonValue == LOW) { // forces mode 1
            lcd.clear();
            mode = 1;
            stopwatchActive = !stopwatchActive; // toggles stopwatch
            lastPressed = millis();
        }
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

    listenForButtons();
    stopwatch();
    displayMode();
}