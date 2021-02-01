#include "main.h"

void 
selectChoice (int choice, int key) {
  if (key == 1) {
    switch (choice) {
      case 1: initialMenu(2); break;
      case 2: system("clear"); exit(0);
      default: {
        printf("%s", warnings[0]);
        sleep(SECONDS);
        main();
      }
    }
  } else {
    switch (choice) {
      case 1: registerItem(); break;
      case 2: showStockList(); break;
      case 3: initialMenu(1); break;
      default: {
        printf("%s", warnings[0]);
        sleep(SECONDS);
        initialMenu(2);
      }
    }
  }
}


void 
initialMenu (int payload) {
  switch (payload) {
    case 1: plotInitialMenu(); break;
    case 2: plotStockMenu(); break;
  }

  int choice;

  printf(BWHT"[+] Enter your choice: "reset);
  scanf("%i", &choice);

  selectChoice(choice, payload);
}