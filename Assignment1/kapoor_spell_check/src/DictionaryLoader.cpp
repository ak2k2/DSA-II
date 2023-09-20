#include "DictionaryLoader.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>

void loadDictionaryIntoHashTable(hashTable &ht, const std::string &filename)
{
    std::ifstream dictFile(filename);
    if (!dictFile.is_open())
    {
        std::cerr << "Could not open " << filename << std::endl;
        return;
    }

    std::string word;
    unsigned int wordCount = 0; // Counter to keep track of the number of words loaded

    while (std::getline(dictFile, word))
    {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower); // Convert word to lowercase
        ht.insert(word);
        ++wordCount; // Increment the counter
    }

    dictFile.close();

    // Display how many words were loaded into the hash table
    std::cout << "Successfully loaded " << wordCount << " words into the hash table." << std::endl;
}
