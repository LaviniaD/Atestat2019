#include "SHT31d.h"
#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void SHT31dInit(){
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
  //  Serial.println("Couldn't find SHT31");
  }
}

struct TempData SHT31dRead(){
  struct TempData retVal;
  retVal.temp=sht31.readTemperature();
  retVal.humi=sht31.readHumidity();

  return retVal;
}
