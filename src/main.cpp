#include <Arduino.h>
#include <FastLED.h>

#include "rtcTime.h"

const int NUM_LEDS = 4 * 7 * 2 + 2; // 4 numbers of 7 segments, each segment has 2 leds, plus 2 dots
CRGB leds[NUM_LEDS];

void drawAllRed();
void drawAllBlue();

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

    FastLED.addLeds<NEOPIXEL, 14>(leds, NUM_LEDS);
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

    drawAllRed();

    delay(20);

    drawAllBlue();

    delay(20);
}

void drawAllRed() {
    for (auto & led : leds) {
        led = CRGB::Red;
    }
    FastLED.show();
}

void drawAllBlue() {
    for (auto & led : leds) {
        led = CRGB::Blue;
    }
    FastLED.show();
}
