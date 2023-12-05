// Member functions and non-member functions related to Node

#include "Node.h"

#include <cmath>

// subtract operator calculates Manhattan difference between nodes
double Node::distance(const Node& n2) const {
    const double R {6.3781e6}; // radius of the earth in meters
    const double pi {3.14159265358979323846};
    const double toRad { pi / 180.0 };
    double lat1 = latitude * toRad;
    double lat2 = n2.latitude * toRad;
    double lon1 = longitude * toRad;
    double lon2 = n2.longitude * toRad;
    double x = (lon2 - lon1) * std::cos((lat1 + lat2) / 2.0);
    double y = (lat2 - lat1);
    double d = R * std::sqrt(x*x + y*y);
    return d;
}




