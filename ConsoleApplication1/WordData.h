#ifndef WORDDATA_H
#define WORDDATA_H

#include <string>
#include <sstream>

struct WordDefNode
{
    std::string wordDef;
    WordDefNode* next = nullptr;
};

struct WordData
{
    WordData();
    WordData(std::string wordIn);
    
    // Member functions
    void consolePrint();

    // Member variables
    std::string word;
    /*
        Indices for word types:
            0 -> noun
            1 -> verb
            2 -> adjective
            3 -> adverb
        Each element in the array contains a pointer to a list of definitions corresponding to that word type
    */
    WordDefNode* defListHead[4];
};

void insertAtEnd(WordDefNode* &head, std::string wordDef);

// Helper functions
bool isValidCharacter(char ch);
bool isValidWordType(std::string wordType);
bool isNumber(std::string numStr);

// Function to extract different components of a word form "wordInfo" variable
void extractWordData(WordData &theWordData, std::string word, std::string wordInfo);

#endif