#ifndef RADIO_H
#define RADIO_H

#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
//#include <printf.h>

#define R_PL_LENGTH 32
//extern char r_payload[R_PL_LENGTH];
extern char * r_playload;
extern RF24 radio;
extern RF24Network network;
//extern uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
//extern int channel = 90;
//const uint16_t node01 = 01;  

typedef void(*callback)(uint16_t, char *);

void radioBegin(int channel, uint16_t this_addr);

bool request(uint16_t addr, char * content);

void recieve(callback func, char * payload);

#endif
