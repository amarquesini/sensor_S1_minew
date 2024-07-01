#ifndef BLE
#define BLE

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "BLEBeacon.h"
#include "BLEEddystoneTLM.h"
#include "BLEEddystoneURL.h"

//BLE ACCELEROMETER
extern uint8_t cServiceData[100];
extern BLEScan *pBLEScan;
extern const uint8_t SCAN_TIME;
extern uint16_t beconUUID;
#define ENDIAN_CHANGE_U16(x) ((((x)&0xFF00) >> 8) + (((x)&0xFF) << 8))

enum bleDevice{
  SENSOR_1=0,
  SENSOR_2=1,
};

const uint8_t NUM_OF_BLE_DEVS=2;

typedef struct{

  //ROM
  bool enabled = true;
    
  //RAM
  float tempF = 0;
  float humF = 0;
  int8_t batteryLevel = 0;
  String macStr = "FF:FF:FF:FF:FF:FF";

}BleType;

extern BleType bleDev[NUM_OF_BLE_DEVS];

class MyAdvertisedDeviceCallbacks;

void bleInit();

bool getBLEdata(BleType &bleDev);

#endif