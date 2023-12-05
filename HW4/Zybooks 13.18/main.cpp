#include <iostream>
#include <random>
#include <list>
#include "IntBSTree.h"

int main()
{
    //std::random_device generator;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> dist(0,1000);

    IntBSTree b2;
    std::cout << "Insert:" << std::endl;
    for(int i=0; i<20; i++)
    {
        int n = dist(generator);
        std::cout << n << ' ';
        b2.insert(n);
    }
    std::cout << std::endl;

    std::list<int> l2 = b2.getOrderedList();

    std::cout << "Print list: " << std::endl;
    for (auto i : l2) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    std::cout << "Check list: ";
    bool ordered { true };
    int val { l2.front() };
    auto iter { l2.begin() };
    ++iter;
    while (iter != l2.end()) {
        if (*iter < val) { ordered = false; break; }
        val = *iter;
        ++iter;
    }
    if (ordered) std::cout << "CORRECT" << std::endl;
    else std::cout << "INCORRECT ORDER" << std::endl;

    return 0;
}

