#ifndef SENSOR_BMP_H
#define SENSOR_BMP_H

#include "MENU.h"
class Item;
class DataItem;
class Menu;

struct bmp280data{
  float temp;
  float pres;
};
typedef struct bmp280data BMP280Data; 

const char * const BMP_VOICE = "Your current temperature is %.2f, current pressure is %.2f";

extern DataItem i_temp;
extern DataItem i_pres;
extern Item i_bmp;

#endif
