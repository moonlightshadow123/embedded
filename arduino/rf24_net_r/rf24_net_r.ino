/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
  == Example 01 - Servo Control / Node 01 - Servo motor ==
*/
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include <Servo.h>
RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t node00 = 00;
//Servo myservo;  // create servo object to control a servo

struct BMP280Data{
  float temp;
  float pressure;
};
char payload[32] = {0};

void setup() {
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
  //myservo.attach(3);   // (servo pin)
  Serial.begin(115200);
}

bool reply(){
  memset(payload, 0, sizeof(payload));
  BMP280Data * bdata = (BMP280Data*)payload;
  bdata->temp = 20.35;
  bdata->pressure = 10135.57;
  RF24NetworkHeader header(node00);
  bool ok = network.write(header, bdata, sizeof(BMP280Data));
  return ok;
}

void receive(){
  network.update();
  while(network.available()){
    memset(payload, 0, sizeof(payload));
    RF24NetworkHeader header;
    network.read(header, &payload, sizeof(payload));
    if(header.from_node == 0){
      Serial.print("Got data: ");
      Serial.println(payload);
      reply();
    }
  }
}
void loop() {
  /*network.update();
  while ( network.available()){     // Is there any incoming data?
    RF24NetworkHeader header;
    char text[32] = {0};
    network.read(header, &text, sizeof(text)); // Read the incoming data
    //myservo.write(incomingData);  // tell servo to go to a particular angle
    Serial.print("Got text: ");
    Serial.println(text);
  }*/
  receive();
  delay(5);
}
