#ifndef ECE309_SPR23_STREETMAP_WAY_H
#define ECE309_SPR23_STREETMAP_WAY_H

// Way is a sequence of nodes.
// An open sequence (first and last nodes aren't the same) represents a path.
// A closed sequence (first and last nodes are the same) represents an area.
// A collection of tags gives information about the way.

// Can implement small methods here, but most code should reside in Way.cpp.

#include <string>
#include <utility>
#include <vector>
using std::vector;
using namespace std;
#include <memory>
#include "Node.h"

class Way {
public:
    explicit Way(long long id) { wayID = id; }  // constructor requires ID
    // add destructor if needed
    // add copy constructor

    // Node-related methods
    void addNode(std::shared_ptr<Node>&);   // add a new node to the end of the sequence
    std::shared_ptr<Node> lookupNode(long long id) const;

    // Tag-related methods
    using Tag = std::pair<std::string, std::string>;   // tag is a key-value pair, both strings
    void addTag(const Tag&);     // add a new tag to the collection of tags
    std::string lookupTag(std::string_view key) const;   // return value associated with key

    // information about this way
    long long getID() const { return wayID; }
    bool isPath() const;
    bool isBuilding() const;
    double length() const;   // calculate length using distance between nodes
private:
    long long wayID;
    vector<shared_ptr<Node>> wayNodes;
    vector<Tag> tagVector;

};

// WayList is a linked list of ways.

class WayList {
public:
    WayList();   // create empty list
    // add destructor if needed
    // add copy constructor

    class Iterator {
        // add private constructor, make WayList a friend
        // implement these public operators:
        // dereference (*), pre-increment (++), equal-to (==), not-equal-to (!=)
    };
    // add begin(), end(), cbegin() and cend()

    size_t size() const;   // how many ways in list?

    void addWay(const Way&);  // append a new way to the end of the list
    void addWay(std::shared_ptr<Way>&);  // append an existing way to the list
};


#endif //ECE309_SPR23_STREETMAP_WAY_H
