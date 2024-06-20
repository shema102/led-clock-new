#ifndef LED_CLOCK_NEW_RTCMANAGER_H
#define LED_CLOCK_NEW_RTCMANAGER_H

#include "RTClib.h"

class RTCManager {
    RTC_DS1307 rtc;

    RTCManager();

public:
    static RTCManager &getInstance() {
        static RTCManager manager;

        return manager;
    }

    void setTime(const DateTime &time);

    DateTime getTime();

    RTCManager(const RTCManager &other) = delete;

    RTCManager(RTCManager &&other) = delete;

    void operator=(const RTCManager &other) = delete;
};


#endif //LED_CLOCK_NEW_RTCMANAGER_H
