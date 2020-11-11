#include "OLED.h"

const int16_t RectCord[4] = {0,17,31,45};
const int16_t TextCord[4] = {12,28,42,56};

void printContent(char * title, char * line0, char * line1, char * line2, int highlight){
	int highidx = highlight+1;
	display.clearDisplay();
	display.setFont(&FreeSerif9pt7b);
	display.setTextColor(WHITE);
	if(highidx>=0 && highidx<4){
		display.fillRect(0, RectCord[highidx], 128, 14, WHITE);
	}
 
	int count = 0;
	printLine(title, count++, highidx);
	printLine(line0, count++, highidx);
	printLine(line1, count++, highidx);
	printLine(line2, count++, highidx);
	display.display();
}

void printLine(char * text, int num, int highidx){
  if(text == NULL) return;
	display.setCursor(0, TextCord[num]);
	if(num != highidx){
		display.setTextColor(WHITE);
	}else{
		display.setTextColor(BLACK);
	}
	display.println(text);
}
