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

// This word data is built to read from EE.txt
// However, it it not suitable for edit definition and add new word
// because word type doesn't limit to only 4 types
// Use WordDataEngVie instead
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
    bool isEdited;
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
void removeEndLineInString(std::string& str);

// Functions to extract different components of a word form "wordInfo" variable
void extractWordData(WordData &theWordData, std::string word, std::string wordInfo);
void extractEngEngData(WordDataEngVie &engEngData, std::string &word, std::string &wordInfo);
void extractEngVieData(WordDataEngVie& engVieData, std::string& word, std::string& wordInfo);
void extractVieEngData(WordDataEngVie& vieEngData, std::string& word, std::string& wordInfo);

// Functions to recover the wordInfo from the data structures
std::string recoverEngEngWordInfo(WordDataEngVie& theWordData);

// Functions to read and write edit from file
void saveEditToFile(WordDataEngVie& theData, int currentDataSetID);
void loadEditFromFile(WordDataEngVie& theData, int currentDataSetID);
void extractEditFile(WordDataEngVie& engEngData, int currentDataSetID);

void separateEngEngExample(std::string& wordInfo);
std::string formatEngEngWordInfo(std::string& wordInfo);

#endif