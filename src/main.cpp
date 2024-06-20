#include <Arduino.h>
#include <led/TimeLedController.h>

#include "rtc/rtcTime.h"

TimeLedController timeLedController{};

void setup() {
    Serial.begin(9600);
    Serial.println("Starting...");

    if (!setupTime()) {
        Serial.println("Couldn't find RTC");
    } else {
        Serial.println("RTC found");
    }

    DateTime now = DateTime(F(__DATE__), F(__TIME__));

    if (!setCurrentTime(now)) {
        Serial.println("Couldn't set time");
    } else {
        Serial.println("Time set");
    }

}

void loop() {
    DateTime now = getCurrentTime();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    timeLedController.drawTime(now.hour(), now.minute(), now.second());

    delay(1000);
}
