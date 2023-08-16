#pragma once
#ifndef	RANDOMDEF_H
#define RANDOMDEF_H

#include <fstream>
#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"
#include "DisplayDefinition.h"
#include "Explore.h"


class RandomDef {
public:
	RandomDef(sf::Font& first, sf::Font& second, sf::RenderWindow& window);
	void handleEvent(sf::Event& event, sf::RenderWindow& window, int& id, std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector, std::vector<WordDataEngVie>& vieEngVector);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	bool isBackButtonPressed;
private:
	void displayDefinition(sf::RenderWindow& window);
	void displayKeyword(sf::RenderWindow& window, std::string& keyword);
	void getRandom(std::vector<WordDataEngVie>& root);
	void wrapText(sf::Text& theText);
private:
	sf::RectangleShape theBox;
	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Texture rightTexture;
	sf::Sprite right;

	sf::Texture wrongTexture;
	sf::Sprite wrong;

	sf::Font font;
	sf::Font font2;

	Button backButton;
	Button randomButton;

	Button button1;
	Button button2;
	Button button3;
	Button button4;

	Button submitButton;

	std::string word1;
	std::string word2;
	std::string word3;
	std::string word4;

	std::string type;
	std::string definition;

	int currentDataSetID;
	int currentChoice;
	int answer;
	bool isSubmitted;
	bool isCorrect;
private:
	void initBackground(sf::RenderWindow& window);
	void initSprite();
	void initBackButton();
	void initRandomButton();
	void initButton1();
	void initButton2();
	void initButton3();
	void initButton4();
	void initSubmitButton();
	void initWord();
};

#endif // !RANDOMDEF_H
