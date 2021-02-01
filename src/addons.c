#include "main.h"

void putBar () {
  for (int i = 0; i < 80; i++) {
    printf(BWHT"="reset);
  }
  putchar('\n');
}


int printCenter (char *string) {
  int width  = 80;
  int length = strlen(string) - 1;
  int padding = (length >= width) ? 0 : (width - length) / 2;
  printf(BCYN"%*.*s%s\n"reset, padding, padding, " ", string);
  return 0;
}