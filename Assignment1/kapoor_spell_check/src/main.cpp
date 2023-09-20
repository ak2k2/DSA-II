#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <ctime>
#include <algorithm>
#include "hashTable.h"
#include "DictionaryLoader.h"

bool isValidChar(char ch)
{
    return std::isalpha(ch) || std::isdigit(ch) || ch == '-' || ch == '\'';
}

void checkWord(std::string word, int lineNumber, hashTable &ht, std::ofstream &outputFile)
{
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    int maxWordLength = 20; // Maximum length of a valid word

    if (word.length() > maxWordLength)
    {
        outputFile << "Long word at line " << lineNumber << ", starts: " << word.substr(0, maxWordLength) << std::endl;
        return; // Return early; no need to spell-check long words
    }

    // Ignore words that contain digits, hyphens, or apostrophes
    if (std::any_of(word.begin(), word.end(), [](char ch)
                    { return std::isdigit(ch) || ch == '-' || ch == '\''; }))
    {
        return;
    }

    if (!ht.contains(word)) // Check if the word is in the dictionary
    {
        outputFile << "Unknown word at line " << lineNumber << ": " << word << std::endl;
    }
}

int main()
{
    // Gather the names of the dictionary, input, and output files
    std::string dictionaryFile, inputFile, outputFile;
    std::cout << "Enter the name of the dictionary file: ";
    std::cin >> dictionaryFile;
    std::cout << "Enter the name of the document file to be spell-checked: ";
    std::cin >> inputFile;
    std::cout << "Enter the name of the output file: ";
    std::cin >> outputFile;

    hashTable ht(25000); // Initialize a hash table with 25000 buckets

    clock_t start = clock();
    loadDictionaryIntoHashTable(ht, dictionaryFile);
    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate the cpu time taken to load the dictionary
    std::cout << "Time taken to load dictionary: " << cpu_time_used << " seconds" << std::endl;

    std::ifstream inStream(inputFile);
    std::ofstream outStream(outputFile);

    if (!inStream.is_open())
    {
        std::cerr << "Could not open " << inputFile << std::endl;
        return 1;
    }

    std::string line;
    int lineNumber = 0;
    std::string temp;

    start = clock();
    while (std::getline(inStream, line))
    {
        lineNumber++;
        for (char ch : line)
        {
            if (isValidChar(ch))
            {
                temp.push_back(ch); // Add the character to a temporary string
            }
            else
            {
                if (!temp.empty()) // If the temporary string is not empty, check the word
                {
                    checkWord(temp, lineNumber, ht, outStream);
                    temp.clear(); // Clear the temporary string
                }
            }
        }

        if (!temp.empty()) // Handle the last word in the line separately
        {
            checkWord(temp, lineNumber, ht, outStream);
            temp.clear();
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate the cpu time taken to spell check the input file
    std::cout << "Time taken to spell check the file: " << cpu_time_used << " seconds" << std::endl;

    inStream.close();
    outStream.close();
    return 0;
}
