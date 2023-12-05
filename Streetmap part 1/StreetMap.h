#ifndef ECE309_SPR23_STREETMAP_STREETMAP_H
#define ECE309_SPR23_STREETMAP_STREETMAP_H

// StreetMap class
// Represents a map using OpenStreetMap data

// Node is a specified location with an ID.
// Way is a sequence of nodes that represents a path (e.g., street or stream),
// or an area (e.g., building or park).

#include <string>
#include "Node.h"
#include "Way.h"
#include <memory>

class StreetMap {
public:
    StreetMap() = default;    // constructor has no parameters
    // add destructor if needed

    // open and read OSM file, replacing old data (if any)
    bool readOSM(std::string_view filename);

    // Node-related methods
    size_t getNumNodes() const { return nodePtr.size(); }             // how many nodes?
    std::shared_ptr<Node> lookupNode(long long id) const;   // find a specific node

    // Way-related methods
    size_t getNumWays() const { return wayVec.size(); }              // how many ways?
    std::shared_ptr<Way> lookupWay(long long id) const;   // find way with specified ID
    WayList getBuildings() const;           // return a list of buildings
    WayList getPaths() const;               // return a list of paths (open-ended ways)

private:
    vector<std::shared_ptr<Node>> nodePtr;
    vector<std::shared_ptr<Way>> wayVec;
    int indexID = 0;
    string idString;
    long long id = 0;
    int indexLat = 0;
    string latString;
    double lat = 0;
    int indexLon = 0;
    string lonString;
    double lon = 0;
    long long wayID = 0;
    shared_ptr<Node> nodeToWay;
};



#endif //ECE309_SPR23_STREETMAP_STREETMAP_H
