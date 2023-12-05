#include "gtest/gtest.h"
#include "../StreetMap.h"
#include <iostream>

bool findWay(long long id, const WayList& ways) {
    for (auto & wp : ways) {
        if (wp->getID() == id) return true;
    }
    return false;
}
bool checkNode(long long id, const WayList& ways) {
    for (auto& wp : ways) {
        if (!wp->lookupNode(id)) return false;
    }
    return true;
}

TEST(MapSuite, NodeWays) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    NodePtr np { sm.lookupNode(1134999078) };
    ASSERT_NE(np, nullptr);
    WayList ways { np->getWays() };
    EXPECT_EQ(ways.size(), 1);
    EXPECT_TRUE(checkNode(1134999078, ways));
    EXPECT_TRUE(findWay(618046706, ways));

    np = sm.lookupNode(475887488);
    ASSERT_NE(np, nullptr);
    ways = np->getWays();
    EXPECT_EQ(ways.size(), 3);
    EXPECT_TRUE(checkNode(475887488, ways));
    EXPECT_TRUE(findWay(52629107, ways));
    EXPECT_TRUE(findWay(164068783, ways));
    EXPECT_TRUE(findWay(922520926, ways));

    np = sm.lookupNode(939557167);
    ASSERT_NE(np, nullptr);
    ways = np->getWays();
    EXPECT_EQ(ways.size(), 0);
}

TEST(MapSuite, Intersecting) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    WayPtr wp1 { sm.lookupWay(686923265) };
    ASSERT_NE(wp1, nullptr);
    WayPtr wp2 { sm.lookupWay(405686510) };
    ASSERT_NE(wp2, nullptr);
    EXPECT_TRUE(wp1->intersects(*wp2));
    EXPECT_TRUE(wp2->intersects(*wp1));
    wp2 = sm.lookupWay(297297483);
    ASSERT_NE(wp2, nullptr);
    EXPECT_TRUE(wp1->intersects(*wp2));
    EXPECT_TRUE(wp2->intersects(*wp1));
    wp2 = sm.lookupWay(686923263);
    ASSERT_NE(wp2, nullptr);
    EXPECT_FALSE(wp1->intersects(*wp2));
    EXPECT_FALSE(wp2->intersects(*wp1));
}

TEST(MapSuite, Intersections) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/Stanford.osm"));
    WayPtr wp { sm.lookupWay(48162044) };
    ASSERT_NE(wp, nullptr);
    NodeList nodes { wp->intersections() };
    EXPECT_EQ(nodes.size(), 3);
    EXPECT_EQ(nodes.at(0)->getID(), 354798545);
    EXPECT_EQ(nodes.at(1)->getID(), 612016132);
    EXPECT_EQ(nodes.at(2)->getID(), 5444520495);

    wp = sm.lookupWay(50372781);
    ASSERT_NE(wp, nullptr);
    nodes = wp->intersections();
    EXPECT_EQ(nodes.size(), 0);

    wp = sm.lookupWay(597275244);
    ASSERT_NE(wp, nullptr);
    nodes = wp->intersections();
    EXPECT_EQ(nodes.size(), 8);
    EXPECT_EQ(nodes.at(0)->getID(), 65622248);
    EXPECT_EQ(nodes.at(1)->getID(), 65430685);
    EXPECT_EQ(nodes.at(2)->getID(), 6106912808);
    EXPECT_EQ(nodes.at(3)->getID(), 65445286);
    EXPECT_EQ(nodes.at(4)->getID(), 6106912807);
    EXPECT_EQ(nodes.at(5)->getID(), 6444483882);
    EXPECT_EQ(nodes.at(6)->getID(), 6444483881);
    EXPECT_EQ(nodes.at(7)->getID(), 5691285400);
}

TEST(MapSuite, PathDistance) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/Stanford.osm"));
    WayPtr wp { sm.lookupWay(665211854) };
    ASSERT_NE(wp, nullptr);
    NodePtr n1 { sm.lookupNode(6226253354) };
    ASSERT_NE(n1, nullptr);
    NodePtr n2 { sm.lookupNode(6226253352) };
    ASSERT_NE(n2, nullptr);
    EXPECT_NEAR(wp->distance(n1,n2), 98.3642, 0.01);
    EXPECT_NEAR(wp->distance(n2,n1), 98.3642, 0.01);
    EXPECT_EQ(wp->distance(n1,n1), 0);

    n2 = sm.lookupNode(4912961687);  // not on this Way
    ASSERT_NE(n2, nullptr);
    EXPECT_EQ(wp->distance(n1,n2), -1);
}

TEST(MapSuite, ClosestIntersection) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    WayPtr wp { sm.lookupWay(135691898) };
    ASSERT_NE(wp, nullptr);
    // node whose closest information comes later in the list
    NodePtr n { wp->lookupNode(1489843499) };
    ASSERT_NE(n, nullptr);
    NodePtr cx { wp->closestIntersection(n) };
    ASSERT_NE(cx, nullptr);
    EXPECT_EQ(cx->getID(), 1489843617);

    // node whose closest information comes earlier in the list
    n = wp->lookupNode(1489843621);
    ASSERT_NE(n, nullptr);
    cx = wp->closestIntersection(n);
    ASSERT_NE(cx, nullptr);
    EXPECT_EQ(cx->getID(), 1489843519);

    // node that is itself an intersection -- must not return self
    n = wp->lookupNode(3011697027);
    ASSERT_NE(n, nullptr);
    cx = wp->closestIntersection(n);
    ASSERT_NE(cx, nullptr);
    EXPECT_NE(cx->getID(), 3011697027);

    // Way that has no intersections
    wp = sm.lookupWay(96596897);
    ASSERT_NE(wp, nullptr);
    n = wp->lookupNode(1118919174);
    ASSERT_NE(n, nullptr);
    cx = wp->closestIntersection(n);
    EXPECT_EQ(cx, nullptr);

}
