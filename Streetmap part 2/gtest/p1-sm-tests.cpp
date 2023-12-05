#include "gtest/gtest.h"
#include "../StreetMap.h"
#include <iostream>
using std::cout, std::endl;

TEST(StreetMapSuite, ReadFile_Nodes) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/micro_map.osm"));

    int n = sm.getNumNodes();
    EXPECT_EQ(n,7);

    long long id[] {373084187, 3599727535, 3599727536, 668387584,
                    3599727530, 3599727531, 373084188};
    double lat[] {35.7728793, 35.7729205, 35.77295, 35.7729994,
                  35.7726576, 35.7726954, 35.7726659};
    double lon[] {-78.675507, -78.6754721, -78.6755249, -78.6754831,
                  -78.6751094, -78.6750775, -78.6750245};
    NodePtr np;
    for (size_t i {3}; i != 2; i = (i+1)%7) {
        np = sm.lookupNode(id[i]);
        EXPECT_TRUE(np);
        if (np) {
            EXPECT_EQ(np->getID(), id[i]);
            EXPECT_EQ(np->getLatitude(), lat[i]);
            EXPECT_EQ(np->getLongitude(), lon[i]);
        }
    }
    np = sm.lookupNode(1234);   // non-existent node
    EXPECT_FALSE(np);
}

TEST(StreetMapSuite, ReadOneWay) {
    StreetMap sm;
    cout << "Reading micro_map.osm" << endl;
    ASSERT_TRUE(sm.readOSM("maps/micro_map.osm"));
    size_t num;
    // check the number of ways
    EXPECT_EQ(sm.getNumWays(),1);
    WayPtr wp {sm.lookupWay(33069336)};
    EXPECT_TRUE(wp);
    EXPECT_NEAR(wp->length(), 72.50335, 0.01);
}

TEST(StreetMapSuite, ReadFiles) {
    StreetMap sm;
    cout << "Reading ncsu_oval map file" << endl;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    EXPECT_EQ(sm.getNumNodes(), 1790);
    EXPECT_EQ(sm.getNumWays(), 353);

    cout << "Reading mystery map file" << endl;
    ASSERT_TRUE(sm.readOSM("maps/mystery.osm"));
    EXPECT_EQ(sm.getNumNodes(), 337);
    EXPECT_EQ(sm.getNumWays(), 19);

    cout << "Reading Stanford map file" << endl;
    ASSERT_TRUE(sm.readOSM("maps/Stanford.osm"));
    EXPECT_EQ(sm.getNumNodes(), 33091);
    EXPECT_EQ(sm.getNumWays(), 5576);
}

TEST(StreetMapSuite, ReadWays) {
    StreetMap sm;
    cout << "Reading ncsu_oval map file" << endl;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    ASSERT_EQ(sm.getNumWays(), 353);
    // lookup a few random ways and check them
    // Way 40941567 is EB3
    WayPtr wp { sm.lookupWay(40941567) };
    EXPECT_TRUE(wp);
    if (wp) {
        EXPECT_EQ(wp->getID(), 40941567);
        EXPECT_NEAR(wp->length(), 490.231, 0.01);
        EXPECT_TRUE(wp->isBuilding());
        auto val { wp->lookupTag("name") };
        EXPECT_STREQ(val.data(), "Engineering Building III");
    }
    //
    wp = sm.lookupWay(77068104);
    EXPECT_TRUE(wp);
    if (wp) {
        EXPECT_EQ(wp->getID(), 77068104);
        EXPECT_NEAR(wp->length(), 14.174, 0.01);
        EXPECT_TRUE(wp->isPath());
        auto val { wp->lookupTag("name") };
        EXPECT_STREQ(val.data(), "Oval Drive");
    }
    //
    wp = sm.lookupWay(297305755);
    EXPECT_TRUE(wp);
    if (wp) {
        EXPECT_EQ(wp->getID(), 297305755);
        EXPECT_NEAR(wp->length(), 103.986, 0.01);
        EXPECT_FALSE(wp->isPath());
        auto val { wp->lookupTag("leisure") };
        EXPECT_STREQ(val.data(), "park");
    }
}

TEST(StreetMapSuite, Buildings) {
    StreetMap sm;
    cout << "Reading ncsu_oval map file" << endl;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    auto bldgs { sm.getBuildings() };
    EXPECT_EQ(bldgs.size(), 32);
    // check to make sure all are marked as buildings
    for (auto iter {bldgs.begin()}; iter != bldgs.end(); ++iter) {
        auto wp{*iter};
        ASSERT_TRUE(wp->isBuilding());
    }
}

TEST(StreetMapSuite, Paths) {
    StreetMap sm;
    cout << "Reading ncsu_oval map file" << endl;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    auto paths { sm.getPaths() };
    EXPECT_EQ(paths.size(), 272);
    // check to make sure all are marked as buildings
    for (auto iter {paths.begin()}; iter != paths.end(); ++iter) {
        auto wp{*iter};
        ASSERT_TRUE(wp->isPath());
    }
}