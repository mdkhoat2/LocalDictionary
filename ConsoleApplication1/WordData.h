#ifndef WORDDATA_H
#define WORDDATA_H

#include <string>
#include <sstream>
#include <vector>

struct WordDefNode
{
    std::string wordDef;
    std::string wordExample;
    WordDefNode* next = nullptr;
};

struct WordData
{
public:
    WordData();
    ~WordData();
    
    // Member functions
    void consolePrint();
public:
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

struct EngVieDef
{
public:
    EngVieDef();
    void clear();
    bool empty();
public:
    std::string wordType;
    std::pair<std::string, std::string> defAndExample;
};

struct WordDataEngVie
{
public:
    WordDataEngVie();
    void consolePrint();
public:
    std::string word;
    std::vector<EngVieDef> defList;
};

void insertAtEnd(WordDefNode* &head, std::string wordDef);
void insertAtEnd(WordDefNode* &head, WordDefNode* theNode);
void deleteAllList(WordDefNode* &head);
int countNumOfDefs(WordData& theWordData);

// Helper functions
bool isValidEngChar(wchar_t ch);
bool isValidWordType(std::string wordType);
bool isNumber(std::string numStr);
void convertToNormalChar(wchar_t &ch);
void convertToNormalLine(std::wstring &line);

// Function to extract different components of a word form "wordInfo" variable
void extractWordData(WordData &theWordData, std::string word, std::string wordInfo);
void extractEngVieData(WordDataEngVie& engVieData, std::string& word, std::string& wordInfo);
void extractVieEngData(WordDataEngVie& vieEngData, std::string& word, std::string& wordInfo);

void separateEngEngExample(std::string& wordInfo);

#endif