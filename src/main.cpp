#include <Arduino.h>
#include <led/TimeLedController.h>

#include "rtc/RTCManager.h"
#include "settings/SettingsManager.h"

TimeLedController timeLedController{};

void setup() {
    Serial.begin(9600);
    Serial.println("Starting...");
}

void loop() {
    DateTime now = RTCManager::getInstance().getTime();

    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    const CRGB currentColor = SettingsManager::getInstance().getColor();
    timeLedController.setColor(currentColor);

    timeLedController.drawTime(now.hour(), now.minute(), now.second());

    delay(1000);
}
