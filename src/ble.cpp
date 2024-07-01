#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "BLEBeacon.h"
#include "BLEEddystoneTLM.h"
#include "BLEEddystoneURL.h"
#include <Arduino.h>
#include "settings.h"

const uint8_t SCAN_TIME = 1;

//BLE ACCELEROMETER
uint8_t cServiceData[100];
uint8_t cManufacturerData[100];
BLEScan *pBLEScan;
//int  scanTime = 1; //In seconds
uint16_t beconUUID = 0xFEAA;
#define ENDIAN_CHANGE_U16(x) ((((x)&0xFF00) >> 8) + (((x)&0xFF) << 8))

BleType bleDev[NUM_OF_BLE_DEVS];

bool getBLEdata(BleType &bleDev)
{

  //Serial.println("GET BLE DATA:");

  int8_t battery = 255;
  int tempInd = 0;
  int8_t tempInt = 0;
  int8_t humInt = 0;
  char humDec = 0;
  char tempDec = 0;
  float tempF = 0;
  float humF = 0;

  bleDev.batteryLevel = (short)cServiceData[2];
  
  tempInt = (int8_t)cServiceData[3];
  tempDec = (char)cServiceData[4];
  tempF = ((float)tempDec / 256); 
  bleDev.tempF = tempInt + tempF;
  
  humInt = (int8_t)cServiceData[5];
  humDec = (char)cServiceData[6];
  humF = ((float)humDec / 256);
  bleDev.humF = humInt + humF;

  Serial.printf("Battery: %d\n", bleDev.batteryLevel);
  Serial.printf("Temp: %.2f\n", bleDev.tempF);
  Serial.printf("Hum: %.2f\n", bleDev.humF);

  return true;

}


class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{

  void onResult(BLEAdvertisedDevice advertisedDevice)
  {

    std::string macReceived=advertisedDevice.getAddress().toString();

    for(int i=0;i<(NUM_OF_BLE_DEVS);i++){

      if(bleDev[i].enabled && macReceived==bleDev[i].macStr.c_str()){

        //Serial.printf("MAC Recibida: %s\n", macReceived.c_str());
        Serial.printf("\nDatos de Sensor %d:\n", i);
        
        if(advertisedDevice.haveServiceData()){

          std::string strServiceData = advertisedDevice.getServiceData();
          strServiceData.copy((char *)cServiceData, strServiceData.length(), 0);

          // Serial.printf("0x");
          // for(int i=0;i<strServiceData.length();i++)
          //   Serial.printf("%02x,", cServiceData[i]);
          // Serial.printf("\n");

          if (cServiceData[0] == 0xA1 && cServiceData[1] == 0x1) {

            getBLEdata(bleDev[i]);

          }
        
        }

      }
    
    }

    
  }

};


void bleInit(){

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster

}



