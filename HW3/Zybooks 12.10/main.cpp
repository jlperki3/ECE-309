#include <iostream>
#include "HashTable.h"

int main()
{
    HashTable myset(10);
    std::cout << "Hash table has " << myset.getNumElements() << " elements." << std::endl;

    std::cout << "Insert 0." << std::endl;
    myset.insert(0);

    std::cout << "Hash table has " << myset.getNumElements() << " elements." << std::endl;

    std::cout << "Insert another 0." << std::endl;
    myset.insert(0);

    std::cout << "Hash table has " << myset.getNumElements() << " elements." << std::endl;
    std::cout << "Should be 1, because 0 was already inserted." << std::endl;

    std::cout << "Insert 1." << std::endl;
    myset.insert(1);

    std::cout << "Hash table has " << myset.getNumElements() << " elements." << std::endl;

    std::cout << "Remove 0." << std::endl;
    myset.remove(0);

    if (!myset.find(0)) {
        std::cout << "Success: didn't find 0!" << std::endl;
    } else {
        std::cout << "Error: found 0!" << std::endl;
    }

    return 0;
}
