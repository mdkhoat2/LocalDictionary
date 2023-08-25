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

void saveWords(const std::vector<WordItem>& words,std::string filePath);

//void favourite(sf::RenderWindow& window);

bool checkStringInFile(const std::string& file_path, const std::string& target_string);

void appendStringToFile(const std::string& file_path, const std::string& target_string);

void removeStringFromFile(const std::string& filePath, const std::string& stringToRemove);

class Favourite
{
public:
	Favourite(sf::RenderWindow& window);

	//void add(std::string word);

	//void drawTo(sf::RenderWindow& window);

	//void addtoFile();

	//void likeOrNot(sf::RenderWindow& window);

	void loadWordsList();

	void resavePositionDeleteButton();

	void addWord(std::string inputword, EngTrieNode* root);
	
	void removeWord(sf::RenderWindow& window);

	bool filterAndCheck(std::string  wordCheck);

	void eraseWordList();

	bool filterAndCheckinDictionary(EngTrieNode* root, std::string word);


public:

	void setDataSet(int theID);

	void handleEvent(sf::Event& event, sf::RenderWindow& window,bool&endScreen, EngTrieNode* root);

	void update(sf::RenderWindow& window);

	void render(sf::RenderWindow& window);

	void setEndScreen(bool value);


private:
	Button addButton;
	Button backButton;
	Button nextButton;
	Button prevButton;
	Button dataSetButton;
	Textbox addBar;
	sf::Clock clock;
	sf::Time elapse;
	sf::Text existed;
	sf::Text notFoundText;
	bool isExist;
	bool notFound;
	std::vector<WordItem>wordItems;
	sf::Texture  deleteButtonTexture, prevButtonTexture, nextButtonTexture, backgroundTexture;
	sf::Sprite  deleteButtonImage, prevButtonImage, nextButtonImage, backgroundImage;
	sf::Font font;
	sf::Time t1;
	std::string filePath;
	int  posY1;
	int currentPage;
	int numberPage;
	bool isEndScreen;
	int currentDataSetID;
private:
	void initExistedText();
	void initNotFoundText();
	void initBackground(sf::RenderWindow& window);
	void initAddButton(sf::Font& font);
	void initBackButton(sf::Font& font);
	void initprevButton(sf::Font& font);
	void initnextButton(sf::Font& font);
	void initAddBar(sf::Font& font);
	void initDataSetButton(sf::Font& font);
	void setCurrentDataSet();
	void changeDataSet();

};

//===========================================================================================



class FavouriteOnMainAndOptionScreen
{
public:
	FavouriteOnMainAndOptionScreen();

	void checkWordAddedOrNot(std::string word,int currentDataSetID);

	void eraseOrAdd(Textbox& searchBar, int currenDataSetID);

	void drawTo(sf::RenderWindow& window,Textbox&searchBar);

	void initFavouriteFlagImage();

	void initAddedText();

	void initRemovedText();

	bool filterAndCheck(std::string&word,std::string filePath);

	bool showFlag;
private:
	sf::Texture favouriteFlag1Texture, favouriteFlag2Texture;
	sf::Sprite favouriteFlag1Image, favouriteFlag2Image;
	sf::Time t1;
	sf::Clock clock;
	bool CoutText;
	bool isAdded;
	sf::Text Removed;
	sf::Text Added;
	sf::Font font;
};
#endif