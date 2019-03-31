#include <Wire.h>
#include "gy30.h"

uint8_t buff[2];

uint16_t BH1750_Read(int address)
{
   int i=0;
   Wire.beginTransmission(address);
   Wire.requestFrom(address, 2);
   while(Wire.available())
   {
      buff[i] = Wire.read();  // receive one byte
      i++;
   }
   Wire.endTransmission();
   return i;
}

void gy30Init(int address){
  Wire.beginTransmission(address);
   Wire.write(0x10); //1lx reolution 120ms
   Wire.endTransmission();
}
uint16_t gy30Read(int address){
  uint16_t val=0;
  if(2==BH1750_Read(address))
  {
    val=((buff[0]<<8)|buff[1])/1.2;
  }
  return val;
}
