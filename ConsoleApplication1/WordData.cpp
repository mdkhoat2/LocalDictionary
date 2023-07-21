#include <iostream>
#include <fstream>
#include "WordData.h"

WordData::WordData() : word()
{
    for(int i = 0; i < 4; ++i)
        defListHead[i] = nullptr;
}

WordData::~WordData()
{
    for(int i = 0; i < 4; ++i)
    {
        deleteAllList(defListHead[i]);
    }
}

void WordData::consolePrint()
{
    std::cout << "WORD: " << word << std::endl;
    for(int i = 0; i < 4; ++i)
    {
        if(defListHead[i] == nullptr)
            continue;
        if(i == 0)
            std::cout << "Word type: Noun" << std::endl; 
        else if(i == 1)
            std::cout << "Word type: Verb" << std::endl; 
        else if(i == 2)
            std::cout << "Word type: Adjective" << std::endl; 
        else
            std::cout << "Word type: Adverb" << std::endl; 
        WordDefNode* cur = defListHead[i];
        int count = 1;
        while(cur != nullptr)
        {
            std::cout << count << ". " << cur->wordDef << std::endl;
            ++count;
            cur = cur->next;
        }
    }
}

void extractWordData(WordData &theWordData, std::string word, std::string wordInfo)
{
    theWordData.word = word;
    std::stringstream stream(wordInfo);
    std::string line;
    int index;
    while(std::getline(stream, line, '\n'))
    {
        // the line contains word type
        if(isValidWordType(line))
        {
            if(line == "n")
                index = 0;
            else if(line == "v")
                index = 1;
            else if(line == "adj")
                index = 2;
            else
                index = 3;
        }
        // the line that contains the definition
        else
        {
            int i = 0;
            while(line[i] != ' ')
                ++i;
            insertAtEnd(theWordData.defListHead[index], line.substr(i+1));
        }
    }
}

void extractEngVieData(WordDataEngVie &engVieData, std::string &word, std::string &wordInfo)
{
    engVieData.word = word;
    std::stringstream stream(wordInfo);
    std::string line;
    EngVieDef theDef;
    while(std::getline(stream, line))
    // Each of "theDef" will contain a word type, a word definition and example(s) (if exist)
    // We store definition and example in a pair to display it close to each other
    {
        // this is a word type
        if(line[0] == '*') 
        {
            if(!theDef.empty()) // need to push the previous word data
            {
                engVieData.defList.push_back(theDef);
                theDef.clear();
            }
            int i = 1;
            // Skip spaces
            while(line[i] == ' ' && i < line.length())
                ++i;
            while(line[i] != '/' && i < line.length())
            {
                theDef.wordType += line[i];
                ++i;
            }
        }
        // this is a phrase containing the word
        // We will display it like the word type
        if(line[0] == '!')
        {
            // Push the previous eng vie def
            if(!theDef.empty())
            {
                engVieData.defList.push_back(theDef);
                theDef.clear();
            }
            theDef.wordType = "Phrase: " + line.substr(1);
        }
        // this is the definition of the word/phrase
        else if(line[0] == '-')
        {
            if(!theDef.defAndExample.first.empty())
            {
                engVieData.defList.push_back(theDef);
                theDef.defAndExample.first.clear();
                theDef.defAndExample.second.clear();
            }
            theDef.defAndExample.first = line.substr(0);
        }
        // this is the example
        else if(line[0] == '=')
        {
            if(!theDef.defAndExample.second.empty())
                theDef.defAndExample.second += "\n";
            int i = 1;
            while(line[i] != '+' && i < line.length())
            {
                theDef.defAndExample.second += line[i];
                ++i;
            }
            theDef.defAndExample.second += " = ";
            ++i;
            while(line[i] == ' ' && i < line.length())
                ++i;
            theDef.defAndExample.second += line.substr(i);
        }
        // This is the explanation to a technical word
        // We display it like word example
        else if(line[0] == '+')
        {
            if(!theDef.defAndExample.second.empty())
                theDef.defAndExample.second += "\n";
            theDef.defAndExample.second += line.substr(1);
        }
        // This is the sign we add to delete old word type
        // Because a word appears at many places in the dictionary
        else if(line[0] == '@')
        {
            if(!theDef.empty())
            {
                engVieData.defList.push_back(theDef);
                theDef.clear();
            }
        }
        else
            continue;
    }
    // Push the last definition
    if(!theDef.empty())
        engVieData.defList.push_back(theDef);
}

void extractVieEngData(WordDataEngVie &vieEngData, std::string &word, std::string &wordInfo)
{
    vieEngData.word = word;
    std::stringstream stream(wordInfo);
    std::string line;
    EngVieDef theDef;
    while(std::getline(stream, line))
    // Each of "theDef" will contain a word type, a word definition and example(s) (if exist)
    // We store definition and example in a pair to display it close to each other
    {
        // this is a word type
        if(line[0] == '*') 
        {
            if(!theDef.empty()) // need to push the previous word data
            {
                vieEngData.defList.push_back(theDef);
                theDef.clear();
            }
            int i = 1;
            // Skip spaces
            while(line[i] == ' ' && i < line.length())
                ++i;
            theDef.wordType = line.substr(i);
        }
        // this is the definition of the word
        else if(line[0] == '-')
        {
            if(!theDef.defAndExample.first.empty())
            {
                vieEngData.defList.push_back(theDef);
                theDef.defAndExample.first.clear();
                theDef.defAndExample.second.clear();
            }
            theDef.defAndExample.first = line;
        }
        // this is the example
        else if(line[0] == '=')
        {
            if(!theDef.defAndExample.second.empty())
                theDef.defAndExample.second += "\n";
            int i = 1;
            while(line[i] != '+' && i < line.length())
            {
                theDef.defAndExample.second += line[i];
                ++i;
            }
            if(i < line.length()-1)
            {
                theDef.defAndExample.second += " = ";
                theDef.defAndExample.second += line.substr(i+1);
            }
        }
        // This is the sign we add to delete old word type
        // Because a word appears at many places in the dictionary
        else if(line[0] == '@')
        {
            if(!theDef.empty())
            {
                vieEngData.defList.push_back(theDef);
                theDef.clear();
            }
        }
        else
            continue;
    }
    // Push the last definition
    if(!theDef.empty())
        vieEngData.defList.push_back(theDef);
}

void insertAtEnd(WordDefNode *&head, std::string wordDef)
{
    if(head == nullptr)
    {
        head = new WordDefNode();
        head->wordDef = wordDef;
        return;
    }
    WordDefNode* cur = head;
    while(cur->next != nullptr)
        cur = cur->next;
    cur->next = new WordDefNode();
    cur->next->wordDef = wordDef;
}

void deleteAllList(WordDefNode *&head)
{
    WordDefNode* temp;
    while(head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
}

int countNumOfDefs(WordData &theWordData)
{
    int count = 0;
    for(int i = 0; i < 4; ++i)
    {
        if(theWordData.defListHead[i] == nullptr)
            continue;
        WordDefNode* cur = theWordData.defListHead[i];
        while(cur != nullptr)
        {
            ++count;
            cur = cur->next;
        }
    }
    return count;
}

bool isValidEngChar(wchar_t ch)
{
    if(ch >= 'a' && ch <= 'z')
        return true;
    if(ch >= 'A' && ch <= 'Z')
        return true;
    if(ch >= '0' && ch <= '9')
        return true;
    if(ch == 39) // single quote
        return true;
    if(ch == 46) // dot
        return true;
    if(ch == 45) // hyphen
        return true;
    if(ch == 32) // space
        return true;
    if(ch == 47) // forward slash
        return true;
    return false;
}

bool isValidWordType(std::string wordType)
{
    if(wordType == "n" || wordType == "v" || wordType == "adj" || wordType == "adv")
        return true;
    return false;
}

bool isValidWord(std::string word)
{
    if(word.empty())
        return false;
    for(int i = 0; i < word.length(); ++i)
    {
        if(!(word[i] >= 0 && word[i] < 128))
            return false;
    }
    return true;
}

bool isNumber(std::string numStr)
{
    for(int i = 0; i < numStr.length(); ++i)
    {
        if(!isdigit(numStr[i]))
            return false;
    }
    return true;
}

void convertToNormalChar(wchar_t &ch)
{
    if(ch == L'á' || ch == L'à' || ch == L'ả' || ch == L'ã' || ch == L'ạ' || ch == L'â'
    || ch == L'ấ' || ch == L'ầ' || ch == L'ẩ' || ch == L'ẫ' || ch == L'ậ' || ch == L'ă'
    || ch == L'ắ' || ch == L'ằ' || ch == L'ẳ' || ch == L'ẵ' || ch == L'ặ')
    {
        ch = 'a';
        return;
    }

    if(ch = L'đ')
    {
        ch = 'd';
        return;
    }

    if(ch == L'é' || ch == L'è' || ch == L'ẻ' || ch == L'ẽ' || ch == L'ẹ' || ch == L'ê'
    || ch == L'ế' || ch == L'ề' || ch == L'ể' || ch == L'ễ' || ch == L'ệ')
    {
        ch = 'e';
        return;
    }

    if(ch == L'í' || ch == L'ì' || ch == L'ỉ' || ch == L'ĩ' || ch == L'ị')
    {
        ch = 'i';
        return;
    }
    
    if(ch == L'ó' || ch == L'ò' || ch == L'ỏ' || ch == L'õ' || ch == L'ọ' || ch == L'ô'
    || ch == L'ố' || ch == L'ồ' || ch == L'ổ' || ch == L'ỗ' || ch == L'ộ' || ch == L'ơ'
    || ch == L'ớ' || ch == L'ờ' || ch == L'ở' || ch == L'ỡ' || ch == L'ợ')
    {
        ch = 'o';
        return;
    }   

    if(ch == L'ú' || ch == L'ù' || ch == L'ủ' || ch == L'ũ' || ch == L'ụ' || ch == L'ư'
    || ch == L'ứ' || ch == L'ừ' || ch == L'ử' || ch == L'ữ' || ch == L'ự')
    {
        ch = 'u';
        return;
    }
    
    if(ch == L'ý' || ch == L'ỳ' || ch == L'ỷ' || ch == L'ỹ' || ch == L'ỵ')
    {
        ch = 'y';
        return;
    }
}

void convertToNormalLine(std::wstring &line)
{
    for(int i = 0; i < line.length(); ++i)
    {
        convertToNormalChar(line[i]);
    }
}

WordDataEngVie::WordDataEngVie() : word(), defList()
{
}

void WordDataEngVie::consolePrint()
{
    std::cout << "Word: " << word << std::endl;
    for(int i = 0; i < defList.size(); ++i)
    {
        if(!defList[i].wordType.empty())
            std::cout << "Word type/Phrase: " << defList[i].wordType << std::endl;
        std::cout << defList[i].defAndExample.first << std::endl;
        if(!defList[i].defAndExample.second.empty())
        {
            std::cout << "Example:" << std::endl;
            std::cout << defList[i].defAndExample.second << std::endl;
        }
        std::cout << std::endl;
    }
}

EngVieDef::EngVieDef() : wordType(), defAndExample()
{
}

void EngVieDef::clear()
{
    if(!wordType.empty())
        wordType.clear();
    if(!defAndExample.first.empty())
        defAndExample.first.clear();
    if(!defAndExample.second.empty())
        defAndExample.second.clear();
}

bool EngVieDef::empty()
{
    return (wordType.empty() && defAndExample.first.empty() && defAndExample.second.empty());
}
