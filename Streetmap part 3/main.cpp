// ECE 309 Spring 2023
// Street Map programming project

#include <iostream>
#include <string>
#include "StreetMap.h"
using std::cout, std::endl;
#include "HashTable.h"
#include "Graph.h"
// main function just creates a StreetMap,
// initializes with a file, and prints the
// number of Nodes and Ways

// pass file name (without map/) as a command-line argument
// in CLion: use Edit Configurations to set Program arguments
// in CLion: set Working Directory to project directory

int main(int argc, char **argv) {
//    if (argc != 2) {
//        cout << "Must specify map file name.\n";
//        return 0;
//    }
//    std::string filename {"maps/"};
//    filename += argv[1];
//
//    StreetMap sm;
//    if (!sm.readOSM(filename)) {
//        cout << "Error reading " << filename << endl;
//        return 0;
//    }
//
//    cout << "Map named \"" << argv[1] << "\" has " << sm.getNumNodes() << " nodes and "
//         << sm.getNumWays() << " ways." << endl;

Graph<int, int> g;
    for (int i {0}; i < 14; ++i) g.addVertex(i);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 8);
    g.addEdge(1, 9);
    g.addEdge(2, 6);
    g.addEdge(2, 7);
    g.addEdge(3, 5);
    g.addEdge(3, 6);
    g.addEdge(4, 10);
    g.addEdge(6, 11);
    g.addEdge(7, 8);
    g.addEdge(7, 12);
    g.addEdge(8, 13);
    srand(1313);

    return 0;
}
