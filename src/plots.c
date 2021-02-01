#include "main.h"

void 
plotInitialMenu () {
  system("clear");
  putBar();
  printCenter("STOCK MNGMT SYSTEM");
  putBar();
  printCenter(" [1] Admin");
  printCenter("[2] Exit");
  putchar('\n');
}


void 
plotStockMenu () {
  system("clear");
  putBar();
  printCenter("STOCK");
  putBar();
  printCenter("\t[1] Register new item");
  printCenter("\t[2] Show item table");
  printCenter("[3] Back to menu");
  putchar('\n');
}


void 
plotRegisterItemHeader () {
  system("clear");
  putBar();
  printCenter(BGRN"\t REGISTER NEW ITEM"reset);
  putBar();
  putchar('\n');
}


void 
plotEditItemHeader () {
  system("clear");
  putBar();
  printCenter(BYEL"\t  EDIT ITEM"reset);
  putBar();
  putchar('\n');
}


void 
plotDeleteItemHeader () {
  system("clear");
  putBar();
  printCenter(BRED"\t  DELETE ITEM"reset);
  putBar();
  putchar('\n');
}


void 
plotStockListHeader () {
  system("clear");
  putBar();
  printCenter("STOCK LIST");
  putBar();
  putchar('\n');
}


void 
plotStockListMenu () {
  putBar();
  printf(BYEL"\n\t\t[1] Edit item"BRED"\
  [2] Delete item"BCYN"  [3] Back to menu\n"reset);
}
