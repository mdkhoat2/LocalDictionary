#include <sstream>
#include "Trie.h"

TrieNode::TrieNode() : flag(false) {
    for(int i = 0; i < 26; ++i) {
      links[i] = nullptr;
    }
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

void trieInsert(TrieNode*& root, std::string word, std::string wordDef)
{
    if(root == nullptr)
        root = new TrieNode();
    TrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) {
        if(word[i] < 'a' || word[i] > 'z')
            return;
        if(!node->containsKey(word[i])) {
            node->put(word[i], new TrieNode());
        }
        node = node->get(word[i]);
    }
    node->setEnd();
    node->wordDef = wordDef;
}

std::string trieSearch(TrieNode* root, std::string word)
{
    TrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) 
    {
        if(word[i] < 'a' || word[i] > 'z')
            return "";
        if(!node->containsKey(word[i]))
            return "";
        node = node->get(word[i]);
    }
    if(node->isEnd())
        return node->wordDef;
}

TrieNode* trieRemove(TrieNode*& root, std::string word, int depth)
{
    if (!root)
        return nullptr;

    if (depth == word.size()) {

        if (root->flag)
            root->flag = false;

        if (root->hasNoChildren()) {
            delete root;
            root = nullptr;
        }

        return root;
    }

    int index = word[depth] - 'a';
    root->links[index] = trieRemove(root->links[index], word, depth + 1);

    if (root->hasNoChildren() && root->flag == false) {
        delete root;
        root = nullptr;
    }

    return root;
}

void trieDeleteAll(TrieNode* &root)
{
    if(root == nullptr)
        return;
    for(int i = 0; i < 26; ++i)
    {
        trieDeleteAll(root->links[i]);
    }
    delete root;
}

bool isValidWord(std::string word)
{
    for(int i = 0; i < word.length(); ++i)
    {
        if(word[i] < 'a' || word[i] > 'z')
            return false;
    }
    return true;
}
