#ifndef NEWWORD_H
#define NEWWORD_H

#include <iostream>
#include <queue>
#include <fstream>
#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"
#include "DisplayDefinition.h"

class NewWord {
public:
	void saveAddedWord();
	// EE
	bool addEEFromTextFile(EngTrieNode*& root, std::string& inputWord, std::string& wordInfo,
		std::vector<WordDataEngVie>& engEngVector);
	void addNewEEWord(EngTrieNode*& root, std::string& word, std::string& wordInfo,
		std::vector<WordDataEngVie>& engEngVector);
	void saveAddedEEWord();
	void loadAddedEEWord(EngTrieNode*& root, std::vector<WordDataEngVie>& engEngVector);
	// EV
	bool addEVFromTextFile(EngTrieNode*& root, std::string& inputWord, std::string& wordInfo,
		std::vector<WordDataEngVie>& engVieVector);
	void addNewEVWord(EngTrieNode*& root, std::string& word, std::string& wordInfo,
		std::vector<WordDataEngVie>& engVieVector);
	void saveAddedEVWord();
	void loadAddedEVWord(EngTrieNode*& root, std::vector<WordDataEngVie>& engVieVector);
public:
	NewWord(sf::Font& font,sf::Font& font2 , sf::RenderWindow& window);
	void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen, EngTrieNode*& engEngRoot,
		std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector,
		std::vector<WordDataEngVie>& vieEngVector);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void setEndScreen(bool value);
public:
	void addInEngEngDict(std::string& inputWord, EngTrieNode*& engEngRoot, std::vector<WordDataEngVie>& engEngVector);
	void addInEngVieDict(std::string& inputWord, EngTrieNode*& engEngRoot, std::vector<WordDataEngVie>& engVieVector);
	void addInVieEngDict(std::string& inputWord, EngTrieNode*& engEngRoot, std::vector<WordDataEngVie>& vieEngVector);
private:
	//std::queue<WordDataEngVie*> addedWord;
	std::queue<std::pair<std::string, std::string>> addedEEWord;
	std::queue<std::pair<std::string, std::string>> addedEVWord;

	sf::Texture addScreenTex, dataSetTex;
	sf::Sprite addScreen, dataSet;

	Textbox wordBar;

	DisplayBox noteBox;
	DisplayBox displayBox;

	sf::Text dataSetText;

	Button backButton;
	Button addButton;
	Button dataSetButton;

	int currentDataSetID;
	/*
		0: EngEng
		1: EngVie
		2: VieEng
		3: Emoji
	*/

	bool isEndScreen;
private:
	void initBackground(sf::RenderWindow& window);
	void initWordBar(sf::Font& font);
	void initBackButton(sf::Font& font);
	void initAddButton(sf::Font& font);
	void initDataSetText(sf::Font& font);
	void initDataSetButton(sf::Font& font);
	void initDisplayBox(sf::Font& font);
	void initNoteBox(sf::Font& font);
	void changeDataSet();
};

#endif