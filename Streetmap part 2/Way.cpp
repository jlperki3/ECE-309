// member functions for Way and WayList

#include "Way.h"
#include <memory>
using std::make_shared, std::shared_ptr;

using NodePtr = shared_ptr<Node>;
using WayPtr = shared_ptr<Way>;

// Node-related methods
void Way::addNode(NodePtr& np) {   // add a new node to the end of the sequence
    nodes.push_back(np);
    if (nodes.size() > 1) {
        size_t last = nodes.size() - 1;
        m_length += nodes.at(last)->distance(*nodes.at(last-1));
        if (np->getID() != nodes.at(0)->getID()) is_path = true;
        else is_path = false;
    }
}

NodePtr Way::lookupNode(long long id) const {
    for (auto& np : nodes) {
        if (np->getID() == id) return np;
    }
    return nullptr;
}


// tag-related functions
void Way::addTag(const Tag& t) {     // add a new tag to the collection of tags
    tags.push_back(t);
    // tags added after nodes, so we know if it's a path or not
    // if "building" is anywhere in the tag, mark it as a building
    if (!is_path && (t.first.find("building") != std::string::npos)) is_building = true;
}

std::string Way::lookupTag(std::string_view key) const {  // return value associated with key
    for (auto &t: tags) {
        if (t.first == key) return t.second;
    }
    return "";
}

double Way::distance(const NodePtr& n1, const NodePtr& n2) const {
    bool found1 = false;
    bool found2 = false;
    size_t index1;
    size_t index2;
    double totalDist;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (n1 == nodes[i] && n1 != nullptr) {
            index1 = i;
            found1 = true;
            break;
        }
    }
    for (size_t i = 0; i < nodes.size(); i++) {
        if (n2 == nodes[i] && n2 != nullptr) {
            index2 = i;
            found2 = true;
            break;
        }
    }

    if (found1 == false || found2 == false) return -1;
    if (n1 == n2) return 0;

    while (index1 < index2) {
        Node nextNode = *nodes[index1+1];
        double smallDist = nodes[index1]->distance(nextNode); //starts at n1 and continues till it gets to n2
        totalDist += smallDist;
        index1++;
    }
    while (index2 < index1) {
        Node nextNode = *nodes[index2+1];
        double smallDist = nodes[index2]->distance(nextNode); //starts at n1 and continues till it gets to n2
        totalDist += smallDist;
        index2++;
    }
    return totalDist;
}

bool Way::intersects(const Way& other) const {
    for (size_t i = 0; i < nodes.size(); i++) {
        for (size_t j = 0; j < other.nodes.size(); j++) {
            if (nodes[i] == other.nodes[j]) return true;
        }
    }
    return false;
}

NodeList Way::intersections() const {
    NodeList listOfIntersections;
    //if (is_building && is_building) return listOfIntersections;     //Check if both ways are buildings
    //if (!(is_path || is_building)) return listOfIntersections;      //Check that the ways are either a path or building
    /*for (int i = 0; i < nodes.size(); i++) {
        auto test = nodes[i]->getWays();
        for (int j = 0; j < test.size(); j++) {
            if (test.size() > 1) {
                if (test[j]->isBuilding() || test[j]->isPath()) {
                    listOfIntersections.push_back(nodes[i]);
                }
            }
        }
    }
    return listOfIntersections;*/
    for (size_t i = 0; i < nodes.size(); i++) {
        auto test = nodes[i]->getWays();
        bool intersection = false;
        bool pathFlag1 = false;
        bool pathFlag2 = false;
        bool buildingFlag = false;
        int count = 0;
        for (size_t j = 0; j < test.size(); j++) {
            if (test.size() > 1 && ID != nodes[i]->getID()) {
                if (test[j]->isPath()) {
                    count++;
                    pathFlag1 = true;
                }
                if (test[j]->isPath() && pathFlag1 == true && count > 1) pathFlag2 = true;
                if (test[j]->isBuilding()) buildingFlag = true;
                if ((pathFlag1 == true && pathFlag2 == true) || (pathFlag1 == true && buildingFlag == true)) {
                    intersection = true;
                    break;
                }
            }
        }
        if (intersection == true) listOfIntersections.push_back(nodes[i]);
    }
    return listOfIntersections;
}

NodePtr Way::closestIntersection(const NodePtr& np) const {
    NodeList intersectionsList = intersections();
    double tempDist = 0;
    NodePtr myNode = lookupNode(np->getID());
    if (myNode == nullptr) return myNode;           // return nullptr if node does not exist

    if (intersectionsList.size() <= 1) return nullptr;
    NodePtr closest = nullptr;

    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i] != np) {
            if (tempDist >= np->distance(*nodes[i]) || tempDist == 0) {
                tempDist = np->distance(*nodes[i]);
                closest = nodes[i];
            } else if (np->distance(*nodes[i]) == np->distance(*closest) && nodes[i]->getID() < closest->getID()) {
                closest = nodes[i];
            }
        }
    }
    return closest;

}

#if 0
// removing WayList, replacing with std::list

// copy constructor for WayList
WayList::WayList(const WayList& other) {
    for (auto p{other.head}; p; p = p->next) {
        auto node = new WayNode(p->way);
        append(node);
    }
}

void WayList::append(WayNode *node) {
    if (head) {
        tail->next = node;
        tail = node;
        count += 1;
    }
    else {
        head = tail = node;
        count = 1;
    }
}

// add a new Way to the tail of list
void WayList::addWay(const Way& w) {
    auto wp = make_shared<Way>(w);
    auto node = new WayNode(wp);
    append(node);
}

// add an existing way to the tail of the list
void WayList::addWay(WayPtr& wp) {
    auto node = new WayNode(wp);
    append(node);
}
#endif
