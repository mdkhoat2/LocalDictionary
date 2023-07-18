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
    ~WordData();
    
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
void deleteAllList(WordDefNode* &head);
int countNumOfDefs(WordData& theWordData);

// Helper functions
bool isValidEngChar(wchar_t ch);
bool isValidWordType(std::string wordType);
bool isValidWord(std::string word);
bool isNumber(std::string numStr);
void convertToNormalChar(wchar_t &ch);
void convertToNormalLine(std::wstring &line);

// Function to extract different components of a word form "wordInfo" variable
void extractWordData(WordData &theWordData, std::string word, std::string wordInfo);

#endif