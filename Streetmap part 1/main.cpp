// ECE 309 Spring 2023
// Street Map programming project

#include <iostream>
#include <string>
#include "StreetMap.h"
#include "Node.h"
#include "Way.h"
using std::cout, std::endl;

// main function just creates a StreetMap,
// initializes with a file, and prints the
// number of Nodes and Ways

// pass file name (without map/) as a command-line argument
// in CLion: use Edit Configurations to set Program arguments
// in CLion: set Working Directory to project directory

int main(int argc, char **argv) {
/*
    if (argc != 2) {
        cout << "Must specify map file name.\n";
        return 0;
    }
    std::string filename {"maps/"};
    filename += argv[1];

    StreetMap sm;
    if (!sm.readOSM(filename)) {
        cout << "Error reading " << filename << endl;
        return 0;
    }

    cout << "Map named \"" << argv[1] << "\" has " << sm.getNumNodes() << " nodes and "
         << sm.getNumWays() << " ways." << endl;*/

StreetMap test;
test.readOSM("maps/Stanford.osm");
cout << test.getNumWays() << endl;
cout << test.getNumNodes() << endl;


    return 0;
}
