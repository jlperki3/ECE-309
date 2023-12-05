#include "gtest/gtest.h"
#include "../Way.h"
#include <string>
using std::string;

class WayFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // data for nodes to add to the Way
        double lat[numNodes] {38.8895061, 38.8896858, 38.8891478,
                              38.889755, 38.88951, 38.8899001};
        double lon[numNodes] {-77.0333179, -77.0349267, -77.0332038,
                              -77.0333595, -77.0333082, -77.0335297};

        std::shared_ptr<Node> nodes[numNodes];
        size_t i;
        for (i = 0; i < numNodes; i++) {
            nodes[i] = std::make_shared<Node>(id[i], lat[i], lon[i]);
            w.addNode(nodes[i]);
        }
    }
    static const size_t numNodes = 6;
    long long id[numNodes] {804638194, 6505011749, 8313442339,
                            8313453708, 8313462910, 8319509248};
    Way w{1};
};

TEST_F(WayFixture, WayNodes) {
    for (auto x : id) {
        EXPECT_TRUE(w.lookupNode(x));
    }
    auto len = w.length();
    EXPECT_NEAR(len, 445.708, 0.01);
    EXPECT_EQ(w.lookupNode(42), nullptr);
}

TEST_F(WayFixture, WayPath) {
    EXPECT_TRUE(w.isPath());
    EXPECT_FALSE(w.isBuilding());
    // add initial point to make a closed area
    auto n = w.lookupNode(id[0]);
    w.addNode(n);
    EXPECT_FALSE(w.isPath());
}

TEST_F(WayFixture, WayCopy) {
    Way w2 {w};
    for (auto x : id) {
        EXPECT_TRUE(w.lookupNode(x));
    }
    auto len = w.length();
    EXPECT_NEAR(len, 445.708, 0.01);
}

TEST_F(WayFixture, WayTags) {
    auto n = w.lookupNode(id[0]);
    w.addNode(n);
    const size_t numTags = 4;
    // data for nodes to add to the Way
    string key[numTags] {"name", "opening_hours", "shop", "barrier"};
    string val[numTags] {"Washington Monument", "09:00-18:00", "gift", "retaining_wall"};
    size_t i;
    for (i = 0; i < numTags; i++) {
        w.addTag({key[i], val[i]});
    }
    for (i = 0; i < numTags; i++) {
        EXPECT_EQ(w.lookupTag(key[i]), val[i]);
    }
    EXPECT_FALSE(w.isBuilding());

    w.addTag({"building", "yes"});
    EXPECT_TRUE(w.isBuilding());
    // copy constructor
    Way w2(w);
    for (i = 0; i < numTags; i++) {
        EXPECT_EQ(w2.lookupTag(key[i]), val[i]);
    }
    // bogus tag
    auto vs = w.lookupTag("owner");
    EXPECT_TRUE(vs.empty());
}
