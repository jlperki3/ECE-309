#include <iostream>
using namespace std;
#include "ItemToPurchase.h"

int main() {

ItemToPurchase item1;
ItemToPurchase item2;
string name;
int price;
int quantity;
int totPrice;

//Prompt user for Item 1 name
cout << "Item 1" << endl<< "Enter the item name:" << endl;
getline(cin, name);
item1.SetName(name);

//Prompt user for Item 1 price
cout << "Enter the item price:" << endl;
cin >> price;
item1.SetPrice(price);

//Prompt user for Item 1 quantity
cout << "Enter the item quantity:" << endl;
cin >> quantity;
item1.SetQuantity(quantity);
cout << endl;

cin.ignore();

//Prompt user for Item 2 name
    cout << "Item 2" << endl<< "Enter the item name:" << endl;
    getline(cin, name);
    item2.SetName(name);

//Prompt user for Item 2 price
    cout << "Enter the item price:" << endl;
    cin >> price;
    item2.SetPrice(price);

//Prompt user for Item 2 quantity
    cout << "Enter the item quantity:" << endl;
    cin >> quantity;
    cout << endl;
    item2.SetQuantity(quantity);

//Output the item's total cost
cout << "TOTAL COST" << endl;
cout << item1.GetName() << " " << item1.GetQuantity() << " @ $" << item1.GetPrice() << " = $" << item1.GetQuantity()*item1.GetPrice() <<endl;
cout << item2.GetName() << " " << item2.GetQuantity() << " @ $" << item2.GetPrice() << " = $" << item2.GetQuantity()*item2.GetPrice() <<endl;
cout << endl;
totPrice = (item1.GetQuantity()*item1.GetPrice())+(item2.GetQuantity()*item2.GetPrice()) ;//Get total price for both items combined
cout << "Total: $" << totPrice << endl;

    return 0;
}