// member functions for Way

#include "Way.h"
using std::list;

// Node-related methods

// Add a new Node to this Way -- updates length and checks for closed path
void Way::addNode(NodePtr& np) {   // add a new node to the end of the sequence
    nodes.push_back(np);
    if (nodes.size() > 1) {
        size_t last = nodes.size() - 1;
        m_length += nodes.at(last)->distance(*nodes.at(last-1));
    }
}

// Find a Node by ID
NodePtr Way::lookupNode(long long id) const {
    for (auto& np : nodes) {
        if (np->getID() == id) return np;
    }
    return nullptr;
}


// tag-related functions

// Add a new tag to this Way
void Way::addTag(const Tag& t) {     // add a new tag to the collection of tags
    tags.push_back(t);
    // tags added after nodes, so we know if it's a path or not
    // if "building" is anywhere in the tag, mark it as a building
    if (t.first.find("building") != std::string::npos) is_building = true;
    // if there's a "highway" tag, it's a path
    if (t.first == "highway") is_path = true;
}

// Return tag value, if present
std::string Way::lookupTag(std::string_view key) const {  // return value associated with key
    for (auto &t: tags) {
        if (t.first == key) return t.second;
    }
    return "";
}

// Calculate distance between Nodes along this Way
// NOTE: Does not consider closed path, but consistent with spec
double Way::distance(const NodePtr& n1, const NodePtr& n2) const {
    if (n1 == n2) return 0;
    NodePtr startNode;
    NodePtr endNode;
    NodePtr prev { nullptr };
    double d {0};
    // follow the path until one of the nodes is encountered
    for (auto& np : nodes) {
        if (!startNode) {
            if (np == n1) { startNode = n1; endNode = n2; }
            else if (np == n2) { startNode = n2; endNode = n1; }
            prev = np;
        }
        else {
            d += prev->distance(*np);
            prev = np;
            if (np == endNode) { prev = nullptr; break; }
        }
    }
    if (!startNode || prev) return -1; // one or both not on the path
    // account for closed Way
    if (nodes.front() == nodes.back()) {
        d = std::min(d, m_length - d);
    }
    return d;
}

// check whether this Way and another Way intersect each other
// update: intersection is only between two paths, or between a path and a building
bool Way::intersects(const Way& other) const {
    // if this Way is not a path or building, no intersections
    if (!is_path && !is_building) return false;
    // if this Way is a path, other must be path or building
    if (is_path && (!other.is_path && !other.is_building)) return false;
    // if this Way is a building, other must be a path
    if (is_building && !other.is_path) return false;
    // now, if you find that other Way associated with any of your nodes, it's an intersection
    for (auto& np : nodes) {
        auto ways { np->getWays() };
        if (ways.size() > 1) {
            for (auto i { ways.begin() }; i != ways.end(); ++i) {
                if ((*i)->ID == other.ID) return true;
            }
        }
    }
    return false;
}

// Return all Nodes on this Way that are intersections with other Ways
NodeList Way::intersections() const {
    NodeList points;
    // if this way is not a path and not a building, no intersections
    if (!is_path && !is_building) return points;
    for (auto& np : nodes) {
        auto ways { np->getWays() };
        bool found {false};
        if (ways.size() > 1) {
            for (auto &wp: ways) {
                if ((wp->ID != ID) && (wp->is_path || wp->is_building)) {
                    found = true;
                    break;
                }
            }
        }
        if (found) points.push_back(np);
    }
    // for a closed path, need to make sure that first/last node is not pushed twice
    if (!points.empty() && isClosed() && (points.back() == nodes.front())) points.pop_back();
    return points;
}

// Return closest intersection Node on this Way for given Node
// Assumes non-closed path, because closed path has no intersection
// (Does not work correctly for buildings, but consistent with spec)
NodePtr Way::closestIntersection(const NodePtr& np) const {
    NodePtr nearest { nullptr };
    auto ix = intersections();
    double min {-1};
    for (auto& other: ix) {
        if (other != np) {
            double d = distance(np, other);  // distance along the path
            if ((min == -1) || (d < min)) {
                min = d;
                nearest = other;
            }
        }
    }
    return nearest;
}

NodeList Way::nearestIntersections(const NodePtr& thisNode) const {
    NodeList nearest;
//    if (thisNode->getWays().size() > 1) {
//        nearest.push_back(thisNode);
//        return nearest;
//    }
//    auto ix = intersections();
//    double min {-1};
//    for (auto& other: ix) {
//        if (other != thisNode) {
//            double d = distance(thisNode, other);  // distance along the path
//            if ((min == -1) || (d < min)) {
//                min = d;
//                nearest = other;
//            }
//        }
//    }
    return nearest;


    // check start node is an intersectino
    // if not good
    // if it is get closest intersection on either side
    //add start node to your graph and add edges from the start node to each of the closest intersection
   // same for end node
   // call shorest path
   // find which way its on put it as a route
}
