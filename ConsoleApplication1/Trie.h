#ifndef TRIE_H
#define TRIE_H

#include "WordData.h"

struct TrieNode
{
    // Member variables
    /*
        Indices for characters
        0 -> 25: a -> z
        26 -> 51: A -> Z
        52 -> 61: 0 -> 9
        62: '
        63: .
        64: -
        65: [space]
    */
    TrieNode* links[66];
    bool flag;
    std::string wordInfo;

    // Constructor
    TrieNode();

    // Member functions
    bool containsKey(char ch);
    void put(char ch, TrieNode* node);
    TrieNode* get(char ch);
    void setEnd();
    bool isEnd();
    bool hasNoChildren();
};

// Functions about Trie opearations 
void trieInsert(TrieNode*& root, std::string word, std::string wordInfo);
std::string trieSearch(TrieNode* root, std::string word);
TrieNode* trieRemove(TrieNode*& root, std::string word, int depth = 0);
void trieDeleteAll(TrieNode* &root);



#endif // TRIE_H
