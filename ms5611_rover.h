#ifndef MS5611_ROVER_H
#define MS5611_ROVER_H

typedef struct PresData {
  long pressure; // Pascals
  double altitude; // Meters
};

void ms5611Init();
struct PresData ms5611Read();

#endif MS5611_ROVER_H
