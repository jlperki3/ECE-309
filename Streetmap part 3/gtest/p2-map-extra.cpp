#include "gtest/gtest.h"
#include "../StreetMap.h"
#include "math.h"


static bool findWay(long long id, const WayList& ways) {
    for (auto & wp : ways) {
        if (wp->getID() == id) return true;
    }
    return false;
}
static bool checkNode(long long id, const WayList& ways) {
    for (auto& wp : ways) {
        if (!wp->lookupNode(id)) return false;
    }
    return true;
}

TEST(MapExtraSuite, NodeWays) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    NodePtr np { sm.lookupNode(373083231) };
    ASSERT_NE(np, nullptr);
    WayList ways { np->getWays() };
    EXPECT_EQ(ways.size(), 4);
    EXPECT_TRUE(checkNode(373083231, ways));
    EXPECT_TRUE(findWay(33069316, ways));
    EXPECT_TRUE(findWay(352696783, ways));
    EXPECT_TRUE(findWay(352696784, ways));
    EXPECT_TRUE(findWay(352696786, ways));

    np = sm.lookupNode(1118919259);
    ASSERT_NE(np, nullptr);
    ways = np->getWays();
    EXPECT_EQ(ways.size(), 1);
    EXPECT_TRUE(checkNode(1118919259, ways));
    EXPECT_TRUE(findWay(96596897, ways));
}

static bool TwoWayFPCheck(double value, double ans1, double ans2, double accuracy) {
    bool pass = true;
    // value must be close to one of the two answers
    if ((abs(value - ans1) > accuracy) && (abs(value - ans2) > accuracy)) pass = false;
    return pass;
}

TEST(MapExtraSuite, PathDistance) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    WayPtr wp { sm.lookupWay(543895756) };
    ASSERT_NE(wp, nullptr);
    NodePtr n1 { sm.lookupNode(5257722952) };
    ASSERT_NE(n1, nullptr);
    NodePtr n2 { sm.lookupNode(5257722940) };
    ASSERT_NE(n2, nullptr);
    //EXPECT_NEAR(wp->distance(n1,n2), 52.48088, 0.01);
    //EXPECT_NEAR(wp->distance(n1,n2), 45.73776, 0.01);
    EXPECT_PRED4(TwoWayFPCheck, wp->distance(n1,n2), 52.48088, 45.73776, 0.01);

    wp = sm.lookupWay(1029356999);
    ASSERT_NE(wp, nullptr);
    n1 = sm.lookupNode(2915315432);
    ASSERT_NE(n1, nullptr);
    n2 = sm.lookupNode(5220460245);
    ASSERT_NE(n2, nullptr);
    EXPECT_NEAR(wp->distance(n1, n2), 199.6696, 0.01);
}


TEST(MapExtraSuite, ClosestIntersection) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/Stanford.osm"));
    WayPtr wp { sm.lookupWay(30775961) };
    ASSERT_NE(wp, nullptr);
    // node whose closest information comes later in the list
    NodePtr n { wp->lookupNode(5818757655) };
    ASSERT_NE(n, nullptr);
    NodePtr cx { wp->closestIntersection(n) };
    ASSERT_NE(cx, nullptr);
    EXPECT_EQ(cx->getID(), 5206902980);

    wp = sm.lookupWay(28592916);
    ASSERT_NE(wp, nullptr);
    n = wp->lookupNode(1782366287);
    ASSERT_NE(n, nullptr);
    cx = wp->closestIntersection(n);
    ASSERT_NE(cx, nullptr);
    EXPECT_EQ(cx->getID(), 314063894);
}