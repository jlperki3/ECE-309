#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

#include <string>
using namespace std;

class ItemToPurchase {
public:
    ItemToPurchase();
    //ItemToPurchase(int price, int quantity);
    void SetName(string name);
    string GetName();
    void SetPrice(int price);
    int GetPrice();
    void SetQuantity(int quantity);
    int GetQuantity();

private:
    string itemName;
    int itemPrice;
    int itemQuantity;

};

#endif