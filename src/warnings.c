#include "main.h"

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

