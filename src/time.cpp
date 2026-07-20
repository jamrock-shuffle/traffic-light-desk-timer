#include "time.h"

bool stopwatchActive = false;
int timeSession = 0;
int timeToday = 0;
int prevSecond = -1;
bool countdownActive = false;
bool timesUp = false;
int examTime = 5400;

void stopwatch() {
    if (stopwatchActive) {
        if (now.second() != prevSecond) {
            timeSession++;
            timeToday++;
            prevSecond = now.second();
        }
    } else timeSession = 0;
}

void countdown() {
    if (countdownActive) {
        if (now.second() != prevSecond && examTime > 0) {
            examTime--;
            prevSecond = now.second();
        }
        if (examTime == 0) {
            countdownActive = false;
            timesUp = true;
            examTime = 5400;
        }
    }
}