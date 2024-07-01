#ifndef SETTINGS
#define SETTINGS

#include <Preferences.h>      //SETTINGS
#include <ble.h>

extern Preferences preferences;
extern bool read_flash_fail;

//Global Settings

//Default values
const bool DEFAULT_ENABLED = true;

//Constant strings
const char GLOBAL_SETTINGS_NAME[]="settings";
const char MAC[]="mac";
const char ENABLED[]="enabled";
const String SENSOR_SETTINGS_NAMES[NUM_OF_BLE_DEVS]= {
    "sensor_0",
    "sensor_1",
};

const String SENSOR_DEFAULT_MAC = "11:11:11:11:11:11";

void readSettingsFromFlash();

void saveDefaultSettings();

#endif