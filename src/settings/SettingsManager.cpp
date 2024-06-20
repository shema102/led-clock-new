#include "SettingsManager.h"

SettingsManager::SettingsManager() {
    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("Failed to init EEPROM\n");
    }

    Settings loadedSettings{};

    EEPROM.get(EEPROM_ADDRESS, loadedSettings);

    if (loadedSettings.magic_number != MAGIC_NUMBER) {
        loadedSettings = DEFAULT_SETTINGS;
    }

    this->currentSettings = loadedSettings;

    saveSettings();
}

SettingsManager::~SettingsManager() {
    EEPROM.end();
}

void SettingsManager::saveSettings() const {
    Serial.println(this->currentSettings.magic_number);
    EEPROM.put(EEPROM_ADDRESS, this->currentSettings);

    EEPROM.commit();
}

CRGB SettingsManager::getColor() const {
    return {currentSettings.color_r, currentSettings.color_g, currentSettings.color_b};
}

void SettingsManager::saveColor(const CRGB color) {
    currentSettings.color_r = color.r;
    currentSettings.color_g = color.g;
    currentSettings.color_b = color.b;

    saveSettings();
}

void SettingsManager::clearSettings() {
    EEPROM.put(EEPROM_ADDRESS, DEFAULT_SETTINGS);
}

uint8_t SettingsManager::getBrightness() const {
    return currentSettings.brightness;
}

void SettingsManager::saveBrightness(uint8_t brightness) {
    currentSettings.brightness = brightness;

    saveSettings();
}

bool SettingsManager::isDotsEnabled() const {
    return !(currentSettings.settings_flags & 0x01);
}

void SettingsManager::setDotsEnabled(bool enabled) {
    if (enabled) {
        currentSettings.settings_flags &= ~0x01;
    } else {
        currentSettings.settings_flags |= 0x01;
    }

    saveSettings();
}
