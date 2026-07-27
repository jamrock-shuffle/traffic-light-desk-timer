#ifndef OUTPUT_H
#define OUTPUT_H

#include <RTClib.h>
#include <LiquidCrystal_AIP31068_I2C.h>
#include "input.h"

void alarm();
void displayClock();
void displaySession();
void displayToday(); 
void displayCountdown();
void displayMode(state currentState);
extern LiquidCrystal_AIP31068_I2C lcd;
extern const int buzzerPin;

#endif