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
    std::string line, definition, example;
    WordDefNode* theNode;
    int index;
    while(std::getline(stream, line, '\n'))
    {
        // the line contains word type
        if(isValidWordType(line))
        {
            if(!definition.empty())
            {
                theNode = new WordDefNode();
                theNode->wordDef = definition;
                theNode->wordExample = example;
                insertAtEnd(theWordData.defListHead[index], theNode);
                definition.clear();
                example.clear();
            }
            if(line == "n")
                index = 0;
            else if(line == "v")
                index = 1;
            else if(line == "adj")
                index = 2;
            else
                index = 3;
        }
        // the line contains example, synonym or antonym
        else if(line[0] == ';' || line[0] == '[')
        {
            if(example.empty())
            {
                // examples exist
                if(line[0] == ';' && line.length() >= 2)
                    example = line.substr(1);
                else
                    example = line;
            }
            else
                example += "\n" + line;
        }
        // the line that contains the definition
        else
        {
            if(definition.empty())
            {
                definition = line;
            }
            // insert previous definition along with examples, synonyms, antonyms
            else
            {
                theNode = new WordDefNode();
                theNode->wordDef = definition;
                theNode->wordExample = example;
                insertAtEnd(theWordData.defListHead[index], theNode);
                definition = line;
                example.clear();
            }
        }
    }
    if(!definition.empty())
    {
        theNode = new WordDefNode();
        theNode->wordDef = definition;
        theNode->wordExample = example;
        insertAtEnd(theWordData.defListHead[index], theNode);
        definition = line;
        example.clear();
    }   
}

void extractEngEngData(WordDataEngVie &engEngData, std::string &word, std::string &wordInfo)
{
    // Make sure that the edit definition file or the new word file has the valid format
    // so that it can extract the word data
    engEngData.word = word;
    std::stringstream stream(wordInfo);
    std::string line;
    EngVieDef theDef;
    while(std::getline(stream, line, '\n'))
    {
        // this is the word type
        if(line[0] == '*')
        {
            // push the previous definition
            if(!theDef.empty())
            {
                engEngData.defList.push_back(theDef);
                theDef.clear();
            }
            if(line.length() >= 2)
            {
                std::string wordType = line.substr(1);
                if(wordType == "n")
                    theDef.wordType = "noun";
                else if(wordType == "v")
                    theDef.wordType = "verb";
                else if(wordType == "adj")
                    theDef.wordType = "adjective";
                else if(wordType == "adv")
                    theDef.wordType = "adverb";
                else
                    theDef.wordType = line;
            }
        }
        // this is the definition (assume that has only 1 line or has been modified to have 1 line)
        else if(line[0] == '-')
        {
            // push the previous definition
            if(!theDef.defAndExample.first.empty())
            {
                engEngData.defList.push_back(theDef);
                theDef.defAndExample.first.clear();
                theDef.defAndExample.second.clear();
            }
            theDef.defAndExample.first = line;
        }
        // this is the example (careful: example can have multiple lines)
        // so we add the sign "=" before each line of the example in file
        else if(line[0] == '=')
        {
            if(theDef.defAndExample.second.empty())
            {
                if(line.length() >= 2)
                    theDef.defAndExample.second = line.substr(1);
            }
            else
            {
                if(line.length() >= 2)
                    theDef.defAndExample.second += "\n" + line.substr(1);
            }
        }
        else
        {
            std::cout << "What is this line?" << line << std::endl;
            continue;
        }
    }
    // Push the last definition
    if(!theDef.empty())
        engEngData.defList.push_back(theDef);
}

std::string recoverEngEngWordInfo(WordDataEngVie& theWordData)
{
    std::string wordInfo;
    std::string wordType, wordDef, wordExample;
    std::string temp, line;
    int defNum = theWordData.defList.size();
    for(int i = 0; i < defNum; ++i)
    {
        temp = theWordData.defList[i].wordType;
        wordDef = theWordData.defList[i].defAndExample.first;
        wordExample = theWordData.defList[i].defAndExample.second;
        if(wordType != temp)
        {
            wordType = temp;
            if(i == 0)
                wordInfo = "*" + wordType;
            else
                wordInfo += "\n*" + wordType;
        }
        wordInfo += "\n" + wordDef;
        // Note that wordExample can have multiple lines
        std::stringstream stream(wordExample);
        while(getline(stream, line))
            wordInfo += "\n=" + line;
    }
    return wordInfo;
}

void extractEngVieData(WordDataEngVie &engVieData, std::string &word, std::string &wordInfo)
{
    engVieData.word = word;
    std::stringstream stream(wordInfo);
    std::string line;
    EngVieDef theDef;
    while(std::getline(stream, line, '\n'))
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
            if(line.length() >= 2)
            {
                theDef.wordType = line.substr(1);
            }
        }
        // this is a phrase containing the word
        // We will display it like the word type
        else if(line[0] == '!')
        {
            // Push the previous eng vie def
            if(!theDef.empty())
            {
                engVieData.defList.push_back(theDef);
                theDef.clear();
            }
            if(line.length() >= 2)
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
            theDef.defAndExample.first = line;
        }
        // this is the example
        else if(line[0] == '=')
        {
            if(!theDef.defAndExample.second.empty())
                theDef.defAndExample.second += "\n";
            int i = 1;
            while(i < line.length())
            {
                if(line[i] == '+')
                    break;
                else
                {
                    theDef.defAndExample.second += line[i];
                    ++i;
                }
            }
            if(i < line.length()-1)
            {
                if(line[i] == '+')
                    theDef.defAndExample.second += " = " + line.substr(i+1);
            }
        }
        // This is the explanation to a technical word
        // We display it like word example
        else if(line[0] == '+')
        {
            if(!theDef.defAndExample.second.empty())
                theDef.defAndExample.second += "\n";
            if(line.length() >= 2)
                theDef.defAndExample.second += line.substr(1);
        }
        // Because a word appears at many places in the dictionary
        // So we add this sign to add other meanings of the word
        else if(line[0] == '@')
        {
            if(!theDef.empty())
            {
                engVieData.defList.push_back(theDef);
                theDef.clear();
            }
        }
        else
        {
            std::cout << "What is this line?" << line << std::endl;
            continue;
        }   
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
    while(std::getline(stream, line, '\n'))
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
            if(line.length() >= 2)
            {
                theDef.wordType = line.substr(1);
            }
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
            while(i < line.length())
            {
                if(line[i] == '+')
                    break;
                else
                {
                    theDef.defAndExample.second += line[i];
                    ++i;
                }
            }
            if(i < line.length()-1 && line[i] == '+')
            {
                theDef.defAndExample.second += " = " + line.substr(i+1);
            }
        }
        // Because a word appears at many places in the dictionary
        // So we add this sign to add other meanings of the word
        else if(line[0] == '@')
        {
            if(!theDef.empty())
            {
                vieEngData.defList.push_back(theDef);
                theDef.clear();
            }
        }
        else
        {
            std::cout << "What is this line?" << line << std::endl;
            continue;
        }   
    }
    // Push the last definition
    if(!theDef.empty())
        vieEngData.defList.push_back(theDef);
}

void separateEngEngExample(std::string &wordInfo)
{
    std::stringstream stream(wordInfo);
    std::string newWordInfo;
    std::string line;
    while(std::getline(stream, line, '\n'))
    {
        if(isValidWordType(line))
        {
            if(newWordInfo.empty())
                newWordInfo = line;
            else
                newWordInfo += "\n" + line;
        }
        else
        {
            if(!newWordInfo.empty())
                newWordInfo += "\n";
            int i = 0;
            bool flag = false;
            // we don't separate each example
            while(i < line.length())
            {
                if(line[i] == ';' && flag == false)
                {
                    if(i+2 < line.length())
                    {
                        // If we meet ; " then there will be examples
                        if(line[i+1] == ' ' && line[i+2] == 34)
                        {
                            newWordInfo += "\n";
                            flag = true;
                        }
                    }
                }
                if(line[i] == '[')
                    newWordInfo += "\n";
                newWordInfo += line[i];
                ++i;
            }
        }
    }
    wordInfo = newWordInfo;
}

std::string formatEngEngWordInfo(std::string &wordInfo)
{
    std::string newWordInfo;
    std::stringstream stream(wordInfo);
    std::string line, definition, example;
    while(std::getline(stream, line, '\n'))
    {
        // the line contains word type
        if(isValidWordType(line))
        {
            if(newWordInfo.empty())
                newWordInfo = "*" + line;
            else
                newWordInfo += "\n*" + line; 
        }
        // the line contains example
        else if(line[0] == ';')
        {
            if(line.length() >= 2)
                newWordInfo += "\n=" + line.substr(1);
        }
        // the line contains synonyms or antonyms
        else if(line[0] == '[')
        {
            newWordInfo += "\n=" + line;
        }
        // the line that contains the definition
        else
        {
            newWordInfo += "\n-" + line;
        }
    }
    return newWordInfo;
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

void insertAtEnd(WordDefNode *&head, WordDefNode *theNode)
{
    if(head == nullptr)
    {
        head = theNode;
        return;
    }
    WordDefNode* cur = head;
    while(cur->next != nullptr)
        cur = cur->next;
    cur->next = theNode;
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

void removeEndLineInString(std::string &str)
{
    std::string ans;
    for(int i = 0; i < str.length(); ++i)
    {
        if(str[i] == '\n')
            continue;
        else
            ans += str[i];
    }
    str = ans;
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
