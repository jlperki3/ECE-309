#include "gtest/gtest.h"
#include "../Graph.h"
#include <stack>
using std::stack;
#include <list>
using std::list;
#include <map>
using std::map;

class UnweightedGraphFixture : public ::testing::Test {
protected:
    Graph<int> g;
public:
    UnweightedGraphFixture() {
        // initialize to graph from BFS lecture slides
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
    }
};

// function object to collect vertices during search
template <class K>
struct Collect {
    list<K> searchOrder;
    bool operator()(K n) { searchOrder.push_back(n); return false; }
};

TEST_F(UnweightedGraphFixture, basic) {
    EXPECT_EQ(g.numVertices(), 14);
    EXPECT_EQ(g.numEdges(), 15);
    EXPECT_FALSE(g.isDirected());
    // spot check some vertices
    EXPECT_TRUE(g.findVertex(4));
    EXPECT_TRUE(g.findVertex(13));
    EXPECT_FALSE(g.findVertex(15));
    // spot check some edges
    EXPECT_TRUE(g.isAdjacent(6, 11));
    EXPECT_TRUE(g.isAdjacent(3, 0));
    EXPECT_TRUE(g.isAdjacent(7, 12));
    EXPECT_FALSE(g.isAdjacent(0, 5));
    EXPECT_FALSE(g.isAdjacent(7, 5));
    // clear and check number of vertices and edges
    g.clear();
    EXPECT_EQ(g.numVertices(), 0);
    EXPECT_EQ(g.numEdges(), 0);
}

TEST_F(UnweightedGraphFixture, removeVertex) {
    ASSERT_EQ(g.numVertices(), 14);
    EXPECT_TRUE(g.removeVertex(3));
    EXPECT_FALSE(g.findVertex(3));
    EXPECT_FALSE(g.isAdjacent(3,0));
    EXPECT_FALSE(g.isAdjacent(3,5));
    EXPECT_EQ(g.numVertices(),13);
    EXPECT_EQ(g.numEdges(),12);
}

TEST_F(UnweightedGraphFixture, removeEdge) {
    ASSERT_EQ(g.numVertices(), 14);
    ASSERT_TRUE(g.removeEdge(3,5));
    EXPECT_FALSE(g.isAdjacent(3,5));
    EXPECT_FALSE(g.isAdjacent(5,3));
    EXPECT_EQ(g.numEdges(), 14);
}

TEST_F(UnweightedGraphFixture, path) {
    ASSERT_EQ(g.numVertices(), 14);
    list<int> goodPath {0, 2, 6, 3, 5};
    EXPECT_TRUE(g.confirmPath(goodPath));
    EXPECT_EQ(g.pathWeight(goodPath), 4);
    list<int> badPath {4, 9, 1, 8};
    EXPECT_FALSE(g.confirmPath(badPath));
    EXPECT_EQ(g.pathWeight(badPath), 0);
}

template <class K>
static void printList(list<K>& x) {
    std::cout << "( ";
    for (auto n : x) {
        std::cout << n << " ";
    }
    std::cout << ")" << std::endl;
}

template <class K>
static bool list_search(const list<K>& vals, K x) {
    for (auto n : vals) {
        if (n == x) return true;
    }
    return false;
}


template <class K>
static void list_merge(list<K>& next, const list<K>& adj) {
    for (auto val : adj) {
        if (!list_search(next, val)) next.push_back(val);
    }
}

// assuming elements of list are legal indices for bool array
static list<int> list_prune(const list<int>& next, const bool discovered[]) {
    list<int> pruned;
    for (auto n : next) {
        if (!discovered[n]) pruned.push_back(n);
    }
    return pruned;
}

template <class K>
static list<K> list_prune(const list<K>& next, map<K,bool>& discovered) {
    list<K> pruned;
    for (auto n : next) {
        if (!discovered[n]) pruned.push_back(n);
    }
    return pruned;
}

TEST_F(UnweightedGraphFixture, bfs) {
    for (int t=0; t<3; t++) {
        int start = rand() % g.numVertices();
        bool discovered[g.numVertices()];  // set of visited vertices
        for (size_t d=0; d<g.numVertices(); d++) discovered[d] = false;
        list<int> current;  // set of vertices at current distance
        list<int> next;  // all adjacent vertices to current -- pruned to remove visited
        current.push_back(start);
        int n;
        size_t i, c;
        Collect<int> collector;
        BFS(g, start, collector);
        list<int>& bfs = collector.searchOrder;
        std::cout << "BFS from " << start << ": ";
        printList(bfs);
        EXPECT_EQ(bfs.size(), g.numVertices());

        while (!bfs.empty()) {
            c = current.size();
            if (c > 0) {
                // next c vertices should be in current list
                for (i = 0; i < c; i++) {
                    n = bfs.front();
                    bfs.pop_front();
                    EXPECT_TRUE(list_search(current, n)) << "n = " << n << std::endl;
                    discovered[n] = true;
                    list<int> adj = g.getAdjacencyList(n);
                    list_merge(next, adj); // add to next group of vertices
                }
                current = list_prune(next, discovered);  // remove all visited vertices
                next.clear();
            }
            else bfs.pop_front();
        }
    }
}

TEST_F(UnweightedGraphFixture, dfs) {
    for (int i=0; i<3; i++) {
        int start = rand() % g.numVertices();
        bool visited[g.numVertices()];
        for (size_t v=0; v < g.numVertices(); v++) visited[v] = false;
        stack<int> trace;
        Collect<int> collector;
        DFS(g, start, collector);
        list<int>& dfs = collector.searchOrder;
        std::cout << "DFS from " << start << ": ";
        printList(dfs);
        EXPECT_EQ(dfs.size(), g.numVertices());
        // check start vertex
        int n, last;
        n = dfs.front(); dfs.pop_front();
        EXPECT_EQ(n, start);
        trace.push(n);
        visited[n] = true;
        last = n;
        while (!dfs.empty()) {
            n = dfs.front(); dfs.pop_front();
            ASSERT_FALSE(visited[n]);  // should not be duplicate
            // should be adjacent to some vertex on the stack
            while (1) {
                auto adj = g.getAdjacencyList(last);
                if (list_search(adj, n)) break;
                trace.pop();
                ASSERT_FALSE(trace.empty());
                last = trace.top();
            }
            trace.push(n);
            visited[n] = true;
            last = n;
        }
    }
}

#include <string>
using std::string_view;

class WeightedGraphFixture : public ::testing::Test {
protected:
    Graph<string_view,unsigned> g;
    string_view a[9] {"ATL", "BHM", "BNA", "CLT", "DCA", "JFK", "MIA", "ORD", "RDU"};
public:
    WeightedGraphFixture() {
        // initialize airports graph from lecture notes
        for (size_t i {0}; i < 9; ++i) g.addVertex(a[i]);
        g.addEdge("JFK", "DCA", 210);
        g.addEdge("DCA", "RDU", 240);
        g.addEdge("ORD", "RDU", 720);
        g.addEdge("RDU", "CLT", 150);
        g.addEdge("RDU", "MIA", 740);
        g.addEdge("ATL", "RDU", 370);
        g.addEdge("JFK", "RDU", 450);
        g.addEdge("ATL", "BHM", 130);
        g.addEdge("MIA", "ATL", 560);
        g.addEdge("ATL", "BNA", 210);
        g.addEdge("BHM", "CLT", 340);
        g.addEdge("CLT", "JFK", 550);
        g.addEdge("BNA", "BHM", 160);
        g.addEdge("BNA", "CLT", 370);
        srand(11254);
    }
};

TEST_F(WeightedGraphFixture, basic) {
    EXPECT_EQ(g.numVertices(), 9);
    EXPECT_EQ(g.numEdges(), 14);
    EXPECT_FALSE(g.isDirected());
    // spot check some vertices
    EXPECT_TRUE(g.findVertex("RDU"));
    EXPECT_TRUE(g.findVertex("MIA"));
    EXPECT_FALSE(g.findVertex("LGA"));
    // spot check some edges
    EXPECT_TRUE(g.isAdjacent("RDU", "CLT"));
    EXPECT_TRUE(g.isAdjacent("CLT", "RDU"));
    EXPECT_TRUE(g.isAdjacent("DCA", "JFK"));
    EXPECT_FALSE(g.isAdjacent("CLT", "ATL"));
    EXPECT_FALSE(g.isAdjacent("BNA", "JFK"));
}

TEST_F(WeightedGraphFixture, removeVertex) {
    ASSERT_EQ(g.numVertices(), 9);
    EXPECT_TRUE(g.removeVertex("ATL"));
    EXPECT_FALSE(g.findVertex("ATL"));
    EXPECT_FALSE(g.isAdjacent("ATL","RDU"));
    EXPECT_FALSE(g.isAdjacent("BHM","ATL"));
    EXPECT_EQ(g.numVertices(),8);
    EXPECT_EQ(g.numEdges(),10);
}

TEST_F(WeightedGraphFixture, updateEdge) {
    ASSERT_EQ(g.numVertices(), 9);
    unsigned length = 0;
    EXPECT_TRUE(g.isAdjacent("RDU","ATL",length));
    EXPECT_EQ(length, 370);
    EXPECT_TRUE(g.updateEdge("ATL","RDU",365));
    length = 0;
    EXPECT_TRUE(g.isAdjacent("RDU","ATL",length));
    EXPECT_EQ(length, 365);
    length = 0;
    EXPECT_TRUE(g.isAdjacent("ATL","RDU",length));
    EXPECT_EQ(length, 365);
}

TEST_F(WeightedGraphFixture, path) {
    ASSERT_EQ(g.numVertices(), 9);
    list<string_view> goodPath {"JFK", "RDU", "CLT", "BHM", "ATL", "MIA"};
    EXPECT_TRUE(g.confirmPath(goodPath));
    EXPECT_EQ(g.pathWeight(goodPath), 1630);
    list<string_view> badPath {"RDU", "CLT", "MIA", "ATL"};
    EXPECT_FALSE(g.confirmPath(badPath));
    EXPECT_EQ(g.pathWeight(badPath), 0);
}

TEST_F(WeightedGraphFixture, bfs) {
    for (int t=0; t<3; t++) {
        auto start = a[rand() % g.numVertices()];
        map<string_view,bool> discovered;  // set of visited vertices
        for (auto s : a) { discovered[s] = false; }
        list<string_view> current;  // set of vertices at current distance
        list<string_view> next;  // all adjacent vertices to current -- pruned to remove visited
        current.push_back(start);
        string_view n;
        size_t i, c;
        Collect<string_view> collector;
        BFS(g, start, collector);
        list<string_view>& bfs = collector.searchOrder;
        std::cout << "BFS from " << start << ": ";
        printList(bfs);
        EXPECT_EQ(bfs.size(), g.numVertices());

        while (!bfs.empty()) {
            c = current.size();
            if (c > 0) {
                // next c vertices should be in current list
                for (i = 0; i < c; i++) {
                    n = bfs.front();
                    bfs.pop_front();
                    EXPECT_TRUE(list_search(current, n)) << "n = " << n << std::endl;
                    discovered[n] = true;
                    list<string_view> adj = g.getAdjacencyList(n);
                    list_merge(next, adj); // add to next group of vertices
                }
                current = list_prune(next, discovered);  // remove all visited vertices
                next.clear();
            }
            else bfs.pop_front();
        }
    }
}

TEST_F(WeightedGraphFixture, dfs) {
    for (int i=0; i<3; i++) {
        string_view start = a[rand() % g.numVertices()];
        map<string_view,bool> visited;
        for (auto v : a) visited[v] = false;
        stack<string_view> trace;
        Collect<string_view> collector;
        DFS(g, start, collector);
        list<string_view>& dfs = collector.searchOrder;
        std::cout << "DFS from " << start << ": ";
        printList(dfs);
        EXPECT_EQ(dfs.size(), g.numVertices());
        // check start vertex
        string_view n, last;
        n = dfs.front(); dfs.pop_front();
        EXPECT_EQ(n, start);
        trace.push(n);
        visited[n] = true;
        last = n;
        while (!dfs.empty()) {
            n = dfs.front(); dfs.pop_front();
            ASSERT_FALSE(visited[n]);  // should not be duplicate
            // should be adjacent to some vertex on the stack
            while (1) {
                auto adj = g.getAdjacencyList(last);
                if (list_search(adj, n)) break;
                trace.pop();
                ASSERT_FALSE(trace.empty());
                last = trace.top();
            }
            trace.push(n);
            visited[n] = true;
            last = n;
        }
    }
}

TEST_F(WeightedGraphFixture, shortest) {
    list<string_view> p;
    unsigned length;
    p = g.shortestPath("RDU","ATL", length);
    EXPECT_EQ(length,370);
    printList(p);
    p = g.shortestPath("JFK", "BHM", length);
    EXPECT_EQ(length,890);
    printList(p);
    p = g.shortestPath("BNA", "DCA", length);
    EXPECT_EQ(length,760);
    printList(p);
}

class DirectedGraphFixture : public ::testing::Test {
protected:
    Graph<int> g {true};   // directed graph
public:
    DirectedGraphFixture() {
        // directed graph from
        // https://www.oreilly.com/library/view/advanced-mathematics/9781119563518/c5.2.xhtml
        for (size_t i {1}; i <= 6; ++i) g.addVertex(i);
        g.addEdge(1,2);
        g.addEdge(2,4);
        g.addEdge(4,3);
        g.addEdge(3,2);
        g.addEdge(4,1);
        g.addEdge(4,5);
        g.addEdge(5,4);
        g.addEdge(5,2);
        g.addEdge(5,6);
        g.addEdge(6,1);
    }
};

TEST_F(DirectedGraphFixture, basic) {
    EXPECT_EQ(g.numVertices(), 6);
    EXPECT_EQ(g.numEdges(), 10);
    EXPECT_TRUE(g.isDirected());
    // spot check some vertices
    EXPECT_TRUE(g.findVertex(4));
    EXPECT_TRUE(g.findVertex(1));
    EXPECT_FALSE(g.findVertex(0));
    // spot check some edges
    EXPECT_TRUE(g.isAdjacent(6, 1));
    EXPECT_TRUE(g.isAdjacent(4, 5));
    EXPECT_TRUE(g.isAdjacent(1, 2));
    EXPECT_FALSE(g.isAdjacent(2, 1));
    EXPECT_FALSE(g.isAdjacent(5,3));
}

TEST_F(DirectedGraphFixture, removeVertex) {
    ASSERT_EQ(g.numVertices(), 6);
    EXPECT_TRUE(g.removeVertex(3));
    EXPECT_FALSE(g.findVertex(3));
    EXPECT_FALSE(g.isAdjacent(3,2));
    EXPECT_FALSE(g.isAdjacent(4,3));
    EXPECT_EQ(g.numVertices(),5);
    EXPECT_EQ(g.numEdges(),8);
}

TEST_F(DirectedGraphFixture, removeEdge) {
    ASSERT_EQ(g.numVertices(), 6);
    EXPECT_TRUE(g.removeEdge(4,5));
    EXPECT_FALSE(g.isAdjacent(4,5));
    EXPECT_TRUE(g.isAdjacent(5,4));
    EXPECT_EQ(g.numEdges(), 9);
}

TEST_F(DirectedGraphFixture, path) {
    ASSERT_EQ(g.numVertices(), 6);
    list<int> goodPath {1, 2, 4, 5, 6};
    EXPECT_TRUE(g.confirmPath(goodPath));
    list<int> goodPath2 {3, 2, 4, 5, 4, 1};
    EXPECT_TRUE(g.confirmPath(goodPath2));
    list<int> badPath {2, 3, 4, 1};
    EXPECT_FALSE(g.confirmPath(badPath));
    list<int> badPath2 {1, 2, 4, 5, 4, 3, 4};
    EXPECT_FALSE(g.confirmPath(badPath2));
}

TEST_F(DirectedGraphFixture, bfs) {
    int startVertices[3] = {1, 6, 4};
    for (int t=0; t<3; t++) {
        int start = startVertices[t];
        // vertices are 1 to 6, so we need 7 elements in discovered array
        bool discovered[7];  // set of visited vertices
        for (size_t d=0; d<7; d++) discovered[d] = false;
        list<int> current;  // set of vertices at current distance
        list<int> next;  // all adjacent vertices to current -- pruned to remove visited
        current.push_back(start);
        int n;
        size_t i, c;
        Collect<int> collector;
        BFS(g, start, collector);
        list<int>& bfs = collector.searchOrder;
        std::cout << "BFS from " << start << ": ";
        printList(bfs);
        EXPECT_EQ(bfs.size(), g.numVertices());

        while (!bfs.empty()) {
            c = current.size();
            if (c > 0) {
                // next c vertices should be in current list
                for (i = 0; i < c; i++) {
                    n = bfs.front();
                    bfs.pop_front();
                    EXPECT_TRUE(list_search(current, n)) << "n = " << n << std::endl;
                    discovered[n] = true;
                    list<int> adj = g.getAdjacencyList(n);
                    list_merge(next, adj); // add to next group of vertices
                }
                current = list_prune(next, discovered);  // remove all visited vertices
                next.clear();
            }
            else bfs.pop_front();
        }
    }
}

TEST_F(DirectedGraphFixture, dfs) {
    int startVertices[3] = {3, 2, 5};
    for (int i=0; i<3; i++) {
        int start = startVertices[i];
        // vertices are numbered 1 to 6, so we need 7 elements in visited vector
        bool visited[7];
        for (size_t v=0; v < 7; v++) visited[v] = false;
        stack<int> trace;
        Collect<int> collector;
        DFS(g, start, collector);
        list<int>& dfs = collector.searchOrder;
        std::cout << "DFS from " << start << ": ";
        printList(dfs);
        EXPECT_EQ(dfs.size(), g.numVertices());
        // check start vertex
        int n, last;
        n = dfs.front(); dfs.pop_front();
        EXPECT_EQ(n, start);
        trace.push(n);
        visited[n] = true;
        last = n;
        while (!dfs.empty()) {
            n = dfs.front(); dfs.pop_front();
            ASSERT_FALSE(visited[n]);  // should not be duplicate
            // should be adjacent to some vertex on the stack
            while (1) {
                auto adj = g.getAdjacencyList(last);
                if (list_search(adj, n)) break;
                trace.pop();
                ASSERT_FALSE(trace.empty());
                last = trace.top();
            }
            trace.push(n);
            visited[n] = true;
            last = n;
        }
    }
}
