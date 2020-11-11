#ifndef SENSOR_BMP_H
#define SENSOR_BMP_H

#include "MENU.h"
class Item;
class DataItem;
class Menu;

struct bmp280data{
  float temp;
  float pressure;
};
typedef struct bmp280data BMP280Data; 

extern DataItem i_temp;
extern DataItem i_pres;
extern Item i_bmp;

#endif
