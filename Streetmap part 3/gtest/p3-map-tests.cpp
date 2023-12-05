#include "gtest/gtest.h"
#include "../StreetMap.h"
#include <iostream>
#include <list>

using std::list, std::pair;

TEST(Part3Map, RouteGraph) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/part3.osm"));
    Graph<long long, double> &g{sm.graph()};
    EXPECT_EQ(g.numVertices(), 9);
    EXPECT_EQ(g.numEdges(), 11);
}

TEST(Part3Map, grey2purple) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/part3.osm"));
    double d{0};
    Route r;
    d = sm.shortestRoute(402, 602);
    EXPECT_NEAR(d, 2226.376, 0.01);
    d = 0;
    d = sm.shortestRoute(402, 602, r);
    EXPECT_NEAR(d, 2226.376, 0.01);
    EXPECT_EQ(r.size(), 1);
    ASSERT_NE(r[0].way, nullptr);
    EXPECT_STREQ(r[0].way->lookupTag("name").data(), "red");
}

struct routeData {
    const char *wayName;
    long long endNode;
    routeData(const char *n, long long e) : wayName(n), endNode(e) {}
};

TEST(Part3Map, blue2blue) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/part3.osm"));
    double d{0};
    Route r;
    d = sm.shortestRoute(104, 406);
    EXPECT_NEAR(d, 4430.367, 0.01);
    d = 0;
    d = sm.shortestRoute(104, 406, r);
    ASSERT_EQ(r.size(), 3);
    EXPECT_NEAR(d, 4430.367, 0.01);
    routeData steps[3]{{"blue",   204},
                       {"orange", 405},
                       {"blue",   406}};
    for (int s = 0; s < 3; ++s) {
        ASSERT_NE(r[s].way, nullptr);
        ASSERT_NE(r[s].toNode, nullptr);
        EXPECT_STREQ(r[s].way->lookupTag("name").data(), steps[s].wayName);
        EXPECT_EQ(r[s].toNode->getID(), steps[s].endNode);
    }
}

TEST(Part3Map, grey2red) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/part3.osm"));
    double d{0};
    Route r;
    d = sm.shortestRoute(0, 802);
    EXPECT_NEAR(d, 9556.689, 0.01);
    d = 0;
    d = sm.shortestRoute(0, 802, r);
    ASSERT_EQ(r.size(), 3);
    EXPECT_NEAR(d, 9556.689, 0.01);
    routeData steps[3]{{"grey",   200},
                       {"yellow", 402},
                       {"red",    802}};
    for (int s = 0; s < 3; ++s) {
        ASSERT_NE(r[s].way, nullptr);
        ASSERT_NE(r[s].toNode, nullptr);
        EXPECT_STREQ(r[s].way->lookupTag("name").data(), steps[s].wayName);
        EXPECT_EQ(r[s].toNode->getID(), steps[s].endNode);
    }
}

TEST(Part3Map, blue2green) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/part3.osm"));
    double d{0};
    Route r;
    d = sm.shortestRoute(7, 700);
    EXPECT_NEAR(d, 15261.669, 0.01);
    d = 0;
    d = sm.shortestRoute(7, 700, r);
    ASSERT_EQ(r.size(), 4);
    EXPECT_NEAR(d, 15261.669, 0.01);
    routeData steps[4]{{"blue",   405},
                       {"orange", 606},
                       {"purple", 600},
                       {"green",  700}};
    for (int s = 0; s < 4; ++s) {
        ASSERT_NE(r[s].way, nullptr);
        ASSERT_NE(r[s].toNode, nullptr);
        EXPECT_STREQ(r[s].way->lookupTag("name").data(), steps[s].wayName);
        EXPECT_EQ(r[s].toNode->getID(), steps[s].endNode);
    }
}

TEST(Part3Map, teal2red) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/part3.osm"));
    double d{100};
    Route r;
    d = sm.shortestRoute(201, 202);
    EXPECT_EQ(d, 0);
    d = 100;
    d = sm.shortestRoute(201, 202, r);
    EXPECT_EQ(r.size(), 0);
    EXPECT_EQ(d, 0);
}

TEST(OvalMap, RouteGraph) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    Graph<long long, double> &g{sm.graph()};
    EXPECT_EQ(g.numVertices(), 410);
    EXPECT_EQ(g.numEdges(), 467);
}

struct stepData {
    long long wayID;
    long long endNode;

    stepData(long long w, long long e) : wayID(w), endNode(e) {}
};

TEST(OvalMap, test1) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    double d{0};
    Route r;
    d = sm.shortestRoute(2438062203, 3011732378);
    EXPECT_NEAR(d, 363.179, 0.01);
    d = 0;
    d = sm.shortestRoute(2438062203, 3011732378, r);
    ASSERT_EQ(r.size(), 15);
    EXPECT_NEAR(d, 363.179, 0.01);
    stepData steps[15]{{135691892, 1489843592},
                       {135691898, 3011697027},
                       {297300833, 3011697032},
                       {425180199, 3011702132},
                       {297302356, 3011709255},
                       {297302357, 3011709254},
                       {297302343, 3011702918},
                       {297302342, 3011702919},
                       {297302340, 3011702917},
                       {297302341, 3011702916},
                       {297302338, 3011702915},
                       {297302339, 3011702914},
                       {297301238, 3011702366},
                       {297302728, 3011732377},
                       {297302729, 3011732378}};

    for (int s = 0; s < 15; ++s) {
        ASSERT_NE(r[s].way, nullptr);
        ASSERT_NE(r[s].toNode, nullptr);
        EXPECT_EQ(r[s].way->getID(), steps[s].wayID);
        EXPECT_EQ(r[s].toNode->getID(), steps[s].endNode);
    }
}

TEST(OvalMap, test2) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/ncsu_oval.osm"));
    double d{0};
    Route r;
    d = sm.shortestRoute(2438062229, 9990207555);
    EXPECT_NEAR(d, 659.112, 0.01);
    d = 0;
    d = sm.shortestRoute(2438062229, 9990207555, r);
    ASSERT_EQ(r.size(), 8);
    EXPECT_NEAR(d, 659.112, 0.01);
    stepData steps[8]{{235748823, 2438062212},
                      {406323603, 1489843493},
                      {135691898, 3011697027},
                      {297573379, 2470637719},
                      {239261986, 2470637720},
                      {664945215, 1489843532},
                      {664945216, 3011642681},
                      {287980262, 9990207555}};

    for (int s = 0; s < 8; ++s) {
        ASSERT_NE(r[s].way, nullptr);
        ASSERT_NE(r[s].toNode, nullptr);
        EXPECT_EQ(r[s].way->getID(), steps[s].wayID);
        EXPECT_EQ(r[s].toNode->getID(), steps[s].endNode);
    }
}
/*
TEST(StanfordMap, RouteGraph) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/Stanford.osm"));
    Graph<long long, double> &g{sm.graph()};
    EXPECT_EQ(g.numVertices(), 4664);
    EXPECT_EQ(g.numEdges(), 6445);
}

TEST(StanfordMap, test1) {
    StreetMap sm;
    ASSERT_TRUE(sm.readOSM("maps/Stanford.osm"));
    double d{0};
    Route r;
    d = sm.shortestRoute(340331917, 6226274927);
    EXPECT_NEAR(d, 1742.79, 0.01);
    d = 0;
    d = sm.shortestRoute(340331917, 6226274927, r);
    ASSERT_EQ(r.size(), 28);
    EXPECT_NEAR(d, 1742.79, 0.01);
    stepData steps[28]{{24772498,   5802972689},
                       {689431792,  354794271},
                       {694397287,  6332211530},
                       {696199097,  6332211531},
                       {906388232,  8416756855},
                       {676154806,  65613239},
                       {906388225,  8416756835},
                       {906388224,  8416756848},
                       {906388227,  8416756849},
                       {906388228,  256568263},
                       {23693550,   65484358},
                       {31705613,   5771900430},
                       {678227662,  9383029288},
                       {1017389194, 5852676327},
                       {630112789,  5852624893},
                       {630112785,  5852624896},
                       {1017389195, 9384053249},
                       {963300818,  9384053282},
                       {1017389225, 9384055029},
                       {1017395954, 1445851427},
                       {26250633,   287482249},
                       {81798743,   3678182393},
                       {363651037,  6226274999},
                       {665214502,  1725630456},
                       {81798744,   6226274937},
                       {665214496,  6226274938},
                       {665214493,  6226274944},
                       {665214489,  6226274927}};

    for (int s = 0; s < 28; ++s) {
        ASSERT_NE(r[s].way, nullptr);
        ASSERT_NE(r[s].toNode, nullptr);
        EXPECT_EQ(r[s].way->getID(), steps[s].wayID);
        EXPECT_EQ(r[s].toNode->getID(), steps[s].endNode);
    }
}*/