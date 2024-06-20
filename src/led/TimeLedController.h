#ifndef LED_CLOCK_NEW_LEDCONTROLLER_H
#define LED_CLOCK_NEW_LEDCONTROLLER_H

#include <cstdint>
#include <FastLED.h>

enum class DigitSegments: uint8_t;

/*
 * Leds in the clock are arranged in non-conventional way:
 *     C
 *  D     B
 *     A
 *  E     G
 *     F
 *
 * Dots in the middle are arranged:
 *     2
 *
 *     1
 *
 * Numbers in the clock are arranged in the following way:
 * HH : MM
 *
 * Digits are wired from left to right, 2 dots are last.
 * Each segment has 2 leds.
 *
 */

class TimeLedController {
    static constexpr int NUM_LEDS = 4 * 7 * 2 + 2; // 4 numbers of 7 segments, each segment has 2 leds, plus 2 dots
    CRGB leds[NUM_LEDS]{};

    CRGB currentColor = CRGB::Red;

    uint8_t brightness = 255;

    void setSegmentDigit(uint8_t number, uint8_t digit);

    void setHours(uint8_t hour);
    void setMinutes(uint8_t minute);
    void setDot(bool enabled);

    CRGB colorForBrightness();

    static DigitSegments getSegmentForNumber(uint8_t number);

public:
    void drawTime(uint8_t hour, uint8_t minute, uint8_t second);

    void setColor(CRGB color);

    void setBrightness(uint8_t brightness);

    void DEBUG_drawNumber(uint8_t number);

    TimeLedController();
    ~TimeLedController() = default;
    TimeLedController(const TimeLedController &other) = delete;
    TimeLedController(TimeLedController &&other) = delete;
};


#endif //LED_CLOCK_NEW_LEDCONTROLLER_H
