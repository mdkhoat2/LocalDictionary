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
    std::string engEngWordInfo;
    std::string engVieWordInfo;
    std::string vieEngWordInfo;

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
void trieInsertEngEng(EngTrieNode*& root, std::string& word, std::string& wordInfo);
void trieInsertEngVie(EngTrieNode*& root, std::string& word, std::string& wordInfo);
void trieInsertVieEng(EngTrieNode*& root, std::string& word, std::string& wordInfo);

std::string trieSearchEngEng(EngTrieNode* root, std::string& word);
std::string trieSearchEngVie(EngTrieNode* root, std::string& word);
std::string trieSearchVieEng(EngTrieNode* root, std::string& word);

EngTrieNode* trieRemove(EngTrieNode*& root, std::string word, int depth = 0);

void trieDeleteAll(EngTrieNode* &root);

// Search functions
std::string filterAndSearchEngEng(EngTrieNode* root, std::string &word);
std::string filterAndSearchEngVie(EngTrieNode* root, std::string &word);
std::string filterAndSearchVieEng(EngTrieNode* root, std::string &word);

#endif // TRIE_H
