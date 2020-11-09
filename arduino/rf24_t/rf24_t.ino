#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
//create an RF24 object
RF24 radio(7, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  radio.begin();
  //radio.setCRCLength(RF24_CRC_16);
  Serial.begin(9600);
  printf_begin();
  //radio.setDataRate( RF24_250KBPS );
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
  //radio.setChannel(21);
  //radio.setCRCLength(RF24_CRC_16);
  radio.printDetails();
}
void loop()
{
  //Send message to receiver
  const char text[] = "Hello World";
  bool res = radio.write(&text, sizeof(text));
  radio.printDetails();
  Serial.print(text);
  Serial.print(" --- ");
  Serial.println(res);
  
  delay(3000);
}
