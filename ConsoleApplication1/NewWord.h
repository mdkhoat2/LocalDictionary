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
	void addNewWord(EngTrieNode*& root, std::string& word, std::string& wordInfo);
	void addFromTextFile(EngTrieNode*& root, std::string& inputWord, std::string& wordInfo);
	void saveAddedWord();
	void loadAddedWord(EngTrieNode*& root);
public:
	NewWord(sf::Font& font, sf::RenderWindow& window);
	void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen, EngTrieNode*& engEngRoot);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void setEndScreen(bool value);
private:
	std::queue<WordData> addedWord;
	//sf::RenderWindow addWindow;
	//sf::Font addFont;
	sf::Texture addScreenTex;
	sf::Sprite addScreen;
	Textbox wordBar;
	//Textbox defBar;
	DisplayBox noteBox;
	DisplayBox displayBox;
	Button backButton;
	Button addButton;
	bool isEndScreen;
private:
	void initBackground(sf::RenderWindow& window);
	//void initFont(sf::Font font);
	void initWordBar(sf::Font& font);
	//void initDefBar(sf::Font& font);
	void initBackButton(sf::Font& font);
	void initAddButton(sf::Font& font);
	void initDisplayBox(sf::Font& font);
	void initNoteBox(sf::Font& font);
};

#endif