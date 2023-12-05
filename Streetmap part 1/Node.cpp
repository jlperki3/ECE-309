// Member functions and non-member functions related to Node

#include "Node.h"
#include <math.h>
using namespace std;

//parameterized constructor
Node::Node(long long id, double lat, double lon) {
    nodeID = id;
    latitude = lat;
    longitude = lon;
}

//copy constructor
Node::Node(const Node& copyNode) {
    nodeID = copyNode.nodeID;
    latitude = copyNode.latitude;
    longitude = copyNode.longitude;
}

//Operator overload
double operator-(const Node& firstPin, const Node& secondPin) {
    //double latitudeChange;
    //double longitudeChange;
    double pinOneLat;
    double pinTwoLat;
    double pinOneLon;
    double pinTwoLon;
    double distanceTot;


    pinOneLat = firstPin.getLatitude() / (180 / M_PI);
    pinTwoLat = secondPin.getLongitude() / (180 / M_PI);
    pinOneLon = firstPin.getLongitude() / (180 / M_PI);
    pinTwoLon = secondPin.getLongitude() / (180 / M_PI);

    double x = (pinOneLon - pinTwoLon) * cos((pinOneLat + pinTwoLat)/2.0);
    double y = pinOneLat - pinTwoLat;
    distanceTot = RADIUS * sqrt(x*x+y*y);

    return distanceTot;
}
