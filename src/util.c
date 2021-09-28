#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include "util.h"

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


void 
putBar () {
  for (int i = 0; i < 80; i++) {
    printf(BWHT"="reset);
  }
  putchar('\n');
}


int 
printCenter (char *string) {
  int width  = 80;
  int length = strlen(string) - 1;
  int padding = (length >= width) ? 0 : (width - length) / 2;
  printf(BCYN"%*.*s%s\n"reset, padding, padding, " ", string);
  return 0;
}


const char * const warnings [] = {
  BRED"\n[!] Error, option does not exist!\n"reset,
  BRED"\n[!] An error occurred"reset,
  BGRN"\n[i] The item was successfully registered!\n"reset,
  BYEL"\n[!] There are no registered items.\n"reset,
  BYEL"\n[!] Do you want to save item data? [Y/N] "reset,
  BYEL"\n[!] The item was not found!\n"reset,
  BGRN"\n[i] The item was found!\n"reset,
  BYEL"\n[!] Are you sure you want to edit item information? [Y/N] "reset,
  BYEL"\n[-] Which field would you like to change? "reset,
  BGRN"\n[i] Item information updated successfully!\n"reset,
  BCYN"\n[i] Finish updating registration [ENTER] "reset,
  BRED"\n[!] Are you sure you want to delete item information? [Y/N] "reset,
  BGRN"\n[i] Item information deleted successfully!\n"reset
};

