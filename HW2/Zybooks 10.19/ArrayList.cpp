#include "ArrayList.h"
#include <cstring>
#define ADDLENGTH 4
#define EMPTY 0


ArrayList::ArrayList() {
    myList = new string[EMPTY];
    length = 0;
    itemNum = 0;
}


// copy constructor
ArrayList::ArrayList(const ArrayList& listCopy) {
    myList = new string[listCopy.length];
    for (int i = 0; i < listCopy.itemNum; i++) {
        myList[i] = listCopy.myList[i];
    }

    itemNum = listCopy.itemNum;
    length = listCopy.length;
}



ArrayList::~ArrayList() {
    delete[] myList;
}


bool ArrayList::empty() const {
    return itemNum == 0;
}

int ArrayList::size() const {
    return itemNum;
}

// makes a copy of data item
void ArrayList::push_back(const string& str) {
    if (itemNum < length) {
        myList[itemNum] = str;
        itemNum++;
    }
    else {
        string* tempList = new string[length + ADDLENGTH];
        length = length + ADDLENGTH;
        for (int i = 0; i < itemNum; i++) {
            tempList[i] = myList[i];
        }
        delete[] myList;
        myList = tempList;
        myList[itemNum] = str;
        itemNum++;
    }
}


void ArrayList::push_front(const string& str) {
    if (itemNum < length) {
        for (int i = length - 1; i > 0; i--) {
            myList[i] = myList[i - 1];
        }
        myList[0] = str;
        itemNum++;
    }
    else {
        string* tempList = new string[length + ADDLENGTH];
        length = length + ADDLENGTH;
        for (int i = 0; i < itemNum; i++) {
            tempList[i+1] = myList[i];
        }
        delete[] myList;
        myList = tempList;
        myList[0] = str;
        itemNum++;
    }

}

// sets str to a copy of the item removed
bool ArrayList::pop_back(string& str) {
    if(itemNum == 0) return false;

    str = myList[itemNum - 1];
    myList[itemNum -1] = "\0";
    itemNum--;
    return true;
}

bool ArrayList::pop_front(string& str) {
    if(itemNum == 0) return false;

    str = myList[0];
    for (int i = 0; i < length; i++) {
        myList[i] = myList[i+1];
    }
    itemNum--;
    return true;
}