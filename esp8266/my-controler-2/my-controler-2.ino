/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
 == Example 01 - Servo Control / Node 00 - Potentiometer ==
  by Dejan, www.HowToMechatronics.com
  Libraries:
  nRF24/RF24, https://github.com/nRF24/RF24
  nRF24/RF24Network, https://github.com/nRF24/RF24Network
*/
#include "OLED.h"
#include "RADIO.h"
#include "KEYPAD.h"
#include <printf.h>

// OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// RF24
RF24 radio(2, 15);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
char r_payload[R_PL_LENGTH] = {0};
const int channel = 90;
const uint16_t this_addr = 00;   // Address of this node in Octal format ( 04,031, etc) 
const uint16_t bmp_addr = 01;

// KEYPAD
Keypad keypad = Keypad();

struct BMP280Data{
  float temp;
  float pressure;
};

void setup(){
  Serial.begin(115200);
  bool ok = display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false);
  Serial.print(ok);
  Serial.println(" ---!");
  display.display();
  radioBegin(channel, this_addr);
  printf_begin();
  radio.printDetails();
  bool result = radio.isChipConnected();
  Serial.println(result);
  keypad.configure();
  delay(1000);
}

void bmp_cbk(uint16_t addr, char * pl){
  if(addr == 1){
    BMP280Data* bdata = (BMP280Data*)pl;
    Serial.print(bdata->temp);
    Serial.print(";");
    Serial.println(bdata->pressure);
    bmp_prt(bdata->temp, bdata->pressure);
  }
}

void bmp_prt(float temp, float pressure){
  char line1[20];
  char line2[20];
  sprintf(line1, "Temp: %.2f", temp);
  sprintf(line2, "Pres: %.2f", pressure);
  printContent("Message: ", line1, line2, "", -1);
}

void key_func(uint16_t key){
  Serial.println(key);
}

void loop() {
  char c;
  if(Serial.available()){
    c = Serial.read();
    if(c == 'r')
      request(bmp_addr, "REQ");
  }
  recieve(bmp_cbk, r_payload);
  uint16_t key = keypad.checkPress();
  if(key != 0) key_func(key);
  delay(10);
}
