#include "settings.h"
#include "ble.h"

#define LED_ONBOARD 2
#define TIME_TO_UPDATE_LED_MS 1000

void ledInit(){

  pinMode(LED_ONBOARD, OUTPUT);
  digitalWrite(LED_ONBOARD, LOW);

}

void led(){

  static bool led_state;
  static unsigned long lastUpdate;

  if(millis()>=lastUpdate+TIME_TO_UPDATE_LED_MS){

    //Blink
    led_state = !led_state;
    digitalWrite(LED_ONBOARD, led_state);

    lastUpdate=millis();

  }

}