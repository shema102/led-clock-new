#include "TimeLedController.h"

// least significant bit is A
enum class DigitSegments: uint8_t
{
    zero  = 0b01111110,
    one   = 0b01000010,
    two   = 0b00110111,
    three = 0b01100111,
    four  = 0b01001011,
    five  = 0b01101101,
    six   = 0b01111101,
    seven = 0b01000110,
    eight = 0b01111111,
    nine  = 0b01101111,
    nothing = 0b00000000
};

TimeLedController::TimeLedController()
{
    FastLED.addLeds<NEOPIXEL, 14>(leds, NUM_LEDS);
}

void TimeLedController::drawTime(const uint8_t hour, const uint8_t minute, const uint8_t second)
{
    this->setHours(hour);
    this->setMinutes(minute);
    this->setDot(second % 2 == 0);

    FastLED.show();
}

void TimeLedController::setColor(const CRGB color)
{
    this->currentColor = color;
}

void TimeLedController::setBrightness(uint8_t brightness)
{
    this->brightness = brightness;
}

void TimeLedController::DEBUG_drawNumber(const uint8_t number)
{
    this->setSegmentDigit(number, 0);
    this->setSegmentDigit(number, 3);
    this->setDot(number == 0);


    FastLED.show();
}

void TimeLedController::setHours(const uint8_t hour)
{
    uint8_t firstDigit = hour / 10;
    uint8_t secondDigit = hour % 10;

    this->setSegmentDigit(firstDigit, 0);
    this->setSegmentDigit(secondDigit, 1);
}

void TimeLedController::setMinutes(const uint8_t minute)
{
    uint8_t firstDigit = minute / 10;
    uint8_t secondDigit = minute % 10;

    this->setSegmentDigit(firstDigit, 2);
    this->setSegmentDigit(secondDigit, 3);
}

void TimeLedController::setDot(const bool enabled)
{
    leds[4 * 7 * 2 + 1] = enabled ? this->currentColor : CRGB::Black;
    leds[4 * 7 * 2] = enabled ? this->currentColor : CRGB::Black;
}

// return color with brightness
CRGB TimeLedController::colorForBrightness()
{
    CRGB color = this->currentColor;

    color.subtractFromRGB(225 - brightness);

    return color;
}

void TimeLedController::setSegmentDigit(const uint8_t number, const uint8_t digit)
{
    const int offset = digit * 7 * 2;

    const auto segmentMask = static_cast<uint8_t>(getSegmentForNumber(number));

    const auto color = colorForBrightness();

    for (int i = 0; i < 7; i++)
    {
        leds[offset + i * 2] = (segmentMask & (1 << i)) ? color : CRGB::Black;
        leds[offset + i * 2 + 1] = (segmentMask & (1 << i)) ? color : CRGB::Black;
    }
}

DigitSegments TimeLedController::getSegmentForNumber(const uint8_t number)
{
    switch (number)
    {
    case 0:
        return DigitSegments::zero;
    case 1:
        return DigitSegments::one;
    case 2:
        return DigitSegments::two;
    case 3:
        return DigitSegments::three;
    case 4:
        return DigitSegments::four;
    case 5:
        return DigitSegments::five;
    case 6:
        return DigitSegments::six;
    case 7:
        return DigitSegments::seven;
    case 8:
        return DigitSegments::eight;
    case 9:
        return DigitSegments::nine;
    default:
        return DigitSegments::nothing;
    }
}
