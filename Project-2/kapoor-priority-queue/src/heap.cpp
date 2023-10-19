#include "heap.h"

// Constructor
heap::heap(int capacity) : capacity(capacity), currentSize(0), mapping(capacity * 2)
{
    data.resize(capacity + 1); // 1-based indexing, so resize to capacity + 1
}

// Insert method
int heap::insert(const std::string &id, int key, void *pv)
{
    if (currentSize == capacity)
    {
        return 1; // heap is full
    }
    if (mapping.contains(id))
    {
        return 2; // id already exists
    }
    // Insert the new node at the end of the heap
    currentSize++;
    node newNode;
    newNode.id = id;
    newNode.key = key;
    newNode.pData = pv;
    data[currentSize] = newNode;
    // Update the mapping hash table
    mapping.insert(id, &data[currentSize]);
    // Restore the heap order property
    percolateUp(currentSize);
    return 0;
}

// setKey method
int heap::setKey(const std::string &id, int key)
{
    bool b;
    node *pn = static_cast<node *>(mapping.getPointer(id, &b));
    if (!b)
    {
        return 1; // id does not exist
    }
    int pos = getPos(pn);
    data[pos].key = key;
    if (key < data[pos / 2].key)
    {
        percolateUp(pos);
    }
    else
    {
        percolateDown(pos);
    }
    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    if (currentSize == 0)
    {
        return 1; // heap is empty
    }
    if (pId != nullptr)
    {
        *pId = data[1].id;
    }
    if (pKey != nullptr)
    {
        *pKey = data[1].key;
    }
    if (ppData != nullptr)
    {
        *(static_cast<void **>(ppData)) = data[1].pData;
    }
    mapping.remove(data[1].id); // Ensuring the item is removed from the mapping
    data[1] = data[currentSize--];
    percolateDown(1); // Ensure heap integrity after deletion
    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData)
{
    bool b;
    node *pn = static_cast<node *>(mapping.getPointer(id, &b));
    if (!b)
    {
        return 1; // id does not exist in the mapping
    }
    int pos = getPos(pn);
    if (pKey != nullptr)
    {
        *pKey = data[pos].key;
    }
    if (ppData != nullptr)
    {
        *(static_cast<void **>(ppData)) = data[pos].pData;
    }
    data[pos] = data[currentSize--];
    mapping.remove(id); // Ensure the item is removed from the mapping

    // No need to mark the node as deleted using pn->key = -1;

    if (pos <= currentSize)
    { // Check if we're not outside the range after decreasing currentSize
        if (pos > 1 && data[pos].key < data[pos / 2].key)
        {
            percolateUp(pos);
        }
        else
        {
            percolateDown(pos);
        }
    }
    return 0;
}

void heap::percolateUp(int hole)
{
    node tmp = data[hole];
    for (; hole > 1 && tmp.key < data[hole / 2].key; hole /= 2)
    {
        data[hole] = data[hole / 2];
        mapping.setPointer(data[hole].id, &data[hole]); // update hash table
    }
    data[hole] = tmp;
    mapping.setPointer(data[hole].id, &data[hole]); // update hash table
}

void heap::percolateDown(int hole)
{
    int child;
    node tmp = data[hole];

    for (; hole * 2 <= currentSize; hole = child)
    {
        child = hole * 2;
        if (child != currentSize && data[child + 1].key < data[child].key)
        {
            child++; // choose the smaller child
        }
        if (data[child].key < tmp.key)
        {
            data[hole] = data[child];
            mapping.setPointer(data[hole].id, &data[hole]); // update hash table
        }
        else
        {
            break;
        }
    }
    data[hole] = tmp;
    mapping.setPointer(data[hole].id, &data[hole]); // update hash table
}

int heap::getPos(node *pn)
{
    int pos = pn - &data[0];
    return pos;
}
