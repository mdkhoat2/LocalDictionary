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

class word {
public:
	//void render(sf::RenderWindow& window, sf::Font& font);
private:
	std::string type;
	std::string def;
};

class RandomWord {
public:
	RandomWord(sf::Font& font, sf::Font& font2, sf::RenderWindow& window);
	void handleEvent(sf::Event& event, sf::RenderWindow& window, std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector, std::vector<WordDataEngVie>& vieEngVector);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
public:
	bool isBackButtonPressed;
	//void getRandom(std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector, std::vector<WordDataEngVie>& vieEngVector);
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Font font;
	sf::Font font2;

	Button backButton;

	Button button1;
	Button button2;
	Button button3;
	Button button4;

	word word1;
	word word2;
	word word3;
	word word4;

private:
	void initBackground(sf::RenderWindow& window);
	void initBackButton();
	void initButton1();
	void initButton2();
	void initButton3();
	void initButton4();
};

#endif // !RANDOMWORD_H
