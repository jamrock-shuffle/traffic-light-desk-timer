#include "output.h"
#include "time.h"

bool buzzerOn = false;
int shortBeeps = 0;
LiquidCrystal_AIP31068_I2C lcd(0x3E,16,2);

const char* months[] = {"ERR", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

void alarm() {
    static unsigned long lastFlipped0, lastFlipped1;
    if (millis() - lastFlipped1 > 650) {
        if (shortBeeps < 4) 
        {
            if (millis() - lastFlipped0 > 50) 
            {
                lastFlipped0 = millis();
                buzzerOn = !buzzerOn;
                if (buzzerOn)
                {
                    tone(buzzerPin, 2000);
                }
                else if (!buzzerOn)
                {
                    noTone(buzzerPin);
                    shortBeeps++;
                }
            }
        } else
        {
            shortBeeps = 0;
            lastFlipped1 = millis();
        }    
    }
}

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

void displayToday() {
    int hours = timeToday/3600;
    int minutes = (timeToday%3600) / 60;
    int seconds = timeToday%60;

    if (hours < 10) lcd.print('0');
    lcd.print(hours);
    lcd.print(':');
    if (minutes < 10) lcd.print('0');
    lcd.print(minutes);
    lcd.print(':');
    if (seconds < 10) lcd.print('0');
    lcd.print(seconds);
}

void displayCountdown() {
    int hours = examTime/3600;
    int minutes = (examTime%3600) / 60;
    int seconds = examTime%60;

    if (timesUp) {
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("TIME'S UP!");
        alarm();
    } else {
        lcd.setCursor(3,0);
        lcd.print("EXAM  MODE");
        noTone(buzzerPin);
        // examTime = 5400;
    }

    lcd.setCursor(0,1);
    lcd.print("    ");
    if (hours < 10) lcd.print('0');
    lcd.print(hours);
    lcd.print(':');
    if (minutes < 10) lcd.print('0');
    lcd.print(minutes);
    lcd.print(':');
    if (seconds < 10) lcd.print('0');
    lcd.print(seconds);
    lcd.print("   ");
}

void displayMode(int mode) {
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
            displayToday();
            break;

        case 3:
            displayCountdown();
            break;
    }
}