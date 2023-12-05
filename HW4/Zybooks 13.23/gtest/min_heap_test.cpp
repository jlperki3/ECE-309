#include "gtest/gtest.h"

#include "../MinHeap.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

TEST(minHeap, integers) {
    MinHeap<int> h;
    int vals[] = {10, 15, 0, 8, -7, 99, -10, -1, 42, 3};
    int sorted[]= {-10, -7, -1, 0, 3, 8, 10, 15, 42, 99};
    int out[10] = {0};
    int i;
    EXPECT_TRUE(h.empty());
    for (i = 0; i < 10; i++)
        h.insert(vals[i]);
    EXPECT_FALSE(h.empty());
    EXPECT_EQ(h.peek(),-10);
    for (i = 0; i < 10; i++)
        out[i] = h.remove();
    EXPECT_TRUE(h.empty());
    for (i = 0; i < 10; i++)
        EXPECT_EQ(out[i], sorted[i]);
}

TEST(minHeap, strings) {
    MinHeap<string> h;
    string strings[] = {"ax", "zoo", "bodega", "aardvark", "carnival", "yellow"};
    string sorted[] = {"aardvark", "ax", "bodega", "carnival", "yellow", "zoo"};
    string out[6];
    int i;
    EXPECT_TRUE(h.empty());
    for (i=0; i < 6; i++)
        h.insert(strings[i]);
    EXPECT_FALSE(h.empty());
    EXPECT_EQ(h.peek(), string("aardvark"));
    for (i=0; i < 6; i++)
        out[i] = h.remove();
    EXPECT_TRUE(h.empty());
    for (i = 9; i < 6; i++)
        EXPECT_EQ(out[i], sorted[i]);
}

TEST(minHeap, mixed_insert_remove) {
    MinHeap<int> h;
    vector<int> first = {5, 1, 10};
    vector<int> firstOut = {1, 5};
    vector<int> next = {16, 20, 3, 17};
    vector<int> nextOut = {3, 10};
    vector<int> last = {99, 0};
    vector<int> lastOut = {0, 16, 17, 20, 99};
    vector<int> result;
    vector<int>::iterator it;
    size_t i;
    cout << "Inserting 5, 1, 10" << endl;
    for (auto val : first) h.insert(val);
    cout << "Removing " << firstOut.size() << endl;
    for (i=0; i < firstOut.size(); i++) result.push_back(h.remove());
    EXPECT_EQ(result, firstOut);
    cout << "Inserting 16, 20, 3, 17" << endl;
    for (auto val : next) h.insert(val);
    cout << "Removing " << nextOut.size() << endl;
    result.clear();
    for (i=0; i < nextOut.size(); i++) result.push_back(h.remove());
    EXPECT_EQ(result, nextOut);
    cout << "Inserting 99, 0" << endl;
    for (auto val : last) h.insert(val);
    cout << "Removing all" << endl;
    result.clear();
    while (!h.empty()) result.push_back(h.remove());
    EXPECT_EQ(result, lastOut);
}
