/*//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

//create an RF24 object
RF24 radio(7, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[][6] = {"00001", "00002"};

void setup()
{
  while (!Serial);
    Serial.begin(9600);
  printf_begin();
  
  radio.begin();
  delay(100);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.setDataRate( RF24_250KBPS );
  //radio.setChannel(115);
  //set the address
  radio.openReadingPipe(0, address[0]);
  radio.openWritingPipe(address[1]);
  
  //Set module as receiver
  //radio.setChannel(4);
  radio.printDetails();
}

void loop()
{
  //Read the data if available in buffer
  radio.startListening();
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    Serial.print("Got Text: ");
    Serial.println(text);
    text[0]++;
    radio.stopListening();
    radio.write(&text, sizeof(text));
  }
  delay(10);
}*/

#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
const uint64_t pipe[1]= {0xF0F0F0F0E1LL};
RF24 radio(7,8);
int rec[1] = {2};
int red;
void setup()
{
  Serial.begin(115200);
  radio.begin();
  delay(100);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(1,pipe[0]);
  radio.startListening();
  radio.setRetries(15,15);
}
void loop()
{
  if ( radio.available() ){
    radio.writeAckPayload( 1, rec, sizeof(int) );
    radio.read( &red,sizeof(red) );rec[0]+=2;
    Serial.print("integer got is : ");
    Serial.println(red);
}
}
