#include "rtcTime.h"

RTC_DS1307 rtc;

bool setupTime() {
    return rtc.begin();
}

bool setCurrentTime(const DateTime& time) {
    rtc.adjust(time);
    return true;
}

DateTime getCurrentTime() {
    return rtc.now();
}
