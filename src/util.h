#ifndef UTIL_H_
#define UTIL_H_
  #include "../lib/colors.h"

  #define PAYLOAD 1
  #define SECONDS 1.8
  #define BUFFER 1000

  #define STOCK_REGISTRATION_DATA \
  "../.data/storage/stock_registration_data.csv"
  #define STOCK_REGISTRATION_DATA_TMP \
  "../.data/storage/stock_registration_data_temp.csv"

  typedef enum {
    false,
    true
  } bool;

  int main();
  void initialMenu();
  void plotInitialMenu();
  void plotStockMenu();
  void plotRegisterItemHeader();
  void plotStockListHeader();
  void plotStockListMenu();
  void plotEditItemHeader();
  void plotDeleteItemHeader();
  void registerItem();
  void saveStockRegistrationData();
  void showStockList();
  void checkItemId();
  void editItemInformation();
  void deleteItemInformation();
  void inputItemRegistrationData();

  int printCenter();
  void putBar();

  extern const char * const warnings[];

  typedef struct stockStruct {
    int    itemId;
    int    itemQty;
    char   itemName[100];
    float  itemPrice;
  } stockData;
#endif