#include "MY_NRF24L01.h"
#include "OLED.h"
#include <Arduino.h>

RF24 radio(7, 8);
RF24Network network(radio);

struct BMP280Data{
  float temp;
  float pressure;
};

char payload[32] = {0};

bool request(){
  network.update();
  RF24NetworkHeader header(node01);
  bool ok = network.write(header, "Req", sizeof("Req"));
  Serial.print("Req --- ");
  Serial.println(ok);
  return ok;
}

void prtData(float temp, float pressure){
  char line1[20] = {0};
  char line2[20] = {0};
  sprintf(line1, "Temp: %.2f", temp);
  sprintf(line2, "Pres: %.2f", pressure);
  printContent("Message:", line1, line2, "",-1);
}

void receive(){
  network.update();
  while(network.available()){
    memset(payload, 0, sizeof(payload));
    RF24NetworkHeader header;
    network.read(header, &payload, sizeof(payload));
    if(header.from_node == 1){
      BMP280Data* bdata = (BMP280Data*)payload;
      Serial.print(bdata->temp);
      Serial.print(";");
      Serial.println(bdata->pressure);
      prtData(bdata->temp, bdata->pressure);
    }
  }
}
