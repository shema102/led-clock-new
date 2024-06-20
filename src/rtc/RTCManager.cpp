#include "RTCManager.h"

RTCManager::RTCManager() {
    if (!this->rtc.begin()) {
        Serial.println("Couldn't find RTC");

        while (true);
    }
}

void RTCManager::setTime(const DateTime &time) {
    this->rtc.adjust(time);
}

DateTime RTCManager::getTime() {
    return this->rtc.now();
}
