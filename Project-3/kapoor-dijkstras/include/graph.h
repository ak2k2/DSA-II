#ifndef GRAPH_H
#define GRAPH_H

#include "hash.h"
#include "heap.h"
#include <list>
#include <string>
#include <vector>

class Graph
{
public:
    Graph(int capacity);
    ~Graph();
    int loadFromFile(const std::string &filename);
    void applyDijkstra(const std::string &start);
    void writeToFile(const std::string &filename);
    bool hasVertex(const std::string &id);

private:
    class Node;

    // Edge structure
    struct Edge
    {
        Node *dest;
        int cost;
        Edge(Node *dst, int c) : dest(dst), cost(c) {}
    };

    // Graph Node
    class Node
    {
    public:
        std::string id;
        std::list<Edge> adjacencyList;
        int dist;   // Shortest distance from the start node
        Node *prev; // Pointer to the previous node in the shortest path

        Node(const std::string &identifier); // Constructor
    };

    // Members
    std::list<Node> nodes;
    hashTable *nodeTable;
    heap *priorityQueue;

    // Helper functions
    Node *getNode(const std::string &id);
    void dijkstra(Node *startNode);
    void outputPath(std::ofstream &outFile, Node *node);
};

#endif // GRAPH_H
