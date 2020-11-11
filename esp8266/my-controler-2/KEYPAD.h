#ifndef KEYPAD_H
#define KEYPAD_H
#include <Arduino.h>
#define PAD_SCL 16
#define PAD_SDA 0

const uint8_t KEYNUM = 16;

class Keypad{
  uint16_t pre_key = 0;
  uint16_t readValue();
  public:
  void configure();
  uint16_t checkPress();
};

#endif
