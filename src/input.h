#ifndef INPUT_H
#define INPUT_H

extern const int buzzerPin;
extern const int redButtonPin;
extern const int yellowButtonPin;
extern const int greenButtonPin;
extern int mode;


void buttonSetup();
void readButtons();
void listenForButtons();

#endif