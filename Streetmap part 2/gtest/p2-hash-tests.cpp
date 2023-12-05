#include "gtest/gtest.h"
#include "../HashTable.h"
#include <string>

using std::string, std::string_view;

#include <iostream>

using std::cout, std::endl;

// Sample tests for HashTable<K,T>

TEST(HashTestSuite, Basic) {
    std::hash<int> hasher;
    HashTable<int, int> h;
    EXPECT_EQ(h.buckets(), 511);
    EXPECT_TRUE(h.empty());
    EXPECT_EQ(h.size(), 0);
    EXPECT_EQ(h.keyToBucket(1234), hasher(1234) % h.buckets());

    HashTable<int, int> h2{777};
    EXPECT_EQ(h2.buckets(), 777);
    EXPECT_EQ(h2.keyToBucket(1234), hasher(1234) % h2.buckets());
}

TEST(HashTestSuite, IntKey_IntValue) {
    HashTable<int, int> h;
// numbers to insert
    int numbers[20] = {12, 19, 104, 111111, 9708,
                       -77, 1234, 65, 77, 992,
                       212223, -720, 815, 1630, 400,
                       1, -1, 0, 128, 1023};
    EXPECT_TRUE(h.empty());
    EXPECT_EQ(h.buckets(), 511);  // default # buckets
    for (auto n: numbers) {
        EXPECT_TRUE(h.insert(n, n));
    }
    EXPECT_EQ(h.size(), 20);
    EXPECT_FALSE(h.empty());

    int val{0};
    EXPECT_TRUE(h.find(1234, val));
    EXPECT_EQ(val, 1234);
    EXPECT_TRUE(h.find(212223, val));
    EXPECT_EQ(val, 212223);
    EXPECT_FALSE(h.find(555, val));
    EXPECT_EQ(val, 212223);  // val should not change

    EXPECT_TRUE(h.erase(111111, val));
    EXPECT_EQ(val, 111111);
    EXPECT_FALSE(h.find(111111, val));

    EXPECT_TRUE(h.erase(-720, val));
    EXPECT_EQ(val, -720);
    EXPECT_FALSE(h.find(-729, val));

    EXPECT_EQ(h.size(), 18);
}

TEST(HashTestSuite, Clear) {
    HashTable<int, int> h;
// numbers to insert
    int numbers[20] = {12, 19, 104, 111111, 9708,
                       -77, 1234, 65, 77, 992,
                       212223, -720, 815, 1630, 400,
                       1, -1, 0, 128, 1023};
    EXPECT_TRUE(h.empty());
    EXPECT_EQ(h.buckets(), 511);  // default # buckets
    for (auto n: numbers) {
        EXPECT_TRUE(h.insert(n, n));
    }
    EXPECT_EQ(h.size(), 20);
    EXPECT_FALSE(h.empty());

    h.clear();
    EXPECT_TRUE(h.empty());
    EXPECT_EQ(h.buckets(), 511);
    int val{0};
    EXPECT_FALSE(h.find(212223, val));
}

TEST(HashTestSuite, StrKey_IntValue) {
    HashTable<string, int> h;
// numbers to insert
    string keys[20] = {"12", "19", "104", "111111", "9708",
                       "-77", "1234", "65", "77", "992",
                       "212223", "-720", "815", "1630", "400",
                       "1", "-1", "0", "128", "1023"};
    int numbers[20] = {12, 19, 104, 111111, 9708,
                       -77, 1234, 65, 77, 992,
                       212223, -720, 815, 1630, 400,
                       1, -1, 0, 128, 1023};
    EXPECT_TRUE(h.empty());
    EXPECT_EQ(h.buckets(), 511);  // default # buckets
    for (size_t i{0}; i < 20; ++i) {
        EXPECT_TRUE(h.insert(keys[i], numbers[i]));
    }
    EXPECT_EQ(h.size(), 20);
    EXPECT_FALSE(h.empty());

    int val{0};
    EXPECT_TRUE(h.find("1234", val));
    EXPECT_EQ(val, 1234);
    EXPECT_TRUE(h.find("212223", val));
    EXPECT_EQ(val, 212223);
    EXPECT_FALSE(h.find("555", val));
    EXPECT_EQ(val, 212223);  // val should not change

    EXPECT_TRUE(h.erase("111111", val));
    EXPECT_EQ(val, 111111);
    EXPECT_FALSE(h.find("111111", val));

    EXPECT_TRUE(h.erase("-720", val));
    EXPECT_EQ(val, -720);
    EXPECT_FALSE(h.find("-729", val));

    EXPECT_EQ(h.size(), 18);
}

TEST(HashTestSuite, IntKey_ObjVal) {
    class Student {
    public:
        string firstName{""};
        string lastName{""};
        long long ID;

        Student() = default;

        Student(string_view first, string_view last, long long num)
                : firstName{first}, lastName{last}, ID{num} {}
    };
    HashTable<long long, Student> h;
// students to insert
    Student students[10] = {{"Atticus", "Finch",      8036488220},
                            {"Scout",   "Finch",      5558675309},
                            {"Tom",     "Robinson",   1089782773},
                            {"Dill",    "Harris",     7987963138},
                            {"Maudie",  "Atkinson",   1231239876},
                            {"Link",    "Deas",       1000000001},
                            {"Heck",    "Tate",       9199199199},
                            {"Walter",  "Cunningham", 4309896712},
                            {"Jeremy",  "Finch",      8328329900},
                            {"Dolphus", "Raymond",    3927480917}};
    EXPECT_TRUE(h.empty());
    EXPECT_EQ(h.buckets(), 511);  // default # buckets
    for (size_t i{0}; i < 10; ++i) {
        EXPECT_TRUE(h.insert(students[i].ID, students[i]));
    }
    EXPECT_EQ(h.size(), 10);
    EXPECT_FALSE(h.empty());

    Student s;
    EXPECT_TRUE(h.find(8036488220, s));
    EXPECT_STREQ(s.firstName.data(), "Atticus");
    EXPECT_STREQ(s.lastName.data(), "Finch");
    EXPECT_EQ(s.ID, 8036488220);
    EXPECT_TRUE(h.find(1089782773, s));
    EXPECT_STREQ(s.firstName.data(), "Tom");
    EXPECT_STREQ(s.lastName.data(), "Robinson");
    EXPECT_EQ(s.ID, 1089782773);
    EXPECT_FALSE(h.find(123412345, s));
    EXPECT_STREQ(s.firstName.data(), "Tom");
    EXPECT_STREQ(s.lastName.data(), "Robinson");
    EXPECT_EQ(s.ID, 1089782773);

    EXPECT_TRUE(h.erase(8328329900, s));
    EXPECT_STREQ(s.firstName.data(), "Jeremy");
    EXPECT_STREQ(s.lastName.data(), "Finch");
    EXPECT_EQ(s.ID, 8328329900);
    EXPECT_FALSE(h.find(8328329900, s));
    EXPECT_EQ(h.size(), 9);
}

/*
TEST(HashTestSuite, HashFunction) {

    HashTable<string, int> h;
    EXPECT_EQ(h.keyToBucket("1630"), 93);
    EXPECT_EQ(h.keyToBucket("212223"), 317);
    EXPECT_EQ(h.keyToBucket("-1"), 447);

// different number of buckets --> different hash function
    HashTable<string, int> h2{127};
    EXPECT_EQ(h2.keyToBucket("1630"), 100);
    EXPECT_EQ(h2.keyToBucket("212223"), 80);
    EXPECT_EQ(h2.keyToBucket("-1"), 23);

}*/

TEST(HashTestSuite, LoadFactor) {
    HashTable<int, int> h;
    EXPECT_EQ(h.max_load_factor(), 3);
    h.max_load_factor(1.5);
    EXPECT_EQ(h.max_load_factor(), 1.5);
}

TEST(HashTestSuite, Rehash) {
    HashTable<int, int> h{3};   // very small hash table
    // numbers to insert
    int numbers[20] = {12, 19, 104, 111111, 9708,
                       -77, 1234, 65, 77, 992,
                       212223, -720, 815, 1630, 400,
                       1, -1, 0, 128, 1023};
    h.max_load_factor(1.5);
    h.insert(numbers[0],numbers[0]);
    std::hash<int> hasher;
    EXPECT_EQ(h.keyToBucket(numbers[0]), hasher(numbers[0])%h.buckets());
    for (size_t j {0}; j < 20; ++j) {
        if (j > 0) {
            EXPECT_TRUE(h.insert(numbers[j], numbers[j]));
        }
        else {
            // duplicate should fail
            EXPECT_FALSE(h.insert(numbers[j], numbers[j]));
        }
    }
    cout << "Buckets after rehash: " << h.buckets() << endl;
    EXPECT_GT(h.buckets(), 3);
    EXPECT_EQ(h.keyToBucket(numbers[0]), hasher(numbers[0])%h.buckets());
}