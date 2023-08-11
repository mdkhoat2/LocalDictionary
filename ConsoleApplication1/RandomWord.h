#pragma once
#ifndef	RANDOMWORD_H
#define RANDOMWORD_H

#include <fstream>
#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"
#include "DisplayDefinition.h"
#include "Explore.h"

class RandomWord {
public:
	RandomWord(sf::Font& font, sf::Font& font2, sf::RenderWindow& window);
	void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen, EngTrieNode*& engEngRoot,
				std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector,
				std::vector<WordDataEngVie>& vieEngVector);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void setEndScreen(bool value);
private:
	std::string word;
	std::string wordType;
	std::string wordDef;


};

#endif // !RANDOMWORD_H
