#include "MENU.h"
#include "SENSOR_BMP.h"

Item i_root = Item("My Controller");
Menu menu(&i_root);

void menu_config(){
  i_root.addItem(&i_bmp);
  i_bmp.addItem(&i_temp);
  i_bmp.addItem(&i_pres);
  menu.jump_to(&i_root);
}

Item::Item(const char * line){ 
  strcpy(this->line, line); 
}

void Item::addItem(Item * subItem){
  if(this->subNum >= MAX_ITEM_NUM){
    Serial.println("ERROR: MAX ITEM NUM REACHED!");
    return;
  }
  if(this->subNum == 0){
    this->subItems = (Item**)malloc(MAX_ITEM_NUM*sizeof(Item*));
    memset(this->subItems, 0, MAX_ITEM_NUM*sizeof(Item*));
  }
  this->subItems[this->subNum] = subItem;
  subItem->preItem = this;
  this->subNum++;
}

DataItem::DataItem(const char * line):Item{line}{
  this->len = strlen(line);
};

void DataItem::prtData(float d){
  uint8_t len = this->len;
  if(d > 10000 || d < -10000)
    sprintf(&this->line[len], DataFmtB, d);
  else
    sprintf(&this->line[len], DataFmtS, d);
}

Menu::Menu(Item * item){
  this->rootItem = item;
}

Item *Menu::getSltItem(){
  // Item
  Item * curItem = this->curItem;
  uint8_t len = curItem->subNum;
  Item ** subItems = curItem->subItems;
  // Menu
  int cur_line = this->cur_line;
  if(cur_line >= 0 && cur_line < len){
    return subItems[cur_line];
  }
  return NULL;
}
  
void Menu::disp(){
  // Item
  Item * curItem = this->curItem;
  uint8_t len = curItem->subNum;
  Item ** subItems = curItem->subItems;
  // Menu
  int fst_line = this->fst_line;
  // Lines
  char * title = curItem->line;
  char * line1 = fst_line<len ? subItems[fst_line]->line : NULL;
  char * line2 = fst_line+1<len ? subItems[fst_line+1]->line : NULL;
  char * line3 = fst_line+2<len ? subItems[fst_line+2]->line : NULL;
  printContent(curItem->line, line1, line2, line3, this->cur_line-this->fst_line);
}

void Menu::move_up(){
  Item * curItem = this->curItem;
  if(this->cur_line <= -2) // Already Top
    return;
  if(this->cur_line > this->fst_line) // Bottom
    this->cur_line--;
  else if(this ->cur_line == this->fst_line && this->fst_line > 0){ // Scroll Up
    this->cur_line--;
    this->fst_line--;
  }else if(this->cur_line <= this->fst_line && this->fst_line == 0){ // Almost Top
    this->cur_line --;
  }
}

void Menu::move_down(){
  uint8_t subNum = this->curItem->subNum;
  if(this->cur_line >= subNum-1){ // Already Bottom
    return;
  }
  if(this->cur_line < this->fst_line + 2){ //Top
    this->cur_line++;
  }else if(this->cur_line == this->fst_line + 2){ // Scroll Down
    this->cur_line++;
    this->fst_line++;
  }
}

void Menu::move_in(){
  Item * curItem = this->curItem;
  uint8_t subNum = curItem->subNum;
  int cur_line = this->cur_line;
  if(cur_line < 0 || cur_line >= subNum) // Not a valid position
    return;
  else if(curItem->subItems[cur_line]->subNum == 0) // Not a valid item
    return;
  else
    jump_to(curItem->subItems[cur_line]);
 }

void Menu::move_out(){
  Item * preItem = this->curItem->preItem;
  if(preItem != NULL)
    jump_to(preItem);
}

void Menu::jump_to(Item * item){
  this->curItem = item;
  this->cur_line = -2;
  this->fst_line = 0;
}
