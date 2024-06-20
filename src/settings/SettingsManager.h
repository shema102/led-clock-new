#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <cstdint>
#include <FastLED.h>
#include <EEPROM.h>

struct Settings
{
    uint16_t magic_number;
    uint8_t brightness;
    uint8_t color_r;
    uint8_t color_g;
    uint8_t color_b;

    uint8_t animation_type;

    uint8_t settings_flags;
};

class SettingsManager {
    static constexpr int EEPROM_SIZE = sizeof(Settings);
    static constexpr int EEPROM_ADDRESS = 0;
    static constexpr uint16_t MAGIC_NUMBER = 0x1234;

    Settings currentSettings{};

    void saveSettings() const;

    static SettingsManager instance;

    SettingsManager();
    ~SettingsManager();

public:
    static SettingsManager& getInstance()
    {
        static SettingsManager instance;

        return instance;
    }

    CRGB getColor() const
    {
        return {currentSettings.color_r, currentSettings.color_g, currentSettings.color_b};
    }

    void saveColor(const CRGB color)
    {
        currentSettings.color_r = color.r;
        currentSettings.color_g = color.g;
        currentSettings.color_b = color.b;

        saveSettings();
    }

    SettingsManager(const SettingsManager &other) = delete;
    SettingsManager(SettingsManager &&other) = delete;
    void operator=(const SettingsManager &other) = delete;
};



#endif //SETTINGSMANAGER_H
