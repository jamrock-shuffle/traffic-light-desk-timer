#ifndef TIME_H
#define TIME_H

#include <RTClib.h>

extern bool stopwatchActive;
extern int timeSession;
extern int timeToday;
extern int prevSecond;
extern bool countdownActive;
extern bool timesUp;
extern int examTime;

extern DateTime now;

void stopwatch();
void countdown();

#endif