#ifndef PROPOSEWORD_H
#define PROPOSEWORD_H

#include <iostream>
#include <queue>
#include <fstream>
#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"
#include "DisplayDefinition.h"
void findWordsWithPrefix(EngTrieNode* prefixRoot, const std::string& prefix, std::vector<std::string>&proposeWordList,int theID);

class ProposeWord
{
public:
	ProposeWord();
	bool setIsTyping();
	bool getMousePosition(sf::RenderWindow&window);
	void LoadWordList();
    EngTrieNode* search(EngTrieNode* root, std::string word);
	void eraseWordList();
	void initScrollBar();
	void setDataSetID(int theID);
	bool isTyping;
	void initWordList(std::string word, EngTrieNode* root);
	bool checkPrefix(std::string word, EngTrieNode* root);
public:
	void drawTo(sf::RenderWindow& window);

	void handleEvent(sf::Event& event, sf::RenderWindow& window);
private:
	EngTrieNode* prefixRoot;
	std::vector<std::string>proposeWordList;
	sf::Font font;
	sf::Texture scrollbar1Texture, scrollbar2Texture;
	sf::Sprite scrollbar1Image, scrollbar2Image;
	std::string prevPrefix;
	int datasetID;
	int firstVisibleIndex;
	int viewableItems ;
};



#endif