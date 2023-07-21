#ifndef FAVOUTITE_H
#define FAVOURITE_H

#include <iostream>
#include <queue>
#include<vector>
#include <fstream>
#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"
#include "DisplayDefinition.h"
struct WordItem {
	std::string word;
	Button deleteButton{ "", {40,40}, 20, sf::Color::Transparent, sf::Color::Transparent };
};
struct WordFavouriteButton
{
	std::string word;
	sf::RectangleShape favouriteButton;
	bool liked = false;
};
void saveWords(const std::vector<WordItem>& words);

//void favourite(sf::RenderWindow& window);

bool checkStringInFile(const std::string& file_path, const std::string& target_string);

void appendStringToFile(const std::string& file_path, const std::string& target_string);

class Favourite
{
public:
	Favourite(sf::RenderWindow& window);

	void add(std::string word);

	void drawTo(sf::RenderWindow& window);

	void addtoFile();

	void likeOrNot(sf::RenderWindow& window);

	void loadWordsList();

	void resavePositionDeleteButton();

	void addWord(std::string inputword);
	
	void removeWord(sf::RenderWindow& window);

public:


	void handleEvent(sf::Event& event, sf::RenderWindow& window,bool&endScreen);

	void update(sf::RenderWindow& window);

	void render(sf::RenderWindow& window);

	void setEndScreen(bool value);

private:
	Button addButton;
	Button backButton;
	Button nextButton;
	Button prevButton;
	Textbox addBar;
	sf::Clock clock;
	sf::Time elapse;
	sf::Text existed;
	bool isExist;
	std::vector<WordFavouriteButton>favourite;
	std::vector<WordItem>wordItems;
	sf::Texture favouriteTexture1, favouriteTexture2, deleteButtonTexture, prevButtonTexture, nextButtonTexture, backgroundTexture;
	sf::Sprite favouriteImage1, favouriteImage2, deleteButtonImage, prevButtonImage, nextButtonImage, backgroundImage;
	sf::Font font;
	std::string filePath;
	sf::Time t1;
	int  posY, posY1;
	int currentPage;
	int numberPage;
	bool isEndScreen;
private:
	void initExistedText();
	void initBackground(sf::RenderWindow& window);
	void initAddButton(sf::Font& font);
	void initBackButton(sf::Font& font);
	void initprevButton(sf::Font& font);
	void initnextButton(sf::Font& font);
	void initAddBar(sf::Font& font);


};
#endif