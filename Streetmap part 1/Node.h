#ifndef ECE309_SPR23_STREETMAP_NODE_H
#define ECE309_SPR23_STREETMAP_NODE_H
#define RADIUS (6.3781 * 10 * 10 * 10 * 10 * 10 * 10)
//using namespace std;
// Node is a specified location.
// ID is a 64-bit integer.
// Latitude and Longitude are 64-bit floating-point values.

// Methods may be implemented here or in Node.cpp.

class Node {
public:
    // constructor requires ID, latitude, and longitude
    Node(long long id, double lat, double lon);
    // no need for destructor
    Node(const Node&);    //copy constructor

    // return node information
    long long getID() const { return nodeID; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

private:
    long long nodeID;
    double latitude;
    double longitude;
};

// operator returns distance between two nodes
double operator-(const Node&, const Node&);


#endif //ECE309_SPR23_STREETMAP_NODE_H
