#include "gtest/gtest.h"
#include "../HashTable.h"
#include <random>
#include <chrono>
#include <set>

TEST(HashExtraSuite, Collisions) {
    HashTable<int, int> h{511};
    // insert a lot of numbers which are the same, modulo 511
    h.max_load_factor(10);   // allow larger bucket sizes
    int i{13};
    for (int j{0}; j < 200; ++j) {
        EXPECT_TRUE(h.insert(i, i));
        i += 511;
    }
    EXPECT_EQ(h.size(), 200);
}

TEST(HashExtraSuite, InsertAndRemove) {
    HashTable<size_t, size_t> h { 100 };
    const size_t numValues { 500 };

    std::minstd_rand gen;
    auto seed { std::chrono::system_clock::now().time_since_epoch().count() };
    gen.seed(seed);
    std::set<size_t> values;  // put in a set, so that we don't have duplicates
    size_t count {0};
    while (count < numValues) {
        size_t v { static_cast<size_t>(gen()) };
        values.insert(v);
        if (values.size() > count) ++count;
    }
    // put values into an array, to allow easy indexing
    size_t numbers[numValues];
    size_t index {0};
    for (auto val : values) {
        numbers[index++] = val;
    }
    // insert 50, remove and insert 10, remove 15
    // do this 10 times
    for (size_t outer {0}; outer < 10; ++outer ) {
        size_t inner = outer * 50;
        size_t dummy;
        for (size_t i { inner}; i < inner+50; ++i) {
            EXPECT_TRUE(h.insert(numbers[i],numbers[i]));
            EXPECT_TRUE(h.find(numbers[i], dummy));
        }
        for (size_t i { inner + 10 } ; i < inner + 20; ++i) {
            EXPECT_TRUE(h.erase(numbers[i], dummy));
            EXPECT_FALSE(h.find(numbers[i], dummy));
            EXPECT_TRUE(h.insert(numbers[i], numbers[i]));
            EXPECT_TRUE(h.find(numbers[i], dummy));
        }
        for (size_t i { inner+1 } ; i < inner + 45; i += 3) {
            EXPECT_TRUE(h.erase(numbers[i], dummy));
            EXPECT_FALSE(h.find(numbers[i], dummy));
        }
    }
    EXPECT_EQ(h.size(), 350);
}