#include "RADIO.h"
//#include <Arduino.h>


//extern uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
//extern int channel = 90;

void radioBegin(int channel, uint16_t this_addr){
  Serial.print("0");
  SPI.begin();
  radio.begin();
  network.begin(channel, this_addr);  //(channel, node address)
  //printf_begin();
  //radio.printDetails();
}

bool request(uint16_t addr, char * payload){
  network.update();
  RF24NetworkHeader header(addr);
  bool ok = network.write(header, payload, sizeof(payload));
  return ok;
}

void recieve(callback func, char * payload){
  network.update();
  while(network.available()){
    memset(payload, 0, sizeof(payload));
    RF24NetworkHeader header;
    network.read(header, payload, R_PL_LENGTH);
    func(header.from_node, payload);
  }
}
