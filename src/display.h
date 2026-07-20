#ifndef DISPLAY_H
#define DISPLAY_H

#include <RTClib.h>
#include <LiquidCrystal_AIP31068_I2C.h>

void displayClock();
void displaySession();
void displayToday(); 
void displayCountdown();
void displayMode(int mode);
extern LiquidCrystal_AIP31068_I2C lcd;

#endif