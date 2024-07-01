#include <Arduino.h>
#include "settings.h"
#include "ble.h"

//Serial
char buffer[300];

enum{
    
  OK_,
  ERROR_,
  INVALID_,
  NAC_,

};


void ack(int result){

  switch (result)
  {
  case OK_:
    Serial.println("OK");
    break;
  case NAC_:
    Serial.println("NOT_A_COMMAND");
    break;
  case INVALID_:
    Serial.println("VALUE_NOT_ALLOWED");
    break;
  case ERROR_:
    Serial.println("ERROR");
  default:
    break;
  }
  
  
}

void showParams(){

  Serial.println();
  for(int i=0;i<NUM_OF_BLE_DEVS; i++)
    Serial.printf("BLE Device: %d, MAC: %s, ENABLED: %d\n", i, bleDev[i].macStr.c_str(), bleDev[i].enabled);
  Serial.println();

}

void serialChek(){

  int rlen=0;
  bool fintrama=false;


  unsigned long ti = millis();
  unsigned long to = 0;

  while (to<1000 && fintrama==false) {

    while (Serial.available() > 0 && fintrama==false) {
      buffer[rlen] = Serial.read();
      if(
        (buffer[rlen]=='#')             //Comando corto
      )fintrama=true;
      else if(buffer[rlen]==0x0d || buffer[rlen]==0x0a){}//ignora los caractres 0x0d y 0x0a
      else rlen++;
    }
    to = millis() - ti;

  }


  if(fintrama){

    rlen++;
    //Serial.println(rlen);

    //Sino es alguno de los comandos:
    if(buffer[0]=='$' && buffer[rlen-1]=='#'){

      //Primero tomamos el indice del dispositivo BLE

      //Se agrega un caracter mas al final en NULL para que el compilador sepa donde termina el string
      //Ver apartado string en Arduino.cc/reference
      char bleDevStr[7]={'0','0','0','0','0','0','\0'};

      //Copiamos los caracteres del numero de bleDEV
      bleDevStr[4]=buffer[1];
      bleDevStr[5]=buffer[2];
      
      //Validamos que todos sean caracteres numericos:
      if(!isDigit(bleDevStr[4]) || !isDigit(bleDevStr[5])){
        ack(INVALID_);
        return;
      }
      
      //Convertimos caracteres a int
      int numBleDev=atoi(bleDevStr);

      //Validamos que todos sean caracteres numericos:
      if(numBleDev<0 || numBleDev>(NUM_OF_BLE_DEVS-1)){
        ack(INVALID_);
        return;
      }

      //COMANDO BLE MAC ADDRESS 
      //$01MAXX:XX:XX:XX:XX:XX#
      if(buffer[3]=='M' && buffer[4]=='A' && rlen == 23){

        String newAddressBLE = "";

        //Extraemos de la trama el String que tiene la MAC addres. 
        for (int i = 5; i < 22; i++)
          newAddressBLE += buffer[i];

        newAddressBLE.toLowerCase();

        bleDev[numBleDev].macStr=newAddressBLE;

        preferences.begin(SENSOR_SETTINGS_NAMES[numBleDev].c_str(), false);
        preferences.putString(MAC,newAddressBLE);  
        preferences.end();

        ack(OK_);

      }//FIN Si es trama mac

      //SINO si es un comando comun:
      //$00XX00#
      else if (rlen == 8){

        //Obtendremos el numero se que desea configurar:
        char numStr[7]={'0','0','0','0','0','0','\0'};

        //Copiamos los caracteres del numero de bleDEV
        numStr[4]=buffer[5];
        numStr[5]=buffer[6];  
        
        if(!isDigit(numStr[0]) || !isDigit(numStr[1])){
          ack(INVALID_);
          return;
        }
        
        //Convertimos caracteres a int
        int numInt=atoi(numStr);       

        if( numInt>=0 && numInt<=90 ){

          //Enable
          if(buffer[3]=='E' && buffer[4]=='N'){

            if(numInt==0 || numInt==1){
              //numBleDev--;
              bleDev[numBleDev].enabled=numInt;
              //bleDev[numBleDev].BLEfound=false;//Para que avise si no encuentra el sensor
              preferences.begin(SENSOR_SETTINGS_NAMES[numBleDev].c_str(), false);
              preferences.putBool(ENABLED,numInt);  
              preferences.end();
              ack(OK_);
            }
            else ack(INVALID_);

          }
          
          
          //Show Params
          else if(buffer[3]=='S' && buffer[4]=='P'){

            showParams();

          }

          //SET DEFAULT
          else if(buffer[3]=='S' && buffer[4]=='D'){
            
            saveDefaultSettings();
            ack(OK_);

          }
          
          else ack(NAC_);

        }//numero de 0 a 90
        else ack(INVALID_); //if ? #

      }//Comando comun
      
      //Sino entonces no es un comando
      else ack(NAC_); //if ? #

    }//Comando mac o comun

  }//if fintrama
  //Sino entonces no es un comando
  else {
    //ack(NAC_); //if ? #
  }

}