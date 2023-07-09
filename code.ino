#include<SPI.h>
#include "protocentral_max30003.h"

#define MAX30003_CS_PIN 7

MAX30003 max30003(MAX30003_CS_PIN);

void setup()
{
    Serial.begin(57600); //Serial begin

    pinMode(MAX30003_CS_PIN,OUTPUT);
    digitalWrite(MAX30003_CS_PIN,HIGH); //disable device

    SPI.begin();

    bool ret = max30003.max30003ReadInfo();
    if(ret){
      Serial.println("Max30003 read ID Success");
    }else{

      while(!ret){
        //stay here untill the issue is fixed.
        ret = max30003.max30003ReadInfo();
        Serial.println("Failed to read ID, please make sure all the pins are connected");
        delay(10000);
      }
    }

    Serial.println("Initialising the chip ...");
    max30003.max30003Begin();   // initialize MAX30003
}

void loop()
{
    max30003.getEcgSamples();   //It reads the ecg sample and stores it to max30003.ecgdata .

    Serial.println(max30003.ecgdata);
    delay(8);
}
