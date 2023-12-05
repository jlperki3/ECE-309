// Functions related to StreetMap

#include "StreetMap.h"
#include "Node.h"
#include "Way.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "ctype.h"
#include <vector>


using namespace std;

bool StreetMap::readOSM(std::string_view filename) {
    ifstream inFS;
    string lineRead;

    //open file and get entire line into one string: lineRead
    inFS.open(filename);

    //check if the file has been opened
    if (!inFS.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return false;
    }

    getline(inFS, lineRead);
    getline(inFS, lineRead);
    getline(inFS, lineRead);

    while (!inFS.eof()) {
        // find the starting indexes of each usable piece of information
        getline(inFS, lineRead);
        //Get node information from osm file
        indexID = lineRead.find("<node id=\"");
        if (indexID != string::npos) {
            indexID += 10;
            indexLat = lineRead.find("lat=");
            indexLat += 5;
            indexLon = lineRead.find("lon=");
            indexLon += 5;

            //copy the data from the lineRead string into separate organized string chunks
            while (lineRead[indexID] != '"') {
                idString += lineRead[indexID];
                indexID++;
            }
            while (lineRead[indexLat] != '"') {
                latString += lineRead[indexLat];
                indexLat++;
            }
            while (lineRead[indexLon] != '"') {
                lonString += lineRead[indexLon];
                indexLon++;
            }

            id = stoll(idString, nullptr, 10);
            lat = stod(latString, nullptr);
            lon = stod(lonString, nullptr);

            //cout << "id = " << id << endl;
            //cout << "lat = " << lat << endl;
            //cout << "lon = " << lon << endl;

            auto p = make_shared<Node>(id, lat, lon);
            nodePtr.push_back(p);
            idString = "";
            latString = "";
            lonString = "";
        }

        //get way information from osm file
        indexID = lineRead.find("<way id=\"");
        if (indexID != string::npos) {
            indexID += 9;

            while (lineRead[indexID] != '"') {
                idString += lineRead[indexID];
                indexID++;
            }

            wayID = stoll(idString, nullptr, 10);

            auto ptr = make_shared<Way>(id);
            wayVec.push_back(ptr);
        }
        wayID = 0;
        idString = "";

        //way id has been found at this point
        //find the nodes to be added to the way vector
        indexID = lineRead.find("<nd ref=\"");
    if (indexID != string::npos) {
        indexID += 9;
            while (lineRead[indexID] != '"') {
                idString += lineRead[indexID];
                indexID++;
            }
            int test = any_of(idString.begin(), idString.end(), ::isdigit);
            if (test == 0) {
                Way myWay(wayID);
                wayID = stoll(idString, nullptr, 10);
                cout << idString << endl;
                nodeToWay = lookupNode(wayID);
                myWay.addNode(nodeToWay);
            }
            getline(inFS, lineRead);
            indexID = lineRead.find("<nd ref=\"");
            idString = "";
        }
    }
    return true;
}

std::shared_ptr<Node> StreetMap::lookupNode(long long id) const {
    size_t vectorSize = nodePtr.size();
    for (int j = 0; j < vectorSize; j++) {
        if (nodePtr[j]->getID() == id) {
            return nodePtr[j];
        }
    }
}