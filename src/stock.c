#include "main.h"

/************************************************
 * Register item                                *
 ************************************************/

void 
freeStockRegistrationMemory (stockData *item_t) {
  free(item_t);
  item_t = NULL;
}


void 
saveStockRegistrationData (stockData *item_t) {
  FILE *savedStockFile;
  savedStockFile = fopen(STOCK_REGISTRATION_DATA, "a");

  if (savedStockFile == NULL) {
    perror(warnings[1]);
    exit(1);
  }

  fprintf(savedStockFile, "%i %s %i %f\n", 
  item_t->itemId,
  item_t->itemName,
  item_t->itemQty,
  item_t->itemPrice);

  fclose(savedStockFile);
  savedStockFile = NULL;
  freeStockRegistrationMemory(item_t);
}


void 
stockRegistryControl (stockData *item_t) {
  char choice;

  printf("%s", warnings[4]);
  setbuf(stdin, NULL);
  scanf("%c", &choice);

  switch (choice) {
    case 'Y':
    case 'y': {
      saveStockRegistrationData(item_t);
      printf("%s", warnings[2]);
      sleep(SECONDS);
      initialMenu(2); 
      break;
    }
    case 'N':
    case 'n': {
      freeStockRegistrationMemory(item_t);
      initialMenu(2);
      break;
    }
    default: {
      printf("%s", warnings[0]);
      sleep(SECONDS);
      getchar();
      return stockRegistryControl(item_t);
      break;
    }
  }
}


int 
generateRandomId () {
  srand(time(NULL));
  return (rand() % 999) << 2;
}


void 
inputItemRegistrationData (stockData *item_t) {
  printf(BWHT"[+] Enter the item name: "reset);
  setbuf(stdin, NULL);
  scanf("%[^\n]s", item_t->itemName);

  printf(BWHT"[+] Enter the item quantity: "reset);
  setbuf(stdin, NULL);
  scanf("%i", &item_t->itemQty);

  printf(BWHT"[+] Enter the item price (per unit): "reset);
  setbuf(stdin, NULL);
  scanf("%f", &item_t->itemPrice);
}


void 
registerItem () {
  stockData *item_t;
  item_t = (void *) malloc(sizeof(struct stockStruct));

  plotRegisterItemHeader();

  item_t->itemId = generateRandomId();

  inputItemRegistrationData(item_t);

  stockRegistryControl(item_t);
}


/************************************************
 * Show Stock List                             *
 ************************************************/

void 
freeStockListMemory (FILE *savedStockFile, stockData *item_t) {
  fclose(savedStockFile);
  savedStockFile = NULL;
  freeStockRegistrationMemory(item_t);
}


int 
checkNumberOfLines () {
  FILE *savedStockFile;
  savedStockFile = fopen(STOCK_REGISTRATION_DATA, "r");

  if (savedStockFile == NULL) {
    perror(warnings[1]);
    exit(1);
  }

  char c;

  int lines = 0;

  while (fread(&c, sizeof(char), 1, savedStockFile)) {
    if (c == '\n') {
      lines++;
    }
  }

  fclose(savedStockFile);
  savedStockFile = NULL;

  return lines;
}


void 
getStockRegistrationData (FILE *savedStockFile, stockData *item_t, int lines) {
  for (int i = 0; i < lines; i++) {
    setbuf(stdin, NULL);
    fscanf(savedStockFile, "%i %s %i %f", 
    &item_t[i].itemId,
    item_t[i].itemName,
    &item_t[i].itemQty,
    &item_t[i].itemPrice);
  }
}


void 
stockListControl (FILE *savedStockFile, stockData *item_t, int choice, int lines) {
  switch (choice) {
    case 1: checkItemId(savedStockFile, item_t, lines, 0); break;
    case 2: checkItemId(savedStockFile, item_t, lines, 1); break;
    case 3: initialMenu(2); break;
    default: {
      printf("%s", warnings[0]);
      sleep(SECONDS);
      showStockList();
    } 
  }
}


void 
showStockList () {
  plotStockListHeader();

  FILE *savedStockFile;
  savedStockFile = fopen(STOCK_REGISTRATION_DATA, "r");

  if (savedStockFile == NULL) {
    perror(warnings[1]);
    exit(1);
  }

  int lines = checkNumberOfLines();

  if (lines == 0) {
    printf("%s", warnings[3]);
    sleep(SECONDS);
    initialMenu(2);
  }

  stockData *item_t;
  item_t = (void *) malloc(sizeof(item_t));

  getStockRegistrationData(savedStockFile, item_t, lines);

  for (int i = 0; i < lines; i++) {
    printf(CYN"ID: %i, NAME: %s, QTY: %i, \
PRICE (per unit): $%.2f\n\n"reset, 
    item_t[i].itemId,
    item_t[i].itemName,
    item_t[i].itemQty,
    item_t[i].itemPrice);
  }

  plotStockListMenu();
  int choice;
  printf(BWHT"\n[+] Enter your choice: "reset);
  scanf("%i", &choice);
  stockListControl(savedStockFile, item_t, choice, lines);
}


/************************************************
 * Edit item                                    *
 ************************************************/

int 
searchItemId (stockData *item_t, int itemId, int infLim, int supLim) {
  int middle;
  if (infLim > supLim) {
    return -1;
  }

  if (itemId == item_t[0].itemId) {
    middle = 0;
    return middle;
  }

  else{
    middle = (infLim + supLim) / 2;
    if (itemId < item_t[middle].itemId) {
      return searchItemId(item_t, itemId, infLim, middle - 1);
    } else {
      if (itemId > item_t[middle].itemId) {
        return searchItemId(item_t, itemId, middle + 1, supLim);
      } else {
        return middle;
      }
    }
  }
}


void 
editItemControl (FILE *savedStockFile, stockData *item_t, int index) {
  char choice;
  printf("%s", warnings[7]);
  setbuf(stdin, NULL);
  scanf("%c", &choice);

  switch (choice) {
    case 'Y':
    case 'y': {
      editItemInformation(item_t, index);
      break;
    }
    case 'N':
    case 'n': {
      showStockList();
      break;
    }
    default: {
      printf("%s", warnings[0]);
      sleep(SECONDS);
      getchar();
      return editItemControl(savedStockFile, item_t, index);
      break;
    }
  }
}


void 
editItemInformation (stockData *item_t, int index) {
  plotEditItemHeader();
  printf(YEL"\n [1] NAME: %s\n [2] QTY: %i\n [3] PRICE (per unit): \
$%.2f\n\n"reset, 
  item_t->itemName,
  item_t->itemQty,
  item_t->itemPrice);
  putBar();

  int choice;
  printf("%s", warnings[8]);
  setbuf(stdin, NULL);
  scanf("%i", &choice);

  FILE *stockTempFile;
  FILE *savedStockFile;

  if (savedStockFile == NULL || stockTempFile == NULL) {
    perror(warnings[1]);
    exit(1);
  }

  savedStockFile = fopen(STOCK_REGISTRATION_DATA, "r");
  stockTempFile = fopen(STOCK_REGISTRATION_DATA_TMP, "w");

  switch(choice) {
    case 1: {
      printf(BWHT"\n[+] Enter the new item name: "reset);
      setbuf(stdin, NULL);
      scanf("%[^\n]s", item_t[index].itemName);
      break;
    }

    case 2: {
      printf(BWHT"\n[+] Enter the new item quantity: "reset);
      setbuf(stdin, NULL);
      scanf("%i", &item_t[index].itemQty);
      break;
    }

    case 3: {
      printf(BWHT"\n[+] Enter the new item price (per unit): "reset);
      setbuf(stdin, NULL);
      scanf("%f", &item_t[index].itemPrice);
      break;
    }

    default: {
      printf("%s", warnings[0]);
      sleep(SECONDS);
      getchar();
      return editItemInformation(item_t, index);
      break;
    }
  }

  char newline[BUFFER];
  char buffer[BUFFER];

  fprintf(stockTempFile, "%i %s %i %f\n",
  item_t->itemId,
  item_t->itemName,
  item_t->itemQty,
  item_t->itemPrice);

  fgets(newline, BUFFER, savedStockFile);

  int count = 0;

  while ((fgets(buffer, BUFFER, savedStockFile)) != NULL) {
    count++;
    if (count == index) {
      fputs(newline, stockTempFile);
    }
    else {
      fputs(buffer, stockTempFile);
    }
  }

  sleep(SECONDS);
  putchar('\n');
  putBar();
  printf("%s", warnings[9]);
  printf("%s", warnings[10]);
  getchar();

  freeStockListMemory(stockTempFile, item_t);
  fclose(savedStockFile);
  savedStockFile = NULL;

  remove(STOCK_REGISTRATION_DATA);
  rename(STOCK_REGISTRATION_DATA_TMP, STOCK_REGISTRATION_DATA);

  getchar();
  initialMenu(2);
}


/************************************************
 * Delete item                                  *
 ************************************************/

void 
deleteItemControl (FILE *savedStockFile, stockData *item_t, int index) {
  char choice;
  printf("%s", warnings[11]);
  setbuf(stdin, NULL);
  scanf("%c", &choice);

  switch (choice) {
    case 'Y':
    case 'y': {
      deleteItemInformation(item_t, index);
      break;
    }
    case 'N':
    case 'n': {
      showStockList();
      break;
    }
    default: {
      printf("%s", warnings[0]);
      sleep(SECONDS);
      getchar();
      return deleteItemControl(savedStockFile, item_t, index);
      break;
    }
  }
}


void 
deleteItemInformation (stockData *item_t, int index) {
  plotDeleteItemHeader();
  printf(RED"\n [1] Name: %s\n [2] QTY: %i\n [3] PRICE (per unit): \
$%.2f\n\n"reset, 
  item_t->itemName,
  item_t->itemQty,
  item_t->itemPrice);
  putBar();

  FILE *stockTempFile;
  FILE *savedStockFile;

  if (savedStockFile == NULL || stockTempFile == NULL) {
    perror(warnings[1]);
    exit(1);
  }

  savedStockFile = fopen(STOCK_REGISTRATION_DATA, "r");
  stockTempFile = fopen(STOCK_REGISTRATION_DATA_TMP, "w");

  char buffer[BUFFER];
  char string[BUFFER];

  int count = 0;

  while ((fgets(buffer, BUFFER, savedStockFile)) != NULL) {
    strcpy(string, "\0");
    if (count != index) {
      fputs(buffer, stockTempFile);
    }
    count++;
  }

  sleep(SECONDS);
  printf("%s", warnings[12]);
  printf("%s", warnings[10]);
  getchar();

  freeStockListMemory(stockTempFile, item_t);
  fclose(savedStockFile);
  savedStockFile = NULL;

  remove(STOCK_REGISTRATION_DATA);
  rename(STOCK_REGISTRATION_DATA_TMP, STOCK_REGISTRATION_DATA);

  getchar();
  initialMenu(2);
}


void 
checkItemId (FILE *savedStockFile, stockData *item_t, int lines, int flag) {
  if (flag == 0) {
    plotEditItemHeader();
  } else {
    plotDeleteItemHeader();
  }

  int itemId;
  printf(BWHT"\n[+] Enter the item ID: "reset);
  setbuf(stdin, NULL);
  scanf("%i", &itemId);

  int index = searchItemId(item_t, itemId, 0, lines);

  if (index == -1) {
    printf("%s", warnings[5]);
    sleep(SECONDS);
    return checkItemId(savedStockFile, item_t, lines, flag);
  } else {
    printf("%s", warnings[6]);
    sleep(SECONDS);
    if (flag == 0) {
      editItemControl(savedStockFile, item_t, index);
    } else {
      deleteItemControl(savedStockFile, item_t, index);
    }
  }
}