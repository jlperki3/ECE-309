#include <iostream>
#include "ArrayList.h"
using namespace std;
int main() {
    ArrayList test;

    test.push_front("one test");
    test.push_back("back test");

    for (int i = 0; i < 2775; i++) {
        test.push_front("test push");
    }

    ArrayList copied(test);
}
