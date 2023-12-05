#ifndef ECE309_SPR23_STREETMAP_STREETMAP_H
#define ECE309_SPR23_STREETMAP_STREETMAP_H

// StreetMap class
// Represents a map using OpenStreetMap data

// Node is a specified location with an ID.
// Way is a sequence of nodes that represents a path (e.g., street or stream),
// or an area (e.g., building or park).

#include <string>
#include <memory>
#include <vector>
#include <list>
#include "Node.h"
#include "Way.h"
#include "HashTable.h"

class StreetMap {
public:
    StreetMap() = default;

    // open and read OSM file, replacing old data (if any)
    bool readOSM(std::string_view filename);

    // Node-related methods
    size_t getNumNodes() const { return nodes.size(); };             // how many nodes?
    NodePtr lookupNode(long long id) const;   // find a specific node

    // Way-related methods
    size_t getNumWays() const { return ways.size(); };              // how many ways?
    WayPtr lookupWay(long long id) const;   // find way with specified ID
    WayList getBuildings() const;           // return a list of buildings
    WayList getPaths() const;               // return a list of paths (open-ended ways)
private:
    HashTable<long long, NodePtr> nodes;
    WayList ways;
};


#endif //ECE309_SPR23_STREETMAP_STREETMAP_H
