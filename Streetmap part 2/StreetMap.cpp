// Functions related to StreetMap

#include "StreetMap.h"

#include <iostream>
#include <fstream>
using std::ifstream;
using std::string, std::getline;
#include <memory>
using std::shared_ptr, std::make_shared;

string extractTag(const string& xmlString);
string extractAttr(const string& xmlString, const char * name);
Node createNode(const string&);
Way createWay(const string&);

bool StreetMap::readOSM(std::string_view filename) {
    if (!nodes.empty()) nodes.clear();
    if (!ways.empty()) ways.clear();

    ifstream osm { filename.data() };
    if (!osm.is_open()) return false;

    string inbuf;   // used to read lines from the file
    // ignore first three lines of the file
    getline(osm, inbuf);  // xml prolog
    getline(osm, inbuf);  // osm root
    getline(osm, inbuf);  // boundary

    bool inWay { false };
    string tag;
    WayPtr wp { nullptr };
    while (true) {
        getline(osm, inbuf);
        if (osm.eof()) break;

        tag = extractTag(inbuf);
        if (tag == "node") {
            auto np = make_shared<Node>(createNode(inbuf));
            nodes.insert(np->getID(), np);
            //if (inbuf.find("/>") != std::string::npos) inNode = true;
        }
        //else if (tag == "/node") inNode = false;
        else if (tag == "tag" && inWay) {
            string key = extractAttr(inbuf, "k");
            string value = extractAttr(inbuf, "v");
            wp->addTag({key, value});
        }
        else if (tag == "way") {
            wp = make_shared<Way>(createWay(inbuf));
            if (inbuf.find("/>") == std::string::npos) inWay = true;
            else ways.push_back(wp);  // should never happen
        }
        else if (tag == "/way") {
            inWay = false;
            ways.push_back(wp);
            wp = nullptr;
        }
        else if (tag == "nd" && inWay) {
            long long id = std::stoll(extractAttr(inbuf, "ref"));
            auto np = lookupNode(id);
                wp->addNode(np);
                np->addWay(wp);
        }
        else if (tag == "relation") break;  // exit when ways are done
    }
    return true;
}

string extractTag(const string& str) {
    size_t pos = str.find('<') + 1;
    size_t p = pos+1;
    while ((str.at(p) != ' ') && (str.at(p) != '>')) p++;
    string tag = str.substr(pos, (p-pos));
    //std::cout << "tag = " << tag << std::endl;
    return tag;
}

string extractAttr(const string& str, const char * name) {
    string ns{name};
    ns += "=";
    size_t pos = str.find(ns);
    pos = str.find('\"', pos) + 1;
    size_t end = str.find('\"', pos + 1);
    return str.substr(pos, end-pos);
}

Node createNode(const string& inbuf) {
    long long id = std::stoll(extractAttr(inbuf, "id"));
    double lat = std::stod(extractAttr(inbuf, "lat"));
    double lon = std::stod(extractAttr(inbuf, "lon"));
    return {id, lat, lon};
}

Way createWay(const string& inbuf) {
    long long id = std::stoll(extractAttr(inbuf, "id"));
    return Way(id);
}

NodePtr StreetMap::lookupNode(long long id) const {
    NodePtr n = nullptr;
            nodes.find(id, n);
            return n;
}

WayPtr StreetMap::lookupWay(long long id) const {
    for (auto iter {ways.cbegin()}; iter != ways.cend(); ++iter) {
        if ((*iter)->getID() == id) return *iter;
    }
    return nullptr;
}

WayList StreetMap::getBuildings() const {
    WayList b;
    for (auto iter {ways.cbegin()}; iter != ways.cend(); ++iter) {
        if ((*iter)->isBuilding()) b.push_back(*iter);
    }
    return b;
}

WayList StreetMap::getPaths() const {
    WayList p;
    for (auto iter {ways.cbegin()}; iter != ways.cend(); ++iter) {
        if ((*iter)->isPath()) p.push_back(*iter);
    }
    return p;
}
