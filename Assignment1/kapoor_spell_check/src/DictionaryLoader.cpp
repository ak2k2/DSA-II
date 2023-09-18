#include "DictionaryLoader.h"
#include <iostream>
#include <fstream>
#include <ctime>

void loadDictionaryIntoHashTable(hashTable &ht, const std::string &filename) {
    std::ifstream dictFile(filename);
    if (!dictFile.is_open()) {
        std::cerr << "Could not open " << filename << std::endl;
        return;
    }

    std::string word;
    while (std::getline(dictFile, word)) { // Read each word from the dictionary file and insert it into the hash table
        ht.insert(word);
    }

    dictFile.close();
}
