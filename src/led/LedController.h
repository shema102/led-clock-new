#ifndef LED_CLOCK_NEW_LEDCONTROLLER_H
#define LED_CLOCK_NEW_LEDCONTROLLER_H

#include <cstdint>
#include <FastLED.h>

class LedController {
private:
    static const int NUM_LEDS = 4 * 7 * 2 + 2; // 4 numbers of 7 segments, each segment has 2 leds, plus 2 dots
    CRGB leds[NUM_LEDS]{};

    CRGB currentColor = CRGB::Red;

public:
    void drawTime(uint8_t hour, uint8_t minute, uint8_t second);

    void setColor(CRGB color);

    void setColor();

    LedController();
    ~LedController() = default;
    LedController(const LedController &other) = delete;
    LedController(LedController &&other) = delete;
};


#endif //LED_CLOCK_NEW_LEDCONTROLLER_H
