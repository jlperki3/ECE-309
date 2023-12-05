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
#include <memory>
#include <list>

// these types need to be defined before including Node.h
class Way;
using WayPtr = std::shared_ptr<Way>;
using WayList = std::vector<WayPtr>;

#include "Node.h"


class Way {
public:
    explicit Way(long long id) : ID {id} {}  // constructor requires ID
    // add destructor if needed
    // add copy constructor
    Way(const Way& way) = default;

    // Node-related methods
    void addNode(std::shared_ptr<Node>&);   // add a new node to the end of the sequence
    std::shared_ptr<Node> lookupNode(long long id) const;

    // Tag-related methods
    using Tag = std::pair<std::string, std::string>;   // tag is a key-value pair, both strings
    void addTag(const Tag&);     // add a new tag to the collection of tags
    std::string lookupTag(std::string_view key) const;   // return value associated with key

    // information about this way
    long long getID() const { return ID; }
    bool isPath() const { return is_path; }
    bool isBuilding() const { return is_building; }
    bool isClosed() const { return nodes.front() == nodes.back(); }
    double length() const { return m_length; }   // calculate length using distance between nodes
    double distance(const NodePtr& n1, const NodePtr& n2) const;

    // information about intersections
    bool intersects(const Way& other) const;
    NodeList intersections() const;
    NodePtr closestIntersection(const NodePtr&) const;
    NodeList nearestIntersections(const NodePtr&) const;

    // printing a Way
    friend ostream& operator<<(ostream& out, const Way& w) {
        std::string name = w.lookupTag("name");
        if (!name.empty()) out << name;
        else out << "Way " << w.ID;
        return out;
    }

private:
    long long ID;
    bool is_path {false};
    bool is_building {false};
    double m_length {0.0};
    vector<std::shared_ptr<Node>> nodes;
    vector<Tag> tags;
};


#if 0
// Replacing WayList with std::list
// WayList is a linked list of ways.

class WayList {
private:
    class WayNode {
    public:
        std::shared_ptr<Way> way;
        WayNode* next {nullptr};
        WayNode(std::shared_ptr<Way>& w) : way{w} {}
        ~WayNode() { delete next; }
    };

    WayNode * head {nullptr};
    WayNode * tail {nullptr};
    size_t count {0};
public:
    WayList() = default;   // create empty list
    // add destructor if needed
    ~WayList() { delete head; }  // deletes all nodes
    // add copy constructor
    WayList(const WayList&);

    class Iterator {
    private:
        WayNode * node { nullptr };
        // add private constructor, make WayList a friend
        Iterator() = default;
        Iterator(WayNode *wp) : node {wp} {}
        friend class WayList;
    public:
        // implement these public operators:
        // dereference (*), pre-increment (++), equal-to (==), not-equal-to (!=)
        std::shared_ptr<Way>& operator*() {
            return node->way;  // crashes if iterator is end()
        }
        Iterator& operator++() {
            if (node) {
                node = node->next;
            }
            return *this;
        }
        bool operator==(const Iterator& other) { return node == other.node; }
        bool operator!=(const Iterator& other) { return node != other.node; }
    };

    Iterator begin() {   // create iterator that refers to first node
        return {head};
    }
    Iterator cbegin() const {
        return {head};
    }
    Iterator end() {    // create iterator that refers to one past the end
        return {nullptr};
    }
    Iterator cend() const {
        return {nullptr};
    }

    size_t size() const { return count; }  // how many ways in list?

    void addWay(const Way&);  // append way to the end of the list
    void addWay(std::shared_ptr<Way>&);     // if already have a pointer
private:
    void append(WayNode*);
};
#endif

#endif //ECE309_SPR23_STREETMAP_WAY_H
