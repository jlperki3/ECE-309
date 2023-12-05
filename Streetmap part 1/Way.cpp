// member functions for Way and WayList

#include "Way.h"

void Way::addNode(std::shared_ptr<Node> &anotherNode) {
    wayNodes.push_back(anotherNode);
}