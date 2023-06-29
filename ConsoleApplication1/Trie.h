#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>


struct TrieNode
{
    // Member variables
    TrieNode* links[26];
    bool flag;
    std::string wordDef;

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
void trieInsert(TrieNode*& root, std::string word, std::string wordDef);
std::string trieSearch(TrieNode* root, std::string word);
TrieNode* trieRemove(TrieNode*& root, std::string word, int depth = 0);
void trieDeleteAll(TrieNode* &root);

// Functions to read from file

bool isValidWord(std::string word);

#endif // TRIE_H
