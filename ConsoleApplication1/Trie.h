#ifndef TRIE_H
#define TRIE_H

#include "WordData.h"
struct EngTrieNode
{
    /*
        Indices for characters
        0 -> 25: a -> z
        26 -> 51: A -> Z
        52 -> 61: 0 -> 9
        62: '
        63: .
        64: -
        65: [space]
        66: /
        67: ,
        68: &
        69: !
        70: :
        71: ?
    */
    // Member variables
    EngTrieNode* links[72];
    bool flag;
    
    // These are the indices to the vector of WordEngVieData in class Application
    // We do this to optimize the space of Trie
    int engEngIndex;
    int engVieIndex;
    int vieEngIndex;
    int emojiIndex;

    // Member variable for remove function
    bool isEEDeleted;
    bool isEVDeleted;
    bool isVEDeleted;
    bool isEmojiDeleted;

    // Constructor
    EngTrieNode();

    // Member functions
    bool containsKey(char ch);
    void put(char ch, EngTrieNode* node);
    EngTrieNode* get(char ch);
    bool hasNoChildren();
};

struct VieTrieNode
{
    VieTrieNode* links[89];
    bool flag;
    std::string wordInfo;

    //Constructor
    VieTrieNode();

    // Member functions
    bool containsKey(wchar_t ch);
    void put(wchar_t ch, VieTrieNode* node);
    VieTrieNode* get(wchar_t ch);
    bool hasNoChildren();
};

// Functions about Trie operations 
void trieInsert(EngTrieNode*& root, std::string& word, int wordIndex, int curDataSetID);

int trieSearch(EngTrieNode* root, std::string word, int curDataSetID);

// Don't use this function remove because it can contain bug!
EngTrieNode* trieRemove(EngTrieNode*& root, std::string word, int depth = 0);
VieTrieNode* trieRemove(VieTrieNode*& root, std::wstring word, int depth = 0);

// This function is use for removing words by flagging them with isDelete variable
void trieHide(EngTrieNode* root, std::string word, int curDataSetID);

void trieDeleteAll(EngTrieNode* &root);
void trieDeleteAll(VieTrieNode* &root);

// Search functions
int filterAndSearch(EngTrieNode* root, std::string &word, int curDataSetID);

//Remove space
std::string trim(const std::string& str);

// Serialize and Deserialize Trie
std::string serialize(EngTrieNode* root);
EngTrieNode* deserialize(std::string data);
void saveSerializedTrie(EngTrieNode* root);
bool loadSerializedTrie(EngTrieNode*& root);


#endif // TRIE_H
