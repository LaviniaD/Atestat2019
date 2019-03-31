#ifndef SENSORS_H
#define SENSORS_H

#include "gy30.h"
#include "MQ_sensors.h"
#include "ms5611_rover.h"
#include "SHT31d.h"
#include "Adafruit_SHT31.h"

typedef struct SensorData {
  int mq5;
  int mq135;
  struct PresData ms5611;
  struct TempData ShT31D;
  uint16_t GY30;
};

void sensorsInit();
struct SensorData sensorsRead();

#endif SENSORS_H
