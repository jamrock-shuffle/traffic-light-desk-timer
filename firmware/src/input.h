#ifndef INPUT_H
#define INPUT_H

extern const int buzzerPin;
extern const int redButtonPin;
extern const int yellowButtonPin;
extern const int greenButtonPin;

extern int redButtonValue;
extern int yellowButtonValue;
extern int greenButtonValue;

enum class state {
    clock,
    currentSession,
    timeToday,
    examSetup,
    examRunning
};

extern state currentState;

void buttonSetup();
void readButtons();
void stateMachine();

#endif