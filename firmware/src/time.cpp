#include "time.h"

bool stopwatchActive = false;
int timeSession = 0;
int timeToday = 0;
int prevSecond = -1;
bool countdownActive = false;
bool timesUp = false;
int examTime = 5;

void stopwatch() {
    static int prevStopwatchSecond;
    if (stopwatchActive) {
        if (now.second() != prevStopwatchSecond) {
            timeSession++;
            timeToday++;
            prevStopwatchSecond = now.second();
        }
    } else timeSession = 0;
}

void countdown() {
    static int prevCountdownSecond;
    if (countdownActive) {
        if (now.second() != prevCountdownSecond && examTime > 0) {
            examTime--;
            timeToday++;
            prevCountdownSecond = now.second();
        }
        if (examTime == 0) {
            countdownActive = false;
            timesUp = true;
            examTime = 5;
        }
    }
}