#ifndef GY30_H
#define GY30_H

#include <Arduino.h>

#define BH1750address 0x23

void gy30Init(int address);
uint16_t gy30Read(int address);

#endif GY30_H
