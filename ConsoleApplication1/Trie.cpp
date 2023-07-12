#include <sstream>
#include "Trie.h"

EngTrieNode::EngTrieNode() : flag(false) 
{
    for(int i = 0; i < 67; ++i) 
      links[i] = nullptr;
}

bool EngTrieNode::containsKey(char ch) 
{
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

void EngTrieNode::put(char ch, EngTrieNode* node) 
{
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
}

EngTrieNode* EngTrieNode::get(char ch) 
{
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

bool EngTrieNode::hasNoChildren()
{
    for (int i = 0; i < 67; i++)
    {
        if (links[i])
            return false;
    }
    return true;
}

void trieInsert(EngTrieNode*& root, std::string word, std::string wordInfo)
{
    if(root == nullptr)
        root = new EngTrieNode();
    EngTrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) {
        if(!node->containsKey(word[i])) {
            node->put(word[i], new EngTrieNode());
        }
        node = node->get(word[i]);
    }
    node->flag = true;
    node->wordInfo = wordInfo;
}

void trieInsertVieInfo(EngTrieNode *&root, std::wstring word, std::wstring wordInfo)
{
    if(root == nullptr)
        root = new EngTrieNode();
    EngTrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) {
        if(!node->containsKey(word[i])) {
            node->put(word[i], new EngTrieNode());
        }
        node = node->get(word[i]);
    }
    node->flag = true;
    node->vieWordInfo = wordInfo;
}

void trieInsert(VieTrieNode *&root, std::wstring word, std::string wordInfo)
{
    if(root == nullptr)
        root = new VieTrieNode();
    VieTrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) {
        if(!node->containsKey(word[i])) {
            node->put(word[i], new VieTrieNode());
        }
        node = node->get(word[i]);
    }
    node->flag = true;
    node->wordInfo = wordInfo;
}

std::string trieSearch(EngTrieNode* root, std::string word)
{
    EngTrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) 
    {
        if(!node->containsKey(word[i]))
            return std::string();
        node = node->get(word[i]);
    }
    if(node->flag && !node->wordInfo.empty())
        return node->wordInfo;
    else
        return std::string();
}

std::wstring trieSearchVieInfo(EngTrieNode *root, std::wstring word)
{
    EngTrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) 
    {
        if(!node->containsKey(word[i]))
            return std::wstring();
        node = node->get(word[i]);
    }
    if(node->flag && !node->vieWordInfo.empty())
        return node->vieWordInfo;
    else
        return std::wstring();
}

std::string trieSearch(VieTrieNode *root, std::wstring word)
{
    VieTrieNode* node = root;
    for(int i = 0; i < word.length(); ++i) 
    {
        if(!node->containsKey(word[i]))
            return std::string();
        node = node->get(word[i]);
    }
    if(node->flag)
        return node->wordInfo;
    else
        return std::string();
}

EngTrieNode* trieRemove(EngTrieNode*& root, std::wstring word, int depth)
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

VieTrieNode *trieRemove(VieTrieNode *&root, std::wstring word, int depth)
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
    // Get index in Trie
    int index = 0;
    if(word[depth] == 'a')
        index = 0;
    else if(word[depth] == L'á')
        index = 1;
    else if(word[depth] == L'à')
        index = 2;
    else if(word[depth] == L'ả')
        index = 3;
    else if(word[depth] == L'ã')
        index = 4;
    else if(word[depth] == L'ạ')
        index = 5;
    else if(word[depth] == L'â')
        index = 6;
    else if(word[depth] == L'ấ')
        index = 7;
    else if(word[depth] == L'ầ')
        index = 8;
    else if(word[depth] == L'ẩ')
        index = 9;
    else if(word[depth] == L'ẫ')
        index = 10;
    else if(word[depth] == L'ậ')
        index = 11;
    else if(word[depth] == L'ă')
        index = 12;
    else if(word[depth] == L'ắ')
        index = 13;
    else if(word[depth] == L'ằ')
        index = 14;
    else if(word[depth] == L'ẳ')
        index = 15;
    else if(word[depth] == L'ẵ')
        index = 16;
    else if(word[depth] == L'ặ')
        index = 17;
    else if(word[depth] == 'b')
        index = 18;
    else if(word[depth] == 'c')
        index = 19;
    else if(word[depth] == 'd')
        index = 20;
    else if(word[depth] == L'đ')
        index = 21;
    else if(word[depth] == 'e')
        index = 22;
    else if(word[depth] == L'é')
        index = 23;
    else if(word[depth] == L'è')
        index = 24;
    else if(word[depth] == L'ẻ')
        index = 25;
    else if(word[depth] == L'ẽ')
        index = 26;
    else if(word[depth] == L'ẹ')
        index = 27;
    else if(word[depth] == L'ê')
        index = 28;
    else if(word[depth] == L'ế')
        index = 29;
    else if(word[depth] == L'ề')
        index = 30;
    else if(word[depth] == L'ể')
        index = 31;
    else if(word[depth] == L'ễ')
        index = 32;
    else if(word[depth] == L'ệ')
        index = 33;
    else if(word[depth] == 'g')
        index = 34;
    else if(word[depth] == 'h')
        index = 35;
    else if(word[depth] == 'i')
        index = 36;
    else if(word[depth] == L'í')
        index = 37; 
    else if(word[depth] == L'ì')
        index = 38;
    else if(word[depth] == L'ỉ')
        index = 39;
    else if(word[depth] == L'ĩ')
        index = 40;
    else if(word[depth] == L'ị')
        index = 41;
    else if(word[depth] == 'k')
        index = 42;
    else if(word[depth] == 'l')
        index = 43;
    else if(word[depth] == 'm')
        index = 44;
    else if(word[depth] == 'n')
        index = 45;
    else if(word[depth] == 'o')
        index = 46;
    else if(word[depth] == L'ó')
        index = 47;
    else if(word[depth] == L'ò')
        index = 48;
    else if(word[depth] == L'ỏ')
        index = 49;
    else if(word[depth] == L'õ')
        index = 50;
    else if(word[depth] == L'ọ')
        index = 51;
    else if(word[depth] == L'ô')
        index = 52;
    else if(word[depth] == L'ố')
        index = 53;
    else if(word[depth] == L'ồ')
        index = 54;
    else if(word[depth] == L'ổ')
        index = 55;
    else if(word[depth] == L'ỗ')
        index = 56;
    else if(word[depth] == L'ộ')
        index = 57;
    else if(word[depth] == L'ơ')
        index = 58;
    else if(word[depth] == L'ớ')
        index = 59;
    else if(word[depth] == L'ờ')
        index = 60;
    else if(word[depth] == L'ở')
        index = 61;
    else if(word[depth] == L'ỡ')
        index = 62;
    else if(word[depth] == L'ợ')
        index = 63;
    else if(word[depth] == 'p')
        index = 64;
    else if(word[depth] == 'q')
        index = 65;
    else if(word[depth] == 'r')
        index = 66;
    else if(word[depth] == 's')
        index = 67;
    else if(word[depth] == 't')
        index = 68;
    else if(word[depth] == 'u')
        index = 69;
    else if(word[depth] == L'ú')
        index = 70;
    else if(word[depth] == L'ù')
        index = 71;
    else if(word[depth] == L'ủ')
        index = 72;
    else if(word[depth] == L'ũ')
        index = 73;
    else if(word[depth] == L'ụ')
        index = 74;
    else if(word[depth] == L'ư')
        index = 75;
    else if(word[depth] == L'ứ')
        index = 76;
    else if(word[depth] == L'ừ')
        index = 77;
    else if(word[depth] == L'ử')
        index = 78;
    else if(word[depth] == L'ữ')
        index = 79;
    else if(word[depth] == L'ự')
        index = 80;
    else if(word[depth] == 'v')
        index = 81;
    else if(word[depth] == 'x')
        index = 82;
    else if(word[depth] == 'y')
        index = 83;
    else if(word[depth] == L'ý')
        index = 84;
    else if(word[depth] == L'ỳ')
        index = 85;
    else if(word[depth] == L'ỷ')
        index = 86;
    else if(word[depth] == L'ỹ')
        index = 87;
    else if(word[depth] == L'ỵ')
        index = 88;

    root->links[index] = trieRemove(root->links[index], word, depth + 1);

    if (root->hasNoChildren() && root->flag == false) {
        delete root;
        root = nullptr;
    }

    return root;
}

void trieDeleteAll(EngTrieNode* &root)
{
    if(root == nullptr)
        return;
    for(int i = 0; i < 67; ++i)
    {
        trieDeleteAll(root->links[i]);
    }
    delete root;
    root = nullptr;
}

void trieDeleteAll(VieTrieNode *&root)
{
    if(root == nullptr)
        return;
    for(int i = 0; i < 89; ++i)
    {
        trieDeleteAll(root->links[i]);
    }
    delete root;
    root = nullptr;
}

std::string filterAndSearch(EngTrieNode *root, std::string &word)
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

VieTrieNode::VieTrieNode() : flag(false)
{
    for(int i = 0; i < 89; ++i)
        links[i] = nullptr;
}

bool VieTrieNode::containsKey(wchar_t ch)
{
    if(ch == 'a')
        return (links[0] != nullptr);
    if(ch == L'á')
        return (links[1] != nullptr);
    if(ch == L'à')
        return (links[2] != nullptr);
    if(ch == L'ả')
        return (links[3] != nullptr);
    if(ch == L'ã')
        return (links[4] != nullptr);
    if(ch == L'ạ')
        return (links[5] != nullptr);
    if(ch == L'â')
        return (links[6] != nullptr);
    if(ch == L'ấ')
        return (links[7] != nullptr);
    if(ch == L'ầ')
        return (links[8] != nullptr);
    if(ch == L'ẩ')
        return (links[9] != nullptr);
    if(ch == L'ẫ')
        return (links[10] != nullptr);
    if(ch == L'ậ')
        return (links[11] != nullptr);
    if(ch == L'ă')
        return (links[12] != nullptr);
    if(ch == L'ắ')
        return (links[13] != nullptr);
    if(ch == L'ằ')
        return (links[14] != nullptr);
    if(ch == L'ẳ')
        return (links[15] != nullptr);
    if(ch == L'ẵ')
        return (links[16] != nullptr);
    if(ch == L'ặ')
        return (links[17] != nullptr);
    if(ch == 'b')
        return (links[18] != nullptr);
    if(ch == 'c')
        return (links[19] != nullptr);
    if(ch == 'd')
        return (links[20] != nullptr);
    if(ch == L'đ')
        return (links[21] != nullptr);
    if(ch == 'e')
        return (links[22] != nullptr);
    if(ch == L'é')
        return (links[23] != nullptr);
    if(ch == L'è')
        return (links[24] != nullptr);
    if(ch == L'ẻ')
        return (links[25] != nullptr);
    if(ch == L'ẽ')
        return (links[26] != nullptr);
    if(ch == L'ẹ')
        return (links[27] != nullptr);
    if(ch == L'ê')
        return (links[28] != nullptr);
    if(ch == L'ế')
        return (links[29] != nullptr);
    if(ch == L'ề')
        return (links[30] != nullptr);
    if(ch == L'ể')
        return (links[31] != nullptr);
    if(ch == L'ễ')
        return (links[32] != nullptr);
    if(ch == L'ệ')
        return (links[33] != nullptr);
    if(ch == 'g')
        return (links[34] != nullptr);
    if(ch == 'h')
        return (links[35] != nullptr);
    if(ch == 'i')
        return (links[36] != nullptr);
    if(ch == L'í')
        return (links[37] != nullptr); 
    if(ch == L'ì')
        return (links[38] != nullptr);
    if(ch == L'ỉ')
        return (links[39] != nullptr);
    if(ch == L'ĩ')
        return (links[40] != nullptr);
    if(ch == L'ị')
        return (links[41] != nullptr);
    if(ch == 'k')
        return (links[42] != nullptr);
    if(ch == 'l')
        return (links[43] != nullptr);
    if(ch == 'm')
        return (links[44] != nullptr);
    if(ch == 'n')
        return (links[45] != nullptr);
    if(ch == 'o')
        return (links[46] != nullptr);
    if(ch == L'ó')
        return (links[47] != nullptr);
    if(ch == L'ò')
        return (links[48] != nullptr);
    if(ch == L'ỏ')
        return (links[49] != nullptr);
    if(ch == L'õ')
        return (links[50] != nullptr);
    if(ch == L'ọ')
        return (links[51] != nullptr);
    if(ch == L'ô')
        return (links[52] != nullptr);
    if(ch == L'ố')
        return (links[53] != nullptr);
    if(ch == L'ồ')
        return (links[54] != nullptr);
    if(ch == L'ổ')
        return (links[55] != nullptr);
    if(ch == L'ỗ')
        return (links[56] != nullptr);
    if(ch == L'ộ')
        return (links[57] != nullptr);
    if(ch == L'ơ')
        return (links[58] != nullptr);
    if(ch == L'ớ')
        return (links[59] != nullptr);
    if(ch == L'ờ')
        return (links[60] != nullptr);
    if(ch == L'ở')
        return (links[61] != nullptr);
    if(ch == L'ỡ')
        return (links[62] != nullptr);
    if(ch == L'ợ')
        return (links[63] != nullptr);
    if(ch == 'p')
        return (links[64] != nullptr);
    if(ch == 'q')
        return (links[65] != nullptr);
    if(ch == 'r')
        return (links[66] != nullptr);
    if(ch == 's')
        return (links[67] != nullptr);
    if(ch == 't')
        return (links[68] != nullptr);
    if(ch == 'u')
        return (links[69] != nullptr);
    if(ch == L'ú')
        return (links[70] != nullptr);
    if(ch == L'ù')
        return (links[71] != nullptr);
    if(ch == L'ủ')
        return (links[72] != nullptr);
    if(ch == L'ũ')
        return (links[73] != nullptr);
    if(ch == L'ụ')
        return (links[74] != nullptr);
    if(ch == L'ư')
        return (links[75] != nullptr);
    if(ch == L'ứ')
        return (links[76] != nullptr);
    if(ch == L'ừ')
        return (links[77] != nullptr);
    if(ch == L'ử')
        return (links[78] != nullptr);
    if(ch == L'ữ')
        return (links[79] != nullptr);
    if(ch == L'ự')
        return (links[80] != nullptr);
    if(ch == 'v')
        return (links[81] != nullptr);
    if(ch == 'x')
        return (links[82] != nullptr);
    if(ch == 'y')
        return (links[83] != nullptr);
    if(ch == L'ý')
        return (links[84] != nullptr);
    if(ch == L'ỳ')
        return (links[85] != nullptr);
    if(ch == L'ỷ')
        return (links[86] != nullptr);
    if(ch == L'ỹ')
        return (links[87] != nullptr);
    if(ch == L'ỵ')
        return (links[88] != nullptr);
    return false;
}

void VieTrieNode::put(wchar_t ch, VieTrieNode *node)
{
    if(ch == 'a')
        links[0] = node;
    else if(ch == L'á')
        links[1] = node;
    else if(ch == L'à')
        links[2] = node;
    else if(ch == L'ả')
        links[3] = node;
    else if(ch == L'ã')
        links[4] = node;
    else if(ch == L'ạ')
        links[5] = node;
    else if(ch == L'â')
        links[6] = node;
    else if(ch == L'ấ')
        links[7] = node;
    else if(ch == L'ầ')
        links[8] = node;
    else if(ch == L'ẩ')
        links[9] = node;
    else if(ch == L'ẫ')
        links[10] = node;
    else if(ch == L'ậ')
        links[11] = node;
    else if(ch == L'ă')
        links[12] = node;
    else if(ch == L'ắ')
        links[13] = node;
    else if(ch == L'ằ')
        links[14] = node;
    else if(ch == L'ẳ')
        links[15] = node;
    else if(ch == L'ẵ')
        links[16] = node;
    else if(ch == L'ặ')
        links[17] = node;
    else if(ch == 'b')
        links[18] = node;
    else if(ch == 'c')
        links[19] = node;
    else if(ch == 'd')
        links[20] = node;
    else if(ch == L'đ')
        links[21] = node;
    else if(ch == 'e')
        links[22] = node;
    else if(ch == L'é')
        links[23] = node;
    else if(ch == L'è')
        links[24] = node;
    else if(ch == L'ẻ')
        links[25] = node;
    else if(ch == L'ẽ')
        links[26] = node;
    else if(ch == L'ẹ')
        links[27] = node;
    else if(ch == L'ê')
        links[28] = node;
    else if(ch == L'ế')
        links[29] = node;
    else if(ch == L'ề')
        links[30] = node;
    else if(ch == L'ể')
        links[31] = node;
    else if(ch == L'ễ')
        links[32] = node;
    else if(ch == L'ệ')
        links[33] = node;
    else if(ch == 'g')
        links[34] = node;
    else if(ch == 'h')
        links[35] = node;
    else if(ch == 'i')
        links[36] = node;
    else if(ch == L'í')
        links[37] = node; 
    else if(ch == L'ì')
        links[38] = node;
    else if(ch == L'ỉ')
        links[39] = node;
    else if(ch == L'ĩ')
        links[40] = node;
    else if(ch == L'ị')
        links[41] = node;
    else if(ch == 'k')
        links[42] = node;
    else if(ch == 'l')
        links[43] = node;
    else if(ch == 'm')
        links[44] = node;
    else if(ch == 'n')
        links[45] = node;
    else if(ch == 'o')
        links[46] = node;
    else if(ch == L'ó')
        links[47] = node;
    else if(ch == L'ò')
        links[48] = node;
    else if(ch == L'ỏ')
        links[49] = node;
    else if(ch == L'õ')
        links[50] = node;
    else if(ch == L'ọ')
        links[51] = node;
    else if(ch == L'ô')
        links[52] = node;
    else if(ch == L'ố')
        links[53] = node;
    else if(ch == L'ồ')
        links[54] = node;
    else if(ch == L'ổ')
        links[55] = node;
    else if(ch == L'ỗ')
        links[56] = node;
    else if(ch == L'ộ')
        links[57] = node;
    else if(ch == L'ơ')
        links[58] = node;
    else if(ch == L'ớ')
        links[59] = node;
    else if(ch == L'ờ')
        links[60] = node;
    else if(ch == L'ở')
        links[61] = node;
    else if(ch == L'ỡ')
        links[62] = node;
    else if(ch == L'ợ')
        links[63] = node;
    else if(ch == 'p')
        links[64] = node;
    else if(ch == 'q')
        links[65] = node;
    else if(ch == 'r')
        links[66] = node;
    else if(ch == 's')
        links[67] = node;
    else if(ch == 't')
        links[68] = node;
    else if(ch == 'u')
        links[69] = node;
    else if(ch == L'ú')
        links[70] = node;
    else if(ch == L'ù')
        links[71] = node;
    else if(ch == L'ủ')
        links[72] = node;
    else if(ch == L'ũ')
        links[73] = node;
    else if(ch == L'ụ')
        links[74] = node;
    else if(ch == L'ư')
        links[75] = node;
    else if(ch == L'ứ')
        links[76] = node;
    else if(ch == L'ừ')
        links[77] = node;
    else if(ch == L'ử')
        links[78] = node;
    else if(ch == L'ữ')
        links[79] = node;
    else if(ch == L'ự')
        links[80] = node;
    else if(ch == 'v')
        links[81] = node;
    else if(ch == 'x')
        links[82] = node;
    else if(ch == 'y')
        links[83] = node;
    else if(ch == L'ý')
        links[84] = node;
    else if(ch == L'ỳ')
        links[85] = node;
    else if(ch == L'ỷ')
        links[86] = node;
    else if(ch == L'ỹ')
        links[87] = node;
    else if(ch == L'ỵ')
        links[88] = node;
    else
        return;
}

VieTrieNode* VieTrieNode::get(wchar_t ch)
{
    if(ch == 'a')
        return links[0];
    if(ch == L'á')
        return links[1];
    if(ch == L'à')
        return links[2];
    if(ch == L'ả')
        return links[3];
    if(ch == L'ã')
        return links[4];
    if(ch == L'ạ')
        return links[5];
    if(ch == L'â')
        return links[6];
    if(ch == L'ấ')
        return links[7];
    if(ch == L'ầ')
        return links[8];
    if(ch == L'ẩ')
        return links[9];
    if(ch == L'ẫ')
        return links[10];
    if(ch == L'ậ')
        return links[11];
    if(ch == L'ă')
        return links[12];
    if(ch == L'ắ')
        return links[13];
    if(ch == L'ằ')
        return links[14];
    if(ch == L'ẳ')
        return links[15];
    if(ch == L'ẵ')
        return links[16];
    if(ch == L'ặ')
        return links[17];
    if(ch == 'b')
        return links[18];
    if(ch == 'c')
        return links[19];
    if(ch == 'd')
        return links[20];
    if(ch == L'đ')
        return links[21];
    if(ch == 'e')
        return links[22];
    if(ch == L'é')
        return links[23];
    if(ch == L'è')
        return links[24];
    if(ch == L'ẻ')
        return links[25];
    if(ch == L'ẽ')
        return links[26];
    if(ch == L'ẹ')
        return links[27];
    if(ch == L'ê')
        return links[28];
    if(ch == L'ế')
        return links[29];
    if(ch == L'ề')
        return links[30];
    if(ch == L'ể')
        return links[31];
    if(ch == L'ễ')
        return links[32];
    if(ch == L'ệ')
        return links[33];
    if(ch == 'g')
        return links[34];
    if(ch == 'h')
        return links[35];
    if(ch == 'i')
        return links[36];
    if(ch == L'í')
        return links[37]; 
    if(ch == L'ì')
        return links[38];
    if(ch == L'ỉ')
        return links[39];
    if(ch == L'ĩ')
        return links[40];
    if(ch == L'ị')
        return links[41];
    if(ch == 'k')
        return links[42];
    if(ch == 'l')
        return links[43];
    if(ch == 'm')
        return links[44];
    if(ch == 'n')
        return links[45];
    if(ch == 'o')
        return links[46];
    if(ch == L'ó')
        return links[47];
    if(ch == L'ò')
        return links[48];
    if(ch == L'ỏ')
        return links[49];
    if(ch == L'õ')
        return links[50];
    if(ch == L'ọ')
        return links[51];
    if(ch == L'ô')
        return links[52];
    if(ch == L'ố')
        return links[53];
    if(ch == L'ồ')
        return links[54];
    if(ch == L'ổ')
        return links[55];
    if(ch == L'ỗ')
        return links[56];
    if(ch == L'ộ')
        return links[57];
    if(ch == L'ơ')
        return links[58];
    if(ch == L'ớ')
        return links[59];
    if(ch == L'ờ')
        return links[60];
    if(ch == L'ở')
        return links[61];
    if(ch == L'ỡ')
        return links[62];
    if(ch == L'ợ')
        return links[63];
    if(ch == 'p')
        return links[64];
    if(ch == 'q')
        return links[65];
    if(ch == 'r')
        return links[66];
    if(ch == 's')
        return links[67];
    if(ch == 't')
        return links[68];
    if(ch == 'u')
        return links[69];
    if(ch == L'ú')
        return links[70];
    if(ch == L'ù')
        return links[71];
    if(ch == L'ủ')
        return links[72];
    if(ch == L'ũ')
        return links[73];
    if(ch == L'ụ')
        return links[74];
    if(ch == L'ư')
        return links[75];
    if(ch == L'ứ')
        return links[76];
    if(ch == L'ừ')
        return links[77];
    if(ch == L'ử')
        return links[78];
    if(ch == L'ữ')
        return links[79];
    if(ch == L'ự')
        return links[80];
    if(ch == 'v')
        return links[81];
    if(ch == 'x')
        return links[82];
    if(ch == 'y')
        return links[83];
    if(ch == L'ý')
        return links[84];
    if(ch == L'ỳ')
        return links[85];
    if(ch == L'ỷ')
        return links[86];
    if(ch == L'ỹ')
        return links[87];
    if(ch == L'ỵ')
        return links[88];
    return nullptr;
}

bool VieTrieNode::hasNoChildren()
{
    for (int i = 0; i < 89; i++)
    {
        if (links[i])
            return false;
    }
    return true;
}

