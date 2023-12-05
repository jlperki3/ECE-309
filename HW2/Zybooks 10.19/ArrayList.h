#ifndef ZYBOOK_ARRAYLIST_H_
#define ZYBOOK_ARRAYLIST_H_

#include <string>
using std::string;

class ArrayList {
public:
   ArrayList();
   ArrayList(const ArrayList&);  // copy constructor
   ~ArrayList();
   bool empty() const;
   int size() const;
   void push_back(const string& str);  // makes a copy of data item
   void push_front(const string& str);
   bool pop_back(string& str);  // sets str to a copy of the item removed
   bool pop_front(string& str);

private:
    string* myList;
    int length;
    int itemNum;
};

#endif