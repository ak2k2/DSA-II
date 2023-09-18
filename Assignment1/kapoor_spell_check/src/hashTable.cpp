#include "hashTable.h"

hashTable::hashTable(int size)
{
    capacity = getPrime(size);
    filled = 0;
    data.resize(capacity);
}

int hashTable::insert(const std::string &key, void *pv)
{
    int pos = findPos(key); // Find the position of the key
    if (pos == -1)
    {
        return 2; // Rehash failed
    }

    // insert the key, set the pv, and set isOccupied to true
    data[pos].key = key;
    data[pos].pv = pv;
    data[pos].isOccupied = true;
    data[pos].isDeleted = false;

    if (++filled > capacity / 2) // If the table is more than half full
    {
        if (!rehash())
        {
            return 2; // Rehash failed
        }
    }

    return 0; // Success
}

bool hashTable::contains(const std::string &key)
{
    int pos = findPos(key);
    return data[pos].isOccupied && data[pos].key == key && !data[pos].isDeleted; // Check if the key is occupied and not deleted
}

void *hashTable::getPointer(const std::string &key, bool *b)
{
    int pos = findPos(key); // Find the position of the key
    if (pos != -1) // If the key is found and b is not null, set b to true
    {
        if (b != nullptr)
        {
            *b = true;
        }
        return data[pos].pv; // Return the pointer to the key
    }
    if (b != nullptr)  // If the key is not found and b is not null, set b to false
    {
        *b = false;
    }
    return nullptr; // Return nullptr if the key is not found
}

int hashTable::setPointer(const std::string &key, void *pv)
{
    int pos = findPos(key);
    if (pos != -1) // If the key is found, set the pointer to pv and return 0
    {
        data[pos].pv = pv;
        return 0;
    }
    return 1;
}

bool hashTable::remove(const std::string &key)
{
    int pos = findPos(key); 
    if (pos != -1) // If the key is found, set isDeleted to true and return true
    {
        data[pos].isDeleted = true;
        return true;
    }
    return false;
}

int hashTable::hash(const std::string &key)
{
    int hashVal = 0;
    for (char ch : key) // Horner's method
    {
        hashVal = 37 * hashVal + ch; // https://userweb.cs.txstate.edu/~js236/201207/cs3358/hashtables.pdf
    }
    hashVal %= capacity;
    if (hashVal < 0)
    {
        hashVal += capacity;
    }
    return hashVal;
}

int hashTable::findPos(const std::string &key)
{
    int offset = 1;
    int currentPos = hash(key);
    // While the current position is occupied and the key is not found
    while (data[currentPos].isOccupied &&
           data[currentPos].key != key)
    {
        currentPos += offset; // Compute ith probe
        offset += 2;          // Use quadratic probing
        if (currentPos >= capacity)
        {
            currentPos -= capacity;
        }
    }
    return currentPos;
}

bool hashTable::rehash()
{
    std::vector<hashItem> oldData = data;
    capacity = getPrime(2 * capacity);
    filled = 0;
    data.clear();
    data.resize(capacity);

    for (const auto &entry : oldData)
    {
        if (entry.isOccupied && !entry.isDeleted) // If the entry is occupied and not deleted, insert the entry into the new hash table
        {
            insert(entry.key, entry.pv);
        }
    }
    return true;
}

unsigned int hashTable::getPrime(int size)
{
    static const unsigned int primes[] = {// sourced from: https://planetmath.org/goodhashtableprimes
                                          2, 5, 53, 97, 193, 389, 769, 1543, 3079, 6151,
                                          12289, 24593, 49157, 98317, 196613, 393241, 786433,
                                          1572869, 3145739, 6291469, 12582917, 25165843, 50331653,
                                          100663319, 201326611, 402653189, 805306457, 1610612741};
    for (auto prime : primes)
    {
        if (prime >= size)
        {
            return prime;
        }
    }
    return size;
}
