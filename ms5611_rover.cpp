#include "ms5611_rover.h"
#include <Wire.h>
#include <MS5611.h>

MS5611 ms5611;

void ms5611Init() {
  // Initialize MS5611 sensor
  // Ultra high resolution: MS5611_ULTRA_HIGH_RES
  // (default) High resolution: MS5611_HIGH_RES
  // Standard: MS5611_STANDARD
  // Low power: MS5611_LOW_POWER
  // Ultra low power: MS5611_ULTRA_LOW_POWER
  while(!ms5611.begin()){};
}

struct PresData ms5611Read() {
  struct PresData retVal;
  retVal.pressure = ms5611.readPressure();
  retVal.altitude = ms5611.getAltitude(retVal.pressure);

  return retVal;
}
