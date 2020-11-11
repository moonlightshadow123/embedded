#include "KEYPAD.h"

void Keypad::configure(){
	// Configure clock as output and hold it high
	pinMode( PAD_SCL, OUTPUT );
  digitalWrite(PAD_SCL, HIGH);

  // Configure data pin as input
  pinMode( PAD_SDA, INPUT);
}


uint16_t Keypad::readValue(){
	uint16_t buttonPressed = 0;
	for (uint16_t idx = 0; idx < KEYNUM; idx++ )
      {
        digitalWrite(PAD_SCL, LOW);
        delayMicroseconds(1);
        digitalWrite(PAD_SCL, HIGH);
        int val = digitalRead(PAD_SDA);
        delayMicroseconds(1);  
        if ( LOW == val )
        {
          buttonPressed =idx;
          return buttonPressed + 1;
        }
      }
  return buttonPressed;
}

uint16_t Keypad::checkPress(){
  uint16_t cur_key = this->readValue();
  if(cur_key == this->pre_key){
      return 0;
  }else{
      this->pre_key = cur_key;
      return cur_key;
  }
}
