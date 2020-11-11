#ifndef MY_NRF24L01_H
#define MY_NRF24L01_H
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

extern RF24 radio;
extern RF24Network network;
const uint16_t this_node = 00;
const uint16_t node01 = 01;

struct BMP280Data;

extern char payload[32];

bool request();

void receive();
#endif
