#include "LedController.h"

LedController::LedController() {
    FastLED.addLeds<NEOPIXEL, 14>(leds, NUM_LEDS);
}


void LedController::drawTime(uint8_t hour, uint8_t minute, uint8_t second) {

}

