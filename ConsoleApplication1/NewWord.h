#ifndef NEWWORD_H
#define NEWWORD_H

#include <queue>
#include <fstream>
#include "Trie.h"
#include "WordData.h"

class NewWord
{
public:
	
	void addNewWord(EngTrieNode*& root, std::string word, std::string wordInfo, std::queue<WordData> addedWord);
	void saveAddedWord(std::queue<WordData> addedWord);
	void loadAddedWord(EngTrieNode*& root);

private:
	std::queue<WordData> addedWord;
};


#endif