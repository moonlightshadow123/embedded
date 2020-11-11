#ifndef MENU_H
#define MENU_H
#include "OLED.h"

#define MAX_LINE_SIZE 32
#define MAX_ITEM_NUM 10

//#define DataFmtS "%.2f"
//#define DataFmtB "%.6e"

const char * const DataFmtS = "%.2f";
const char * const DataFmtB = "%.4e";

class Item;
class DataItem;
class Menu;

extern Item i_root;
extern Menu menu;

void menu_config();

class Item{
  public:
    char line[MAX_LINE_SIZE] = {0};
    Item * preItem = NULL;
    Item ** subItems = NULL;
    uint8_t subNum = 0;
    
    Item(const char *);
    void addItem(Item *);
};

class DataItem: public Item{
  public:
  uint8_t len;
  DataItem(const char *);
  void prtData(float d);
};

class Menu{
  public:
    int fst_line = 0;
    int cur_line = -2;
    Item* rootItem = NULL;
    Item* curItem = NULL;
    
    Menu(Item * item);
    Item * getSltItem();
    void disp();
    void move_up();
    void move_down();
    void move_in();
    void move_out();
    void jump_to(Item*);
};
#endif
