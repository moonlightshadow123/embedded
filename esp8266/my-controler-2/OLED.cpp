#include "OLED.h"

const int16_t RectCord[4] = {0,17,31,45};
const int16_t TextCord[4] = {12,28,42,56};

void printMsg(const char * msg){
  display.clearDisplay();
  display.setFont(&FreeSerif9pt7b);
  display.setTextColor(WHITE);
  display.setCursor(0, 28);
  display.println(msg);
  display.display();
}

void printContent(const char * title,const char * line0,const char * line1,const char * line2, int highlight){
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

void printLine(const char * text, int num, int highidx){
  if(text == NULL) return;
	display.setCursor(0, TextCord[num]);
	if(num != highidx){
		display.setTextColor(WHITE);
	}else{
		display.setTextColor(BLACK);
	}
	display.println(text);
}
