#include <Arduino.h>
#include <Preferences.h>      //SETTINGS
#include "ble.h"
#include "settings.h"


//Creo objeto preferences para almacenar y tomar settings desde la FLASH
Preferences preferences;
bool read_flash_fail;

void readSettingsFromFlash(){

  //Lectura de parametros de los dispositivos BLE.
  for(uint8_t i=0;i<=(NUM_OF_BLE_DEVS-1);i++){
    preferences.begin(SENSOR_SETTINGS_NAMES[i].c_str(), false);
    bleDev[i].macStr = preferences.getString(MAC, SENSOR_DEFAULT_MAC);
    bleDev[i].enabled = preferences.getBool(ENABLED, DEFAULT_ENABLED);
    preferences.end();
  }

}

void saveDefaultSettings(){

  //SENSOR SETTINGS
  for(uint8_t i=0;i<NUM_OF_BLE_DEVS;i++){
    
    preferences.begin(SENSOR_SETTINGS_NAMES[i].c_str(), false);
    
    preferences.putString(MAC, SENSOR_DEFAULT_MAC);
    bleDev[i].macStr = SENSOR_DEFAULT_MAC;
    
    preferences.putBool(ENABLED, DEFAULT_ENABLED);
    bleDev[i].enabled = DEFAULT_ENABLED;
    
    preferences.end();
    
  }

}
