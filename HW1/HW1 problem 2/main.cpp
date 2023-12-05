#include <iostream>
#include "cstring"
using namespace std;
class MyString {
public:
    MyString();
    ~MyString();
    MyString(const char *);

    bool empty();
    int size();
    bool contains(const char *input1);
private:
    char *newString;
};
//Memory allocation
MyString::MyString() {
newString[0] = '\0';
}
//Memory deallocation
MyString::~MyString() {
    delete newString;
}
//find the size of the passed variable workingString using strlen and add one to account for the null character
//set the class string size equal and copy the string into it
MyString::MyString(const char *workingString) {
    auto strSpace {strlen(workingString)};
    newString = new char[strSpace + 1];
    strcpy(newString, workingString);
}
//Check if newString is empty
bool MyString::empty() {
    if (newString == "") return true;
    else return false;
}
//Check the size of newString without inlcuding the null character. strlen does this
int MyString::size() {
    int len;
    len = strlen(newString);
    return len;
}
//check if string input1 occurs anywhere in the newString string
//if it does return true if not return false
bool MyString::contains(const char *input1) {
    char *subString = 0;
    subString = strstr(newString, input1);
    if (subString != 0) return true;
    else return false;

}

int main() {
    char *inputMain;
    cin >> inputMain;
    MyString test(inputMain);
    char otherTest[] = "test";

    test.size();
    test.empty();
    test.contains(otherTest);



    return 0;
}
