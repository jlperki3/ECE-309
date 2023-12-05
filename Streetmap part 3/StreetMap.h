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
#include <fstream>
#include "Node.h"
#include "Way.h"
#include "HashTable.h"
#include "Graph.h"

struct RoutePart {
    WayPtr way = nullptr;       // follow this Way...
    double distance = 0.0;      // ... for this distance ...
    NodePtr toNode = nullptr;   // ... ending at this Node
};
using Route = vector<RoutePart>;

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

    // can get just the length of the shortest route...
    double shortestRoute(long long start, long long end);
    // or get the length and the step-by-step directions
    // (pass in a reference to the Route object where you want the directions)
    double shortestRoute(long long start, long long end, Route& r);

    // function to give access to the route graph -- this would normally not be part
    // of the design, but it allows us to better test your implementation
    Graph<long long,double>& graph() { return routeGraph; }
private:
    HashTable<long long, NodePtr> nodes;
    WayList ways;
    Graph<long long,double> routeGraph;  // undirected graph: vertex = Node, weight = distance (double)
};


#endif //ECE309_SPR23_STREETMAP_STREETMAP_H
