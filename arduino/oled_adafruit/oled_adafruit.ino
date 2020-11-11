/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  bool ok = display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.println(ok);
  if(!ok) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.display(); 
}

void printContent(char * title, char * line1, char * line2, char * line3){
  display.clearDisplay();
  display.setFont(&FreeSerif9pt7b);
  display.setTextColor(WHITE);
  // Title
  display.setCursor(0, 11);
  display.println(title);
  // Line 1
  display.setCursor(0, 28);
  display.println(line1);
  // Line 2
  display.setCursor(0, 42);
  display.println(line2);
  // Line 3
  display.setCursor(0, 56);
  display.println(line3);
  display.display(); 
}

void loop() {
  delay(1000);
  printContent("Message: ", "line1 messg", "line2 messg", "line3 messg");
}
