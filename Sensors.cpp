#include "Sensors.h"

#define MQ135_PIN 35
#define MQ5_PIN 33

void sensorsInit() {
    MQ_sensorsInit(MQ135_PIN);
    MQ_sensorsInit(MQ5_PIN);
    gy30Init(BH1750address);
    ms5611Init();
    SHT31dInit();
    //Serial.println("All sensors initialised OK");
}

struct SensorData sensorsRead() {
  struct SensorData retVal;

  retVal.mq5 = MQ_SensorsRead(MQ5_PIN);
  retVal.mq135 = MQ_SensorsRead(MQ135_PIN);
  retVal.GY30 = gy30Read(BH1750address);
  retVal.ms5611 = ms5611Read();
  retVal.ShT31D = SHT31dRead();

  return retVal;
}
