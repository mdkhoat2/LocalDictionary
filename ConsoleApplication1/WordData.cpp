#include <iostream>
#include "WordData.h"

WordData::WordData() : word()
{
    for(int i = 0; i < 4; ++i)
        defListHead[i] = nullptr;
}

WordData::WordData(std::string wordIn) : word(wordIn)
{
    for(int i = 0; i < 4; ++i)
        defListHead[i] = nullptr;
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

bool isValidCharacter(char ch)
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
    return false;
}

bool isValidWordType(std::string wordType)
{
    if(wordType == "n" || wordType == "v" || wordType == "adj" || wordType == "adv")
        return true;
    return false;
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
