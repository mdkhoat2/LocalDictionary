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
    */
    // Member variables
    EngTrieNode* links[67];
    bool flag;
    std::string wordInfo;
    std::wstring vieWordInfo;

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

// Functions about Trie opearations 
void trieInsert(EngTrieNode*& root, std::string word, std::string wordInfo);
void trieInsert(VieTrieNode*& root, std::wstring word, std::wstring wordInfo);

std::string trieSearch(EngTrieNode* root, std::string word);
std::wstring trieSearch(VieTrieNode* root, std::wstring word);

EngTrieNode* trieRemove(EngTrieNode*& root, std::string word, int depth = 0);
VieTrieNode* trieRemove(VieTrieNode*& root, std::wstring word, int depth = 0);

void trieDeleteAll(EngTrieNode* &root);
void trieDeleteAll(VieTrieNode* &root);

// Search functions
std::string filterAndSearch(EngTrieNode* root, std::string &word);
std::string filterAndSearch(EngTrieNode* root, std::string &word);

#endif // TRIE_H
