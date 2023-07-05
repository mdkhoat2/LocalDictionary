#include <sstream>
#include "Trie.h"

TrieNode::TrieNode() : flag(false) {
    for(int i = 0; i < 67; ++i) {
      links[i] = nullptr;
    }
}

bool TrieNode::containsKey(char ch) {
    if(ch >= 'a' && ch <= 'z')
        return (links[ch - 'a'] != nullptr);
    if(ch >= 'A' && ch <= 'Z')
        return (links[ch - 39] != nullptr);
    if(ch >= '0' && ch <= '9')
        return (links[ch + 4] != nullptr);
    if(ch == 39) // single quote
        return (links[62] != nullptr);
    if(ch == 46) // dot
        return (links[63] != nullptr);
    if(ch == 45) // hyphen
        return (links[64] != nullptr);
    if(ch == 32) // space
        return (links[65] != nullptr);
    if(ch == 47) // forward slash
        return (links[66] != nullptr);
}

void TrieNode::put(char ch, TrieNode* node) {
    if(ch >= 'a' && ch <= 'z')
        links[ch - 'a'] = node;
    else if(ch >= 'A' && ch <= 'Z')
        links[ch - 39] = node;
    else if(ch >= '0' && ch <= '9')
        links[ch + 4] = node;
    else if(ch == 39) // single quote
        links[62] = node;
    else if(ch == 46) // dot
        links[63] = node;
    else if(ch == 45) // hyphen
        links[64] = node;
    else if(ch == 32) // space
        links[65] = node;
    else if(ch == 47) // forward slash
        links[66] = node;
    else
        return;
}

TrieNode* TrieNode::get(char ch) {
    if(ch >= 'a' && ch <= 'z')
        return links[ch - 'a'];
    if(ch >= 'A' && ch <= 'Z')
        return links[ch - 39];
    if(ch >= '0' && ch <= '9')
        return links[ch + 4];
    if(ch == 39) // single quote
        return links[62];
    if(ch == 46) // dot
        return links[63];
    if(ch == 45) // hyphen
        return links[64];
    if(ch == 32) // space
        return links[65];
    if(ch == 47) // forward slash
        return links[66];
}

void TrieNode::setEnd() {
    flag = true;
}

bool TrieNode::isEnd() {
    return flag;
}

bool TrieNode::hasNoChildren()
{
    for (int i = 0; i < 67; i++)
    {
        if (links[i])
            return false;
    }
    return true;
}

void trieInsert(TrieNode*& root, std::string word, std::string wordInfo)
{
    if(root == nullptr)
        root = new TrieNode();
    TrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) {
        if(!isValidCharacter(word[i]))
            return;
        if(!node->containsKey(word[i])) {
            node->put(word[i], new TrieNode());
        }
        node = node->get(word[i]);
    }
    node->setEnd();
    node->wordInfo = wordInfo;
}

std::string trieSearch(TrieNode* root, std::string word)
{
    TrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) 
    {
        if(!isValidCharacter(word[i]))
            return std::string();
        if(!node->containsKey(word[i]))
            return std::string();
        node = node->get(word[i]);
    }
    if(node->isEnd())
        return node->wordInfo;
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
    int index = 0;
    if(word[depth] >= 'a' && word[depth] <= 'z')
        index = word[depth] - 'a';
    else if(word[depth] >= 'A' && word[depth] <= 'Z')
        index = word[depth] - 39;
    else if(word[depth] >= '0' && word[depth] <= '9')
        index = word[depth] + 4;
    else if(word[depth] == 39) // single quote
        index = 62;
    else if(word[depth] == 46) // dot
        index = 63;
    else if(word[depth] == 45) // hyphen
        index = 64;
    else if(word[depth] == 32) // space
        index = 65;
    else if(word[depth] == 47) // forward slash
        index = 66;
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
    for(int i = 0; i < 67; ++i)
    {
        trieDeleteAll(root->links[i]);
    }
    delete root;
}

std::string engEngSearch(TrieNode *root, std::string &word)
{
    std::string result = trieSearch(root, word);
    // If there is a word looks the same as inputWord
    if(!result.empty())
        return result;
    // Uppercase all characters
    for(int i = 0; i < word.length(); ++i)
    {
        if(word[i] >= 'a' && word[i] <= 'z')
            word[i] = toupper(word[i]);
    }
    result = trieSearch(root, word);
    if(!result.empty())
        return result;
    // Lowercase all characters of inputWord
    for(int i = 0; i < word.length(); ++i)
    {
        word[i] = tolower(word[i]);
    }
    result = trieSearch(root, word);
    if(!result.empty())
        return result;
    // Lowercase all characters and uppercase first character of first single word
    word[0] = toupper(word[0]);
    result = trieSearch(root, word);
    if(!result.empty())
        return result;
    // Lowercase all characters and uppercase first character of second single word
    word[0] = tolower(word[0]);
    int i = 0;
    while(word[i] != ' ' && i < word.length())
        ++i;
    if(i < word.length() && word[i] == ' ')
    {
        if(word[i+1] >= 'a' && word[i+1] <= 'z')
            word[i+1] = toupper(word[i+1]);
    }
    result = trieSearch(root, word);
    if(!result.empty())
        return result;
    // Lowercase all characters and uppercase all first characters of each single word
    for(int i = 0; i < word.length(); ++i)
    {
        if(i == 0)
            word[0] = toupper(word[0]);
        if(word[i-1] == ' ')
            word[i] = toupper(word[i]);
    }
    result = trieSearch(root, word);
    if(!result.empty())
        return result;
    return std::string();
}
