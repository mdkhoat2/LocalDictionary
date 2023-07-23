#ifndef REMOVEWORD_H
#define REMOVEWORD_H

#include <iostream>
#include <queue>
#include <fstream>
#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"
#include "DisplayDefinition.h"

class RemoveWord {
public:
	void removeWord(EngTrieNode*& root, std::string word);
	void saveRemovedWord();
	void loadRemovedWord(EngTrieNode*& root);
public:
	RemoveWord(sf::Font& font, sf::RenderWindow& window);
	void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen, EngTrieNode*& engEngRoot);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void setEndScreen(bool value);
public:
	void removeInEngEngDict(std::string& inputWord, EngTrieNode*& engEngRoot);
	void removeInEngVieDict(std::string& inputWord, EngTrieNode*& engEngRoot);
	void removeInVieEngDict(std::string& inputWord, EngTrieNode*& engEngRoot);
private:
	std::queue<std::string> removedWord;

	sf::Texture removeScreenTex, dataSetTex;
	sf::Sprite removeScreen, dataSet;

	Textbox wordBar;

	DisplayBox noteBox;
	DisplayBox displayBox;

	sf::Text dataSetText;

	Button backButton;
	Button removeButton;
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
	void initRemoveButton(sf::Font& font);
	void initDataSetText(sf::Font& font);
	void initDataSetButton(sf::Font& font);
	void initDisplayBox(sf::Font& font);
	void initNoteBox(sf::Font& font);
	void changeDataSet();
};

#endif