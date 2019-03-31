#include "MQ_sensors.h"
#include <Arduino.h>
void MQ_sensorsInit(int pin){
  pinMode(pin, INPUT);
}
int MQ_SensorsRead(int pin){
  int val = analogRead(pin);
  return val;
}
