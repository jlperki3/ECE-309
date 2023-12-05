#ifndef ECE309_SPR23_STREETMAP_NODE_H
#define ECE309_SPR23_STREETMAP_NODE_H

// Node is a specified location.
// ID is a 64-bit integer.
// Latitude and Longitude are 64-bit floating-point values.

// Methods may be implemented here or in Node.cpp.

#include <memory>
#include <vector>
#include <list>
#include <iostream>
using std::ostream;

// these types need to be defined before including Way.h
class Node;
using NodePtr = std::shared_ptr<Node>;
using NodeList = std::vector<NodePtr>;

#include "Way.h"

class Node {
public:
    // constructor requires ID, latitude, and longitude
    Node(long long id, double lat, double lon)
    : ID{id}, latitude{lat}, longitude{lon} {}
    // no need for destructor
    // add a copy constructor
    Node(const Node& other) = default;

    // return node information
    long long getID() const { return ID; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    double distance(const Node&) const;

    // WayList functions
    const WayList& getWays() const { return ways; }
    void addWay(const WayPtr& wp);

    // printing a node
    friend ostream& operator<<(ostream& out, const Node& n) {
        return out << "Node " << n.ID;
    }
private:
    long long ID;
    double latitude;
    double longitude;
    WayList ways;   // Ways that contain this Node -- constructed by addWay
};


#endif //ECE309_SPR23_STREETMAP_NODE_H
