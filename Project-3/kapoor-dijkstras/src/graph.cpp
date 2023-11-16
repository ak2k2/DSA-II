#include "graph.h"
#include "heap.h"
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>

Graph::Node::Node(const std::string &identifier)
    : id(identifier), dist(std::numeric_limits<int>::max()), prev(nullptr) {}

// Graph constructor
Graph::Graph(int capacity) : nodeTable(new hashTable(capacity)), priorityQueue(new heap(capacity)) {}

// Graph destructor
Graph::~Graph()
{
    delete nodeTable;
    delete priorityQueue;
}

// For input verification
bool Graph::hasVertex(const std::string &id)
{
    return nodeTable->contains(id);
}

// Load graph from file
int Graph::loadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return -1;
    }

    std::string line, srcId, destId;
    int cost;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        if (!(iss >> srcId >> destId >> cost))
        {
            std::cerr << "Error reading line: " << line << std::endl;
            continue;
        }

        Node *srcNode = getNode(srcId);
        Node *destNode = getNode(destId);
        srcNode->adjacencyList.push_back(Edge(destNode, cost));
    }
    file.close();
    return 0;
}

// Get node by ID
Graph::Node *Graph::getNode(const std::string &id)
{
    Node *node;
    bool exists;
    void *pv = nodeTable->getPointer(id, &exists);
    if (exists)
    {
        node = static_cast<Node *>(pv);
    }
    else
    {
        nodes.push_back(Node(id));
        node = &nodes.back();
        nodeTable->insert(id, node);
    }
    return node;
}

// Apply Dijkstra's algorithm
void Graph::applyDijkstra(const std::string &startId)
{
    Node *startNode = getNode(startId);
    if (!startNode)
    {
        std::cerr << "Start node not found in graph." << std::endl;
        return;
    }
    dijkstra(startNode);
}

void Graph::dijkstra(Node *startNode)
{
    startNode->dist = 0;
    priorityQueue->insert(startNode->id, 0, startNode);

    std::string id;
    Node *node;
    while (priorityQueue->deleteMin(&id, nullptr, &node) == 0)
    {
        for (auto &edge : node->adjacencyList) // For each edge in adjacency list
        {
            Node *destNode = edge.dest;           // Get destination node
            int newDist = node->dist + edge.cost; // Calculate new distance
            if (newDist < destNode->dist)         // If new distance is less than current distance
            {
                destNode->dist = newDist; // Update distance
                destNode->prev = node;    // Update previous node

                if (priorityQueue->isInMapping(destNode->id)) // If node is already in priority queue
                {
                    priorityQueue->setKey(destNode->id, newDist); // Update key
                }
                else
                {
                    priorityQueue->insert(destNode->id, newDist, destNode); // Insert node into priority queue
                }
            }
        }
    }
}

void Graph::writeToFile(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Unable to open output file: " << filename << std::endl;
        return;
    }

    for (auto &node : nodes)
    {
        outputPath(outFile, &node);
    }
    outFile.close();
}

void Graph::outputPath(std::ofstream &outFile, Node *node)
{
    outFile << node->id << ": ";
    if (node->dist == std::numeric_limits<int>::max())
    {
        outFile << "NO PATH\n";
    }
    else
    {
        outFile << node->dist << " [";
        std::vector<std::string> path;
        for (Node *n = node; n != nullptr; n = n->prev)
        {
            path.push_back(n->id);
        }
        std::reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); ++i)
        {
            if (i > 0)
                outFile << ", ";
            outFile << path[i];
        }
        outFile << "]\n";
    }
}
int main()
{
    Graph myGraph(10000000); // Initialize graph with capacity of 10_000_000 (10 million)

    std::string graphFilename, startVertexId, outputFilename;
    std::cout << "Enter name of graph file: ";
    std::cin >> graphFilename;

    if (myGraph.loadFromFile(graphFilename) != 0)
    {
        return 1;
    }

    bool validStartVertex = false;
    while (!validStartVertex)
    {
        std::cout << "Enter name of starting vertex: ";
        std::cin >> startVertexId;

        // Check if the vertex exists in the graph
        if (myGraph.hasVertex(startVertexId))
        {
            validStartVertex = true;
        }
        else
        {
            std::cout << "Vertex does not exist. Please try again." << std::endl;
        }
    }

    clock_t startTime = clock();
    myGraph.applyDijkstra(startVertexId);
    clock_t endTime = clock();

    double totalTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
    std::cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << totalTime << std::endl;

    std::cout << "Enter name of output file: ";
    std::cin >> outputFilename;
    myGraph.writeToFile(outputFilename);

    return 0;
}
