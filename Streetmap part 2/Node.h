#ifndef ECE309_SPR23_STREETMAP_NODE_H
#define ECE309_SPR23_STREETMAP_NODE_H
// Node is a specified location.
// ID is a 64-bit integer.
// Latitude and Longitude are 64-bit floating-point values.

// Methods may be implemented here or in Node.cpp.

#include <memory>
class Node;
using NodePtr = std::shared_ptr<Node>;
#include "Way.h"

class Node {
public:
    // constructor requires ID, latitude, and longitude
    Node(long long id, double lat, double lon)
    : ID{id}, latitude{lat}, longitude{lon} {}
    // no need for destructor
    // add a copy constructor
    Node(const Node& other) = default;
    // Part 2 code
    void addWay(const WayPtr& way) { nodeWays.push_back(way); }

    // return node information
    long long getID() const { return ID; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    double distance(const Node&) const;
    // Part 2 code
    const WayList& getWays() const { return nodeWays; }

private:
    long long ID;
    double latitude;
    double longitude;
    WayList nodeWays;
};


#endif //ECE309_SPR23_STREETMAP_NODE_H
