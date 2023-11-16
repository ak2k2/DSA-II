#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>
#include "hash.h"

class heap
{
public:
    heap(int capacity); // constructor
    int insert(const std::string &id, int key, void *pv = nullptr);
    int setKey(const std::string &id, int key);
    int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);
    int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);
    bool isInMapping(const std::string &id);

private:
    class node
    { // nested class for heap nodes
    public:
        std::string id;
        int key;
        void *pData;
    };

    int capacity;           // maximum capacity of the heap
    int currentSize;        // current size of the heap
    std::vector<node> data; // vector to hold heap data
    hashTable mapping;      // hash table to hold the position of each node in the heap

    // additional private functions to help with heap operations
    void percolateUp(int hole);
    void percolateDown(int hole);
    int getPos(node *pn);
};

#endif // HEAP_H
