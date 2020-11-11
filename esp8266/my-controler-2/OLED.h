#ifndef OLED_H
#define OLED_H
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
extern Adafruit_SSD1306 display;

void printContent(char * title, char * line1, char * line2, char * line3, int highlight);
void printLine(char * text, int num, int hightlight);
#endif
