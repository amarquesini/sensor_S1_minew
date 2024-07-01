#include <Arduino.h>
#include "settings.h"
#include "ble.h"
#include "led.h"
#include "uart.h"


void setup()
{

  //COMUNICACION SERIAL
  Serial.begin(115200);
   
  //LECTURA DE PARAMETROS DESDE MEMORIA FLASH
  readSettingsFromFlash();

  //SCANNER BLE
  bleInit();

  //LED
  ledInit();

  
}


void loop()
{

  //SCAN
  Serial.print("  .");
  pBLEScan->start(SCAN_TIME, false);


  //SERIAL CHECK
  if (Serial.available() > 0) serialChek();

  //LED
  led();


}