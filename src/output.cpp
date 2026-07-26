#include "output.h"
#include "time.h"

bool buzzerOn = false;
int shortBeeps = 0;
static unsigned long lastFlippedBuzzer, lastSetEnded;
LiquidCrystal_AIP31068_I2C lcd(0x3E,16,2);

const char* months[] = {"ERR", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

void alarm() {
    if (millis() - lastSetEnded > 650) { // wait 650ms between sets of 4 beeps
        if (shortBeeps < 4) 
        {
            if (millis() - lastFlippedBuzzer > 50) 
            {
                lastFlippedBuzzer = millis();
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
            lastSetEnded = millis();
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
        lcd.setCursor(3,0);
        lcd.print("TIME'S UP!");
        alarm();
    } else {
        lcd.setCursor(3,0);
        lcd.print("EXAM  MODE");
        noTone(buzzerPin);
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

void displayMode(state currentState) {
    switch (currentState) 
    {
        case state::clock:
            displayClock();
            break;
        
        case state::currentSession:
            lcd.setCursor(0,0);
            lcd.print("current session");
            lcd.setCursor(4,1);
            displaySession();
            break;
        
        case state::timeToday:
            lcd.setCursor(3,0);
            lcd.print("time today");
            lcd.setCursor(4,1);
            displayToday();
            break;
        
        case state::examSetup:
            displayCountdown();
            break;

        case state::examRunning:
            displayCountdown();
            break;
    }
}