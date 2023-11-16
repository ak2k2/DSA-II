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
    bool exists;
    node *pn = static_cast<node *>(mapping.getPointer(id, &exists));
    if (!exists)
    {
        return 1; // id does not exist
    }
    int currentKey = pn->key;
    pn->key = key;
    int pos = getPos(pn);
    if (key < currentKey)
    {
        percolateUp(pos); // Move up the node if the new key is smaller
    }
    else
    {
        percolateDown(pos); // Move down the node if the new key is larger
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
    // If the node to be removed is the last node, we can simply decrease the currentSize
    if (pos == currentSize)
    {
        currentSize--;
        mapping.remove(id); // Ensure the item is removed from the mapping
        return 0;
    }
    data[pos] = data[currentSize--];              // Move the last item to the position of the one being removed
    mapping.setPointer(data[pos].id, &data[pos]); // Update the mapping for the moved node
    mapping.remove(id);                           // Remove the old id from the mapping

    // Restore the heap order property
    if (pos > 1 && data[pos].key < data[pos / 2].key)
    {
        percolateUp(pos);
    }
    else
    {
        percolateDown(pos);
    }
    return 0;
}

void heap::percolateUp(int hole)
{
    node tmp = data[hole];
    // Move up as long as there's a parent and the tmp node is smaller than the parent
    for (; hole > 1 && tmp.key < data[hole / 2].key; hole /= 2)
    {
        data[hole] = data[hole / 2];
        mapping.setPointer(data[hole].id, &data[hole]); // Update mapping
    }
    data[hole] = tmp;
    mapping.setPointer(tmp.id, &data[hole]); // Update mapping for the tmp node
}

void heap::percolateDown(int hole)
{
    int child;
    node tmp = data[hole];

    while (hole * 2 <= currentSize)
    {
        child = hole * 2;
        // Check if there is a right child and if it's smaller than the left child
        if (child != currentSize && data[child + 1].key < data[child].key)
        {
            child++; // Right child is smaller, so target it for potential swap
        }
        // If the smaller child is less than the temp node, swap it
        if (data[child].key < tmp.key)
        {
            data[hole] = data[child];
            mapping.setPointer(data[hole].id, &data[hole]); // Update mapping
        }
        else
        {
            // If no swap needed, we are done
            break;
        }
        hole = child; // Move the hole down to the child's position
    }
    // Place the temporary node in the correct spot
    data[hole] = tmp;
    mapping.setPointer(tmp.id, &data[hole]); // Update mapping for the temp node
}

int heap::getPos(node *pn)
{
    int pos = pn - &data[0];
    return pos;
}

bool heap::isInMapping(const std::string &id) {
    return mapping.contains(id);
}
