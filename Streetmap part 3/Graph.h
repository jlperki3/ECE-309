#ifndef ECE309_SPR23_STREETMAP_GRAPH_H
#define ECE309_SPR23_STREETMAP_GRAPH_H

#include <cstddef> // for size_t
#include <list>
#include <queue>
#include <set>
#include "HashTable.h"
#include <map>
#include "stdio.h"
#include <unordered_map>
#include <climits>

using std::list;

// TEMPLATE CLASS for Graph, and TEMPLATE FUNCTIONS for BFS and DFS
// All definitions must go here. Do not create Graph.cpp.
// Additional private functions (for the class) or template functions (to help with BFS/DFS) may be added.
// DO NOT change the public member functions.

// TEMPLATE CLASS: Graph<K,W> -- the W type defaults to unsigned int
// This is a weighted graph, but weight on each edge defaults to 1.
// (So if you want unweighted, just leave off the weight parameters.)

// K is a key used to find a vertex in the graph -- K should be lightweight, passed by value.
// W is the type used for an edge weight (default is unsigned int).
// W must be a numeric type (int, double, etc.).
// Each vertex has a list of edges, which connect to adjacent vertices.

template <typename K, typename W = unsigned>
class Graph {
private:
    class Edge {
    public:
        K src;
        K dst;
        W weight;
        Edge(const K &from, const K &to, W wt = 1) : src{from}, dst{to}, weight{wt} {}
        bool operator==(const Edge& otherEdge) const {
            return (src == otherEdge.src && dst == otherEdge.dst);
        }
    };

    class Vertex {
    public:
        K key;
        Vertex(K id) : key{id} {}
        list<Edge> edges;
        std::vector<K> incoming;
        // add member variable(s) to store edges
        // (hint: graph may be directed or undirected -- directed will require separate incoming and outgoing edges)
    };
    // add a data structure (hint: hash table!) to store vertices
    size_t n_edges {0};
    size_t n_vertices {0};
    const bool is_directed;
    HashTable<K, Vertex> myGraph;
public:
    Graph(bool directed = false) : is_directed{directed} {} // DONE
    bool isDirected() const { return is_directed; }         // DONE
    bool addVertex(K key);                                  // DONE
    bool addEdge(K a, K b, W weight = 1);                   // DONE
    bool removeVertex(K key);                               // DONE
    bool removeEdge(K a, K b);                              // DONE
    bool updateEdge(K a, K b, W newWeight);                 // DONE
    size_t numVertices() const {                            // DONE
        return n_vertices;
    }
    size_t numEdges() const {                               // DONE
        return n_edges;
    }
    void clear();                                           // DONE

    bool findVertex(K a) const;                             // DONE
    bool isAdjacent(K a, K b) const;                        // DONE
    bool isAdjacent(K a, K b, W& wt) const;                 // DONE     // returns weight if edge is found
    list<K> getAdjacencyList(K a);                          // DONE     // list of vertices to which there is an edge from a
    bool confirmPath(const list<K>& vertexList) const;      // DONE
    W pathWeight(const list<K>& vertexList) const;          // DONE     // returns 0 if path is not legit
    list<K> shortestPath(K from, K to, W& length);
};


//----- IMPLEMENTATION -----
// put Graph<K,W> member functions here
// (if the function is trivial, you can add it to the declaration above)
// because this is a template, definitions must go here, in the .h file  -- DO NOT create a Graph.cpp file

////////////////////////////////////////////////////////////////
template <class K, class W>
bool Graph<K, W>::addVertex(K key) {
    Vertex * tempVertex = new Vertex(key);
    Vertex insertThis = Vertex(key);
    if (!(myGraph.find(key, *tempVertex))) {
        n_vertices++;
        return myGraph.insert(key, insertThis);
    } else {return false;}
}

////////////////////////////////////////////////////////////////
template <class K, class W>
bool Graph<K, W>::addEdge(K a, K b, W weight) {
    Edge a_To_b = Edge(a, b, weight);
    Edge b_To_a = Edge(b, a, weight);
    Vertex * vertex_a = new Vertex(a);
    Vertex * vertex_b = new Vertex(b);
    if (!(myGraph.find(a, *vertex_a) && myGraph.find(b, *vertex_b))) return false;
    for (auto& value : vertex_a->edges) { // check if the edge already exists
        if (value == a_To_b) {
            return false;
        }
    }

    myGraph.erase(a,*vertex_a);
    // insert edge from a to b
    vertex_a->edges.push_back(a_To_b);
    myGraph.insert(a, *vertex_a);
    n_edges++;
    //-----------------------------------------------------------------------------
    if (!is_directed) {
        // if not directed insert edge from b to a
        for (auto& value : vertex_b->edges) { // check if the edge already exists
            if (value == b_To_a) {
                return true;
            }
        }
        myGraph.erase(b, *vertex_b);
        // insert edge from b to a
        vertex_b->edges.push_back(b_To_a);
        myGraph.insert(b, *vertex_b);
        return true;
    } else {
        myGraph.erase(b, *vertex_b);
        vertex_b->incoming.push_back(a);
        myGraph.insert(b, *vertex_b);
        return true;
    }

}

/////////////////////////////////////////////////////////////
template <class K, class W>
bool Graph<K, W>::removeVertex(K key) {
    Vertex * dummy = new Vertex(key);
    bool removed = myGraph.erase(key, *dummy);
    if (removed)  n_vertices--;
    else {return false;}
    for (auto it = dummy->edges.begin(); it != dummy->edges.end();) {
        it = dummy->edges.erase(it);
        n_edges--;
    }
    if (is_directed) {
        if (!dummy->incoming.empty()) {
            for (size_t i = 0; i < dummy->incoming.size(); i++) {
                K tempKey = dummy->incoming[i];
                Vertex * temp = new Vertex(tempKey);
                myGraph.erase(tempKey, *temp);
                for (auto it = temp->edges.begin(); it != temp->edges.end();) {
                    if (it->dst == key) {
                        it = temp->edges.erase(it);
                        n_edges--;
                    } else {
                        ++it;
                    }
                }
                myGraph.insert(tempKey, *temp);
            }
        }
    }
    return removed;

}

/////////////////////////////////////////////////////////////
template <class K, class W>
bool Graph<K, W>::removeEdge(K a, K b) {
    Vertex * vertex_a = new Vertex(a);
    Vertex * vertex_b = new Vertex(b);
    if (myGraph.find(a, *vertex_a) && myGraph.find(b,*vertex_b)) {    // Make sure both vertices exist if not -> return false
        Edge a_To_b = Edge(a, b);
        Edge b_To_a = Edge(b, a);
        for (auto& value : vertex_a->edges) { // iterate through vertex adjList to see if there is a matching edge
            if  (value == a_To_b) {
                myGraph.erase(a, *vertex_a);
                vertex_a->edges.remove(a_To_b);
                myGraph.insert(a, *vertex_a);
                n_edges--;
                if (is_directed) return true;
                break;
            }
        }
        if (!is_directed) {
            for (auto& value : vertex_b->edges) { // iterate through vertex adjList to see if there is a matching edge
                if  (value == b_To_a) {
                    myGraph.erase(b, *vertex_b);
                    vertex_b->edges.remove(b_To_a);
                    myGraph.insert(b,*vertex_b);
                    return true;
                }
            }
        }
        return false; // if code gets here there is not a matching edge so return false
    } else { // returns false if the vertices don't exist in the graph or the edge isn't in the adjList
        return false; // if code reaches here than the either a or b does not exist in the table
    }

}

///////////////////////////////////////////////////////////// NOT TESTED
template <class K, class W>
bool Graph<K, W>::updateEdge(K a, K b, W newWeight) {
    Edge temp_a = Edge(a, b);
    Vertex * vertex_a = new Vertex(a);
    Vertex * vertex_b = new Vertex(b);
    if (!(myGraph.find(a, *vertex_a) && myGraph.find(b,*vertex_b))) {
        return false;
    }
    myGraph.find(a, *vertex_a);
    bool foundEdge = false;

    for (auto& value : vertex_a->edges) { // check if the edge already exists
        if  (value == temp_a) {
            foundEdge = true;
        }
    }
    if (!foundEdge) return false; //if edge doesnt exist return false

    myGraph.erase(a,*vertex_a);         // remove vertex so it can be modified

    // insert edge from a to b
    vertex_a->edges.remove(temp_a);          // remove current a to b edge
    Edge new_a_To_b = Edge(a, b, newWeight);    // make new edge object to replace old edge
    vertex_a->edges.push_back(new_a_To_b);      // add new edge to adj list
    myGraph.insert(a, *vertex_a);    // add vertex back into graph
    //-----------------------------------------------------------------------------
    if (!is_directed) {

        // if not directed insert edge from b to a
        Edge temp_b = Edge(b, a, newWeight);
        myGraph.erase(b, *vertex_b);         // remove vertex so it can be modified

        vertex_b->edges.remove(temp_b);           // remove current b to a edge
        Edge new_b_To_a = Edge(b, a, newWeight);     // make new edge object to replace old edge
        // insert edge from b to a
        vertex_b->edges.push_back(new_b_To_a);       // add new edge to adj list
        myGraph.insert(b, *vertex_b);     // add vertex back into graph
        return true;
    } else {
        return true;
    }
}

/////////////////////////////////////////////////////////////
template <class K, class W>
void Graph<K, W>::clear() {
    myGraph.clear();
    n_vertices = 0;
    n_edges = 0;
}

////////////////////////////////////////////////////////////////
template <class K, class W>
bool Graph<K, W>::findVertex(K a) const {
    Vertex tempVertex = Vertex(a);
    return myGraph.find(a, tempVertex);
}

////////////////////////////////////////////////////////////////
template <class K, class W>
bool Graph<K, W>::isAdjacent(K a, K b) const {
    Vertex * vertex_a = new Vertex(a);
    Vertex * vertex_b = new Vertex(b);
    if (myGraph.find(a, *vertex_a) && myGraph.find(b,*vertex_b)) {    // Make sure both vertices exist if not -> return false
        Edge a_To_b = Edge(a, b);
        Edge b_To_a = Edge(b, a);
        for (auto& value : vertex_a->edges) { // iterate through vertex adjList to see if there is a matching edge
            if  (value == a_To_b) {
                return true;
            }
        }
        if (!is_directed) {
            for (auto& value : vertex_b->edges) { // iterate through vertex adjList to see if there is a matching edge
                if  (value == b_To_a) {
                    return true;
                }
            }
        }
        return false; // if code gets here there is not a matching edge so return false
    } else { // returns false if the vertices don't exist in the graph or the edge isn't in the adjList
        return false; // if code reaches here than the either a or b does not exist in the table
    }

}

////////////////////////////////////////////////////////////////
template <class K, class W>
bool Graph<K, W>::isAdjacent(K a, K b, W& wt) const { // returns weight if edge is found
    Vertex * vertex_a = new Vertex(a);
    Vertex * vertex_b = new Vertex(b);
    if (myGraph.find(a, *vertex_a) && myGraph.find(b,*vertex_b)) {    // Make sure both vertices exist if not -> return false
        Edge a_To_b = Edge(a, b);
        Edge b_To_a = Edge(b, a);
        for (auto& value : vertex_a->edges) { // iterate through vertex adjList to see if there is a matching edge
            if  (value == a_To_b) {
                wt = value.weight;
                return true;
            }
        }
        if (!is_directed) {
            for (auto& value : vertex_b->edges) { // iterate through vertex adjList to see if there is a matching edge
                if  (value == b_To_a) {
                    wt = value.weight;
                    return true;
                }
            }
        }
        return false; // if code gets here there is not a matching edge so return false
    } else { // returns false if the vertices don't exist in the graph or the edge isn't in the adjList
        return false; // if code reaches here than the either a or b does not exist in the table
    }

}

//////////////////////////////////////////////////////////////// NOT TESTED
template <class K, class W>
list<K> Graph<K, W>::getAdjacencyList(K a) { // list of vertices to which there is an edge from a
    Vertex * vertex_a = new Vertex(a);
    list<K> adjList;
    if (myGraph.find(a, *vertex_a)) {
        for (auto curEdge : vertex_a->edges) {
            adjList.push_back(curEdge.dst);
        }
    }
    return adjList;
}

template <class K, class W>
bool Graph<K, W>::confirmPath(const list<K>& vertexList) const {
    if (vertexList.empty()) return false;
    bool is_path = true;
    auto i = vertexList.begin();
    K prev = *i;
    ++i;
    while (i != vertexList.end()) {
        K next = *i;
        if (!isAdjacent(prev, next)) {
            is_path = false;
            break;
        }
        prev = next;
        ++i;
    }
    return is_path;
}

template <class K, class W>
W Graph<K, W>::pathWeight(const list<K>& vertexList) const {  // returns 0 if path is not legit
    if (!confirmPath(vertexList)) return 0;
    W tempWeight = 0;
    W totalWeight = 0;
    auto i = vertexList.begin();
    K cur = *i;
    ++i;
    while (i != vertexList.end()) {
        K next = *i;
        isAdjacent(cur, next, tempWeight);
        totalWeight += tempWeight;
        cur = next;
        ++i;
    }
    return totalWeight;
}

template <class K, class W>
list<K> Graph<K, W>::shortestPath(K from, K to, W& length) {
// holds the current best distance from source to K
    std::map<K, W> distance;
// previous node in the shortest path tree
    std::map<K, K> previous;
// these are the nodes that we are sure we know the best route to
    std::set<K> discovered;
    distance[from] = 0;

    while (!discovered.count(to)) {
        // find the vertex with the smallest distance to the source
        K currentVertex;
        W smallest_distance = INT_MAX;
        for (auto test : distance) {
            if (!discovered.count(test.first) && test.second < smallest_distance) {
                currentVertex = test.first;
                smallest_distance = test.second;
            }
        }

        // mark the current vertex as discovered
        discovered.insert(currentVertex);

        // update the distances to the adjacent vertices
        Vertex * currentNode = new Vertex(currentVertex);
        myGraph.find(currentVertex, *currentNode);
        for (auto edge : currentNode->edges) {
            K adjacent_vertex = edge.dst;
            if (!discovered.count(adjacent_vertex)) {
                W total_distance = distance[currentVertex] + edge.weight;
                if (!distance.count(adjacent_vertex) || total_distance < distance[adjacent_vertex]) {
                    distance[adjacent_vertex] = total_distance;
                    previous[adjacent_vertex] = currentVertex;
                }
            }
        }
    }

// build the path from the destination vertex to the source vertex
    list<K> connections;
    for (K vertex = to; vertex != from; vertex = previous[vertex]) {
        connections.push_front(vertex);
    }
    connections.push_front(from);

// set the output parameters
    length = distance[to];
    return connections;
}




//---------------------------

// function templates for BFS and DFS

// G is graph class  -- for this assignment, you can assume it will be
// some instance of Graph<K,W>

// K is key type, used to locate the starting vertex (must be the same as Graph's K)

// V is function class that performs "visit" operation -- return true to stop traversal/search
// V must provide function call operator that takes a K parameter and returns a bool

template <class G, class K, class V>
void BFS(G& graph, K start, V& visit) {
    std::queue<K> frontier;
    std::set<K> discovered;
    frontier.push(start);
    discovered.insert(start);
    while(!frontier.empty()) {
        K node = frontier.front();
        frontier.pop();
        if (visit(node)) break; // process and check for early exit
        auto neighbors = graph.getAdjacencyList(node);
        for (auto j : neighbors) {
            if(discovered.find(j) == discovered.end()){
                frontier.push(j);
                discovered.insert(j);
            }
        }
    }
}

template <class G, class K, class V>
void DFS(G& g, K start, V& visit) {
    std::set<K> visited;
    RecursiveDFS(g, start, visited, visit);
}

template <class G, class K, class V>
void RecursiveDFS(G &g, K node, std::set<K>& visited, V& visit) {
    if (visited.find(node) == visited.end()) {
        visit(node);
        visited.insert(node);
        auto neighbors = g.getAdjacencyList(node);
        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
            RecursiveDFS(g, *it, visited, visit);
        }
    }
}
// Other template functions can be added as needed.
// Do not create a Graph.cpp file.


#endif //ECE309_SPR23_STREETMAP_GRAPH_H
