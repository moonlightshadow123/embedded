/*
   Keyboard test
   For the Arduino Leonardo, Micro or Due Reads
      a byte from the serial port, sends a keystroke back. 
   The sent keystroke is one higher than what's received, e.g. if you send a, you get b, send
      A you get B, and so forth.
   The circuit:
   * none
*/

#include <Keyboard.h>

void setup() {
   // open the serial port:
   Serial.begin(9600);
   // initialize control over the keyboard:
   Keyboard.begin();
}

void loop() {
   // check for incoming serial data:
   if (Serial.available() > 0) {
      // read incoming serial data:
      char inChar = Serial.read();
      // Type the next ASCII value from what you received:
      Keyboard.write(inChar + 1);
   }
}
