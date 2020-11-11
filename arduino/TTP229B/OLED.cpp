#include "OLED.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int16_t RectCord[4] = {0,17,31,45};
int16_t TextCord[4] = {11,28,42,56};

void printContent(char * title, char * line1, char * line2, char * line3, int highlight){
	display.clearDisplay();
	display.setFont(&FreeSerif9pt7b);
	display.setTextColor(WHITE);
	if(highlight>=0)
		display.fillRect(0, RectCord[highlight], 100, 14, WHITE);
	int count = 0;
	printLine(title, count++, highlight);
	printLine(line1, count++, highlight);
	printLine(line2, count++, highlight);
	printLine(line3, count++, highlight);
	display.display();
}

void printLine(char * text, int num, int highlight){
	display.setCursor(0, TextCord[num]);
	if(num != highlight){
		display.setTextColor(WHITE);
	}else{
		display.setTextColor(BLACK);
	}
	display.println(text);
}
