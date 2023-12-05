#include "gtest/gtest.h"
#include "../Node.h"

TEST(NodeTestSuite, BasicNode) {
    long long nodeID{123456};
    double nodeLat{88.7676767};
    double nodeLon{-33.45654};
    Node n1{nodeID, nodeLat, nodeLon};
    EXPECT_EQ(n1.getID(), nodeID);
    EXPECT_EQ(n1.getLatitude(), nodeLat);
    EXPECT_EQ(n1.getLongitude(), nodeLon);
}

TEST(NodeTestSuite, CopyNode) {
    long long nodeID{123456};
    double nodeLat{88.7676767};
    double nodeLon{-33.45654};
    Node n1{nodeID, nodeLat, nodeLon};
    Node n2{n1};
    EXPECT_EQ(n2.getID(), nodeID);
    EXPECT_EQ(n2.getLatitude(), nodeLat);
    EXPECT_EQ(n2.getLongitude(), nodeLon);
};

TEST(NodeTestSuite, Distance) {
    long long id[] { 123, 456 };
    double lat[] { 35.7728793, 35.7726659, };  // data taken from nodes in micro_map.osm
    double lon[] { -78.675507, -78.6750245 };
    Node n1 { id[0], lat[0], lon[0] }, n2 { id[1], lat[1], lon[1] };
    double d = n1.distance(n2);
    EXPECT_NEAR(d, 49.6325, 0.01);
}