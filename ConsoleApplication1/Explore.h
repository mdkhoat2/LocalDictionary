#ifndef EXPLORE_H
#define EXPLORE_H

#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"
#include "DisplayDefinition.h"

class Explore
{
public:
	Explore(sf::Font& font, sf::Font& font2, sf::Window& window);
public:
	void render(sf::Window& window);
	void changeCurrentDataSet(int _number);
	void displayDefinition();
	void searchInEngEngDict(std::string& inputWord, std::vector<WordDataEngVie>& engEngVector, EngTrieNode*& engEngRoot);
	void searchInEngVieDict(std::string& inputWord);
	void searchInVieEngDict(std::string& inputWord);
	void searchInEmojiDict(std::string& inputWord);
private:
	sf::Texture backgroundTex;
	sf::Sprite background;
	sf::Font font; //rounded
	sf::Font font2; //regular

	int currentDataSet;
	DisplayBox displayBox;

	std::string currentWord;
private:
	void initCurrentDataSet();
	void initBackground(sf::Window& window);
	void initFont();
	void initDisplayBox();
};

#endif // !EXPLORE_H
