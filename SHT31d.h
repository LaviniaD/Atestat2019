#ifndef SHT31d
#define SHT31d

typedef struct TempData{
  float temp;
  float humi;
};

void SHT31dInit();
struct TempData SHT31dRead();

#endif SHT31d
