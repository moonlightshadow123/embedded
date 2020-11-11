/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
 == Example 01 - Servo Control / Node 00 - Potentiometer ==
  by Dejan, www.HowToMechatronics.com
  Libraries:
  nRF24/RF24, https://github.com/nRF24/RF24
  nRF24/RF24Network, https://github.com/nRF24/RF24Network
*/
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include <printf.h>
RF24 radio(4, 8);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;      

struct BMP280Data{
  float temp;
  float pressure;
};

void setup(){
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  Serial.begin(115200);
  printf_begin();
  radio.printDetails();
}

char payload[32] = {0};

bool request(){
  network.update();
  RF24NetworkHeader header(node01);
  bool ok = network.write(header, "Req", sizeof("Req"));
  Serial.print("Req --- ");
  Serial.println(ok);
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
    }
  }
}

void loop() {
  /*network.update();
  //unsigned long potValue = analogRead(A0);  // Read the potentiometer value
  //unsigned long angleValue = map(potValue, 0, 1023, 0, 180); // Convert the value to 0-180
  char text[32] = {"Hello, Net!"};
  RF24NetworkHeader header(node01);     // (Address where the data is going)
  bool ok = network.write(header, &text, sizeof(text)); // Send the data
  Serial.print(text);
  Serial.print(" --- ");
  Serial.println(ok);
  delay(10);*/
  //char buff[20];
  char c;
  if(Serial.available()){
    c = Serial.read();
    if(c == 'r')
    request();
  }
  receive();
  delay(10);
}
