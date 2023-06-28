#include <sstream>
#include "Trie.h"

TrieNode::TrieNode() : flag(false) {
    for(int i = 0; i < 26; ++i) {
      links[i] = nullptr;
    }
    wordInfo = nullptr;
}

bool TrieNode::containsKey(char ch) {
    return (links[ch - 'a'] != nullptr);
}

void TrieNode::put(char ch, TrieNode* node) {
    links[ch - 'a'] = node;
}

TrieNode* TrieNode::get(char ch) {
    return links[ch - 'a'];
}

void TrieNode::setEnd() {
    flag = true;
}

bool TrieNode::isEnd() {
    return flag;
}

bool TrieNode::hasNoChildren()
{
    for (int i = 0; i < 26; i++)
    {
        if (links[i])
            return false;
    }
    return true;
}

void trieInsert(TrieNode*& root, WordInfo wordInfoInsert)
{
    std::string word = wordInfoInsert.word;
    TrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) {
        if(!node->containsKey(word[i])) {
            node->put(word[i], new TrieNode());
        }
        node = node->get(word[i]);
    }
    node->setEnd();
    node->wordInfo = new WordInfo;
    node->wordInfo->word = wordInfoInsert.word;
    node->wordInfo->wordTypes = wordInfoInsert.wordTypes;
    node->wordInfo->wordDefinitions = wordInfoInsert.wordDefinitions;
}

bool trieSearch(TrieNode* root, std::string word)
{
    TrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) {
        if(!node->containsKey(word[i]))
            return false;
        node = node->get(word[i]);
    }
    return node->isEnd();
}

TrieNode* trieRemove(TrieNode*& root, std::string word, int depth)
{
    if (!root)
        return nullptr;

    if (depth == word.size()) {

        if (root->flag)
            root->flag = false;

        if (root->hasNoChildren()) {
            delete root->wordInfo;
            delete root;
            root = nullptr;
        }

        return root;
    }

    int index = word[depth] - 'a';
    root->links[index] = trieRemove(root->links[index], word, depth + 1);

    if (root->hasNoChildren() && root->flag == false) {
        delete root->wordInfo;
        delete root;
        root = nullptr;
    }

    return root;
}

void getWordInfoFromString(WordInfo &wordInfo, std::string def)
{
    

}
