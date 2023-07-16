#ifndef NEWWORD_H
#define NEWWORD_H

#include <iostream>
#include <queue>
#include <fstream>
#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"

class NewWord {
public:
	void addNewWord(EngTrieNode*& root, std::string word, std::string wordInfo, std::queue<WordData> addedWord);
	void saveAddedWord(std::queue<WordData> addedWord);
	void loadAddedWord(EngTrieNode*& root);
public:
	NewWord();
	void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void setEndScreen(bool value);
private:
	std::queue<WordData> addedWord;
	sf::Font font;
	Textbox wordBar;
	Textbox defBar;
	Button backButton;
	Button addButton;
	bool isEndScreen;
private:
	void initFont();
	void initBackButton();
	void initAddButton();
	void initWordBar();
	void initDefBar();
};

#endif