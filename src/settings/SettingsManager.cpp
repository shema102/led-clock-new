#include "SettingsManager.h"


void SettingsManager::saveSettings() const
{
    EEPROM.put(EEPROM_ADDRESS, currentSettings);
}

SettingsManager::SettingsManager()
{
    Serial.write("Creating settings manager\n");
    if (!EEPROM.begin(EEPROM_SIZE))
    {
        Serial.write("Failed to init EEPROM\n");
    }

    Settings loadedSettings{};

    EEPROM.get(EEPROM_ADDRESS, loadedSettings);

    if (loadedSettings.magic_number != MAGIC_NUMBER)
    {
        loadedSettings = {
            .magic_number = MAGIC_NUMBER,
            .brightness = 255,
            .color_r = 255,
            .color_g = 255,
            .color_b = 255,
            .animation_type = 0,
            .settings_flags = 0
        };
    }

    this->currentSettings = loadedSettings;

    saveSettings();
}

SettingsManager::~SettingsManager()
{
    EEPROM.end();
}
