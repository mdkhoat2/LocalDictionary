#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

struct WordInfo
{
    std::string word;
    std::vector<std::string> wordTypes;
    std::vector<std::string> wordDefinitions;
};

struct TrieNode
{
    // Member variables
    TrieNode* links[26];
    bool flag;
    WordInfo* wordInfo;
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
void trieInsert(TrieNode*& root, WordInfo wordInfo);
bool trieSearch(TrieNode* root, std::string word);
TrieNode* trieRemove(TrieNode*& root, std::string word, int depth = 0);

// Functions to read from file
void getWordInfoFromString(WordInfo &wordInfo, std::string def);

#endif // TRIE_H
