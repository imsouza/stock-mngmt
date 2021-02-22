#include "main.h"

/************************************************
 * Register item                                *
 ************************************************/

void 
freeStockListMemory (FILE *savedStockFile, stockData *item_t) {
  fclose(savedStockFile);
  savedStockFile = NULL;
  free(item_t);
}


void 
saveStockRegistrationData (stockData *item_t) {
  FILE *savedStockFile;
  savedStockFile = fopen(STOCK_REGISTRATION_DATA, "a");

  if (savedStockFile == NULL) {
    perror(warnings[1]);
    exit(1);
  }

  fprintf(savedStockFile, "%i %s %i %.2f\n", 
  item_t->itemId,
  item_t->itemName,
  item_t->itemQty,
  item_t->itemPrice);

  freeStockListMemory(savedStockFile, item_t);
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
      free(item_t);
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
  item_t = (struct stockStruct *) malloc(sizeof(struct stockStruct));

  if (item_t == NULL) {
    perror(warnings[1]);
    exit(1);
  }

  plotRegisterItemHeader();

  item_t->itemId = generateRandomId();

  inputItemRegistrationData(item_t);

  stockRegistryControl(item_t);
}


/************************************************
 * Show Stock List                              *
 ************************************************/

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
    case 1: {
      checkItemId(savedStockFile, item_t, lines, 0); 
      break;
    }
    case 2: {
      checkItemId(savedStockFile, item_t, lines, 1); 
      break;
    }
    case 3: {
      freeStockListMemory(savedStockFile, item_t); 
      initialMenu(2); 
      break;
    }
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
  item_t = (struct stockStruct *) malloc(BUFFER * sizeof(struct stockStruct));

  if (item_t == NULL) {
    perror(warnings[1]);
    exit(1);
  }

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
comparator (const void *x, const void *y) {
  int first  = ((struct stockStruct *) x)->itemId;
  int second = ((struct stockStruct *) y)->itemId;
  return (first - second);
}


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
editItemControl (stockData *item_t, int index) {
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
      free(item_t);
      showStockList();
      break;
    }
    default: {
      printf("%s", warnings[0]);
      sleep(SECONDS);
      getchar();
      return editItemControl(item_t, index);
      break;
    }
  }
}


void 
editItemInformation (stockData *item_t, int index) {
  plotEditItemHeader();
  printf(YEL" [1] NAME: %s\n [2] QTY: %i\n [3] PRICE (per unit): \
$%.2f\n\n"reset, 
  item_t[index].itemName,
  item_t[index].itemQty,
  item_t[index].itemPrice);
  putBar();

  int choice;
  printf("%s", warnings[8]);
  setbuf(stdin, NULL);
  scanf("%i", &choice);

  FILE *stockTempFile;
  FILE *savedStockFile;

  savedStockFile = fopen(STOCK_REGISTRATION_DATA, "r");
  stockTempFile = fopen(STOCK_REGISTRATION_DATA_TMP, "w");

  if (savedStockFile == NULL || stockTempFile == NULL) {
    perror(warnings[1]);
    exit(1);
  }

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

  fprintf(stockTempFile, "%i %s %i %.2f\n",
  item_t[index].itemId,
  item_t[index].itemName,
  item_t[index].itemQty,
  item_t[index].itemPrice);

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

  fclose(stockTempFile);
  fclose(savedStockFile);
  savedStockFile = NULL;
  stockTempFile = NULL;

  remove(STOCK_REGISTRATION_DATA);
  rename(STOCK_REGISTRATION_DATA_TMP, STOCK_REGISTRATION_DATA);

  free(item_t);
  getchar();
  initialMenu(2);
}


/************************************************
 * Delete item                                  *
 ************************************************/

void 
deleteItemControl (stockData *item_t, int index) {
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
      free(item_t);
      showStockList();
      break;
    }
    default: {
      printf("%s", warnings[0]);
      sleep(SECONDS);
      getchar();
      return deleteItemControl(item_t, index);
      break;
    }
  }
}


void 
deleteItemInformation (stockData *item_t, int index) {
  plotDeleteItemHeader();
  printf(RED"\n [1] Name: %s\n [2] QTY: %i\n [3] PRICE (per unit): \
$%.2f\n\n"reset, 
  item_t[index].itemName,
  item_t[index].itemQty,
  item_t[index].itemPrice);
  putBar();

  FILE *stockTempFile;
  FILE *savedStockFile;

  savedStockFile = fopen(STOCK_REGISTRATION_DATA, "r");
  stockTempFile = fopen(STOCK_REGISTRATION_DATA_TMP, "w");

  if (savedStockFile == NULL || stockTempFile == NULL) {
    perror(warnings[1]);
    exit(1);
  }

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

  fclose(stockTempFile);
  fclose(savedStockFile);
  savedStockFile = NULL;
  stockTempFile = NULL;

  remove(STOCK_REGISTRATION_DATA);
  rename(STOCK_REGISTRATION_DATA_TMP, STOCK_REGISTRATION_DATA);

  free(item_t);
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

  qsort(item_t, lines+1, sizeof(struct stockStruct), comparator);

  int index = searchItemId(item_t, itemId, 0, lines);

  if (index == -1) {
    printf("%s", warnings[5]);
    sleep(SECONDS);
    fclose(savedStockFile);
    free(item_t);
    showStockList();
  } else {
    printf("%s", warnings[6]);
    sleep(SECONDS);
    if (flag == 0) {
      fclose(savedStockFile);
      editItemControl(item_t, index);
    } else {
      fclose(savedStockFile);
      deleteItemControl(item_t, index);
    }
  }
}