#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

class hashTable
{
public:
    hashTable(int size = 101);
    int insert(const std::string &key, void *pv = nullptr);
    bool contains(const std::string &key);
    void *getPointer(const std::string &key, bool *b = nullptr);
    int setPointer(const std::string &key, void *pv);
    bool remove(const std::string &key);

private:
    class hashItem
    {
    public:
        std::string key;
        void *pv;        // pointer associated with key
        bool isOccupied; // if the item is occupied
        bool isDeleted;  // if the item is deleted

        hashItem() : pv(nullptr), isOccupied(false), isDeleted(false) {}
    };

    int capacity;               // The current capacity of the hash table.
    int filled;                 // Number of occupied items in the table.
    std::vector<hashItem> data; // The actual entries are here.

    int hash(const std::string &key);
    int findPos(const std::string &key);
    bool rehash();
    static unsigned int getPrime(int size);
};

#endif // HASHTABLE_H
