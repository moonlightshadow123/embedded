#include "TTP229Key.h"
#include "OLED.h"
#include "MY_NRF24L01.h"
#include <printf.h>

CTtP229TouchButton g_ttp229Button;
#define TTP16Button g_ttp229Button

char serialBuff[100];
int highLight = 0;

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)

  DEBUG_STATUS(Serial.println("TTP229 Capacitive Touch Keypad"));
  DEBUG_STATUS(Serial.println("------------------------------"));
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  TTP16Button.Configure(SCLPin, SDAPin);
  //digitalWrite(LEDPin, LOW);             // default turn off output pin
  //pinMode(LEDPin, OUTPUT);               // configure an output test pin to respond on button 6 press/release
  printf_begin();
  radio.printDetails();
  prt();
}

void TestStatus()
{
  uint8_t buttonNumber = TTP16Button.GetButtonStatus();

  if ( 0 != buttonNumber )
  {
    DEBUG_STATUS(Serial.print("Button Pressed : "));
    DEBUG_STATUS(Serial.println(buttonNumber));
  }

  delayMicroseconds(2500); // TTP229 document says it will reset the output if 2ms idle + little bit safety
}

void TestEvent()
{
#if defined(INT0_PIN) || defined(INT1_PIN)
  if ( TTP16Button.HasEvent())
#endif
  {
    CTtp229ButtonEvent buttonEvent = TTP16Button.GetButtonEvent();

    if ( 0 != buttonEvent.ButtonNumber )
    {
      if ( buttonEvent.IsButtonReleased )
      {
        DEBUG_STATUS(Serial.print("Button Released: "));
        if (buttonEvent.ButtonNumber == 6) {
          digitalWrite(LEDPin, LOW);
        }
      }
      else
      {
        DEBUG_STATUS(Serial.print("Button Pressed : "));
        if (buttonEvent.ButtonNumber == 1) {
            if(highLight<3) highLight++;
        }else if(buttonEvent.ButtonNumber == 2){
            if(highLight>0) highLight--;
        }else if(buttonEvent.ButtonNumber == 3){
          request();  
        }
        prt();
      }
      DEBUG_STATUS(Serial.println(buttonEvent.ButtonNumber));
    }
    else
    {
#if defined(INT0_PIN) || defined(INT1_PIN)
      DEBUG_STATUS(Serial.println("Are you not using interrupt? Should never come here for interrupt based system."));
#endif
    }

    //Serial.print("CurrentTime : "); Serial.println(millis());
    delayMicroseconds(2500); // TTP229 document says it will reset the output if 2ms idle + little bit safety. Not required if using interrupts
  }
}

void prt(){
  printContent("Function:", "D1", "D2", serialBuff, highLight);
}

void loop()
{
  int i;
  //TestStatus();
  TestEvent();
  if (Serial.available()){ // Wait 'till there are 9 Bytes waiting
      i = Serial.readBytesUntil('\n', serialBuff, sizeof(serialBuff) - 1);
      serialBuff[i] = '\0';
      prt();
  }
  prt();
  receive();
  delay(10);
}
