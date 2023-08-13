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
	void saveRemovedWord();
	void resetRemove(EngTrieNode*& root);
	// EE 
	void removeEEWord(EngTrieNode*& root, std::string word);
	void saveRemovedEEWord();
	void loadRemovedEEWord(EngTrieNode*& root);

	// EV
	void removeEVWord(EngTrieNode*& root, std::string word);
	void saveRemovedEVWord();
	void loadRemovedEVWord(EngTrieNode*& root);

	// VE
	void removeVEWord(EngTrieNode*& root, std::string word);
	void saveRemovedVEWord();
	void loadRemovedVEWord(EngTrieNode*& root);
public:
	RemoveWord(sf::Font& font1, sf::Font& font2, sf::RenderWindow& window);
	void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen, EngTrieNode*& engEngRoot,
		std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector,
		std::vector<WordDataEngVie>& vieEngVector);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void setEndScreen(bool value);
private:
	std::string wordTmp;
	
	std::queue<std::string> removedEEWord;
	std::queue<std::string> removedEVWord;
	std::queue<std::string> removedVEWord;

	sf::Texture removeScreenTex, dataSetTex, cancelTex, confirmTex;
	sf::Sprite removeScreen, dataSet, cancel, confirm;

	Textbox wordBar;

	DisplayBox noteBox;
	DisplayBox displayBox;

	sf::Text dataSetText;

	Button backButton;
	Button removeButton;
	Button dataSetButton;
	Button cancelButton;
	Button confirmButton;

	int currentDataSetID;
	/*
		0: EngEng
		1: EngVie
		2: VieEng
		3: Emoji
	*/
	bool isDeleting;
	bool isEndScreen;
private:
	void initBackground(sf::RenderWindow& window);
	void initWordBar(sf::Font& font);
	void initBackButton(sf::Font& font);
	void initCancelButton(sf::Font& font);
	void initConfirmButton(sf::Font& font);
	void initRemoveButton(sf::Font& font);
	void initDataSetText(sf::Font& font);
	void initDataSetButton(sf::Font& font);
	void initDisplayBox(sf::Font& font);
	void initNoteBox(sf::Font& font);
	void changeDataSet();
};

#endif