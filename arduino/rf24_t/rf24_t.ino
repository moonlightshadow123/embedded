/*#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
//create an RF24 object
RF24 radio(7, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[][6] = {"00001", "00002"};

void setup()
{
  Serial.begin(9600);
  printf_begin();
  radio.begin();
  delay(100);
  radio.setAutoAck(true);
  //radio.setCRCLength(RF24_CRC_16);
  radio.setDataRate( RF24_250KBPS );
  //radio.setChannel(115);
  //set the address
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(0, address[1]);
  //Set module as transmitter
  radio.printDetails();
}
void loop()
{
  //Send message to receiver
  radio.stopListening();
  const char text[] = "Hello World";
  bool res = radio.write(&text, sizeof(text));
  radio.startListening();
  Serial.print(text);
  Serial.print(" --- ");
  Serial.println(res);
  delay(5);
  while(!radio.available())
  {}
  char text_r[32] = {0};
  radio.read(&text_r, sizeof(text_r));
  Serial.print("Got Text: ");
  Serial.println(text_r);
  delay(3000);
}*/
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
int msg[1] = {1};
int rec[1] = {5};
bool stat = true;
RF24 radio(7,8);
const uint64_t pipe[1] = {0xF0F0F0F0E1LL};
  
void setup()
{
  Serial.begin(115200);
  radio.begin();
  delay(100);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.stopListening();
  radio.openWritingPipe(pipe[0]);
  radio.setRetries(15,15);
 }
void loop()
{
if(stat)
{
    if(radio.write(msg,sizeof(msg)))
    {
      Serial.print( msg[0] );
      Serial.println("...tx success");
      if(radio.isAckPayloadAvailable())
      {
        radio.read(rec,sizeof(int));
        Serial.print("received ack payload is : ");
        Serial.println(rec[0]);
      }
      else
      {
        stat = false; //doing this completely shuts down the transmitter if an ack payload is not received !!
        Serial.println("status has become false so stop here....");
      }
      msg[0]+=3;;
    if(msg[0]>=100)
    {msg[0]=1;}
    }
    delay(10);
 }
}
