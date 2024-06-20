#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <cstdint>
#include <FastLED.h>
#include <EEPROM.h>

struct Settings {
    uint16_t magic_number;
    uint8_t brightness;
    uint8_t color_r;
    uint8_t color_g;
    uint8_t color_b;

    uint8_t animation_type; // reserved for future use

    uint8_t settings_flags; // bit 0 - disable dots, bit 1 - 7 reserved for future use
};

class SettingsManager {
    static constexpr int EEPROM_SIZE = sizeof(Settings);
    static constexpr int EEPROM_ADDRESS = 0;
    static constexpr uint16_t MAGIC_NUMBER = 0x1234;
    constexpr static const Settings DEFAULT_SETTINGS = {
            .magic_number = MAGIC_NUMBER,
            .brightness = 255,
            .color_r = 255,
            .color_g = 255,
            .color_b = 255,
            .animation_type = 0,
            .settings_flags = 0
    };

    Settings currentSettings{};

    void saveSettings() const;

    static SettingsManager instance;

    SettingsManager();

    ~SettingsManager();

public:
    static SettingsManager &getInstance() {
        static SettingsManager manager;

        return manager;
    }

    CRGB getColor() const;

    void saveColor(CRGB color);

    uint8_t getBrightness() const;

    void saveBrightness(uint8_t brightness);

    bool isDotsEnabled() const;

    void setDotsEnabled(bool enabled);

    static void clearSettings();

    SettingsManager(const SettingsManager &other) = delete;

    SettingsManager(SettingsManager &&other) = delete;

    void operator=(const SettingsManager &other) = delete;
};


#endif //SETTINGSMANAGER_H
