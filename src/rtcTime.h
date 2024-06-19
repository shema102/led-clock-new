#ifndef LED_CLOCK_NEW_RTCTIME_H
#define LED_CLOCK_NEW_RTCTIME_H


#include <RTClib.h>

bool setupTime();

bool setCurrentTime(const DateTime& time);

DateTime getCurrentTime();

#endif //LED_CLOCK_NEW_RTCTIME_H
