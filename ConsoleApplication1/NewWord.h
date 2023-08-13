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
#include "EditBox.h"

class NewWord {
public:
	void saveAddedWord();
	void resetAdd(EngTrieNode* root);
	// EE
	bool addEEFromTextFile(EngTrieNode*& root, std::string& inputWord, std::string& wordInfo,
		std::vector<WordDataEngVie>& engEngVector);
	void addNewEEWord(EngTrieNode*& root, std::string& word, std::string& wordInfo,
		std::vector<WordDataEngVie>& engEngVector);
	void saveAddedEEWord();
	void loadAddedEEWord(EngTrieNode*& root, std::vector<WordDataEngVie>& engEngVector);

	// EV
	bool addEVFromTextFile(EngTrieNode*& root, std::string& inputWord, std::string& wordInfo,
		std::vector<WordDataEngVie>& engVieVector);
	void addNewEVWord(EngTrieNode*& root, std::string& word, std::string& wordInfo,
		std::vector<WordDataEngVie>& engVieVector);
	void saveAddedEVWord();
	void loadAddedEVWord(EngTrieNode*& root, std::vector<WordDataEngVie>& engVieVector);


	// VE
	bool addVEFromTextFile(EngTrieNode*& root, std::string& inputWord, std::string& wordInfo,
		std::vector<WordDataEngVie>& vieEngVector);
	void addNewVEWord(EngTrieNode*& root, std::string& word, std::string& wordInfo,
		std::vector<WordDataEngVie>& vieEngVector);
	void saveAddedVEWord();
	void loadAddedVEWord(EngTrieNode*& root, std::vector<WordDataEngVie>& vieEngVector);
public:
	NewWord(sf::Font& font,sf::Font& font2 , sf::RenderWindow& window);
	void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen, EngTrieNode*& engEngRoot,
		std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector,
		std::vector<WordDataEngVie>& vieEngVector);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void setEndScreen(bool value);

	// Accessors
	std::string getEditWordType();
	std::string getEditWordDef();
	std::string getEditWordExample();
public:
	// From keyboard
	void addInEngEngDictKB(std::string& inputWord, EngTrieNode*& engEngRoot, std::vector<WordDataEngVie>& engEngVector);
	void addInEngVieDictKB(std::string& inputWord, EngTrieNode*& engEngRoot, std::vector<WordDataEngVie>& engVieVector);
	void addInVieEngDictKB(std::string& inputWord, EngTrieNode*& engEngRoot, std::vector<WordDataEngVie>& vieEngVector);

	void pushEEWordToQueue(std::string& inputWord, std::string& wordType, std::string& wordDef, std::string& wordExample);
	void pushEVWordToQueue(std::string& inputWord, std::string& wordType, std::string& wordDef, std::string& wordExample);
	void pushVEWordToQueue(std::string& inputWord, std::string& wordType, std::string& wordDef, std::string& wordExample);

	// From text file
	void addInEngEngDict(std::string& inputWord, EngTrieNode*& engEngRoot, std::vector<WordDataEngVie>& engEngVector);
	void addInEngVieDict(std::string& inputWord, EngTrieNode*& engEngRoot, std::vector<WordDataEngVie>& engVieVector);
	void addInVieEngDict(std::string& inputWord, EngTrieNode*& engEngRoot, std::vector<WordDataEngVie>& vieEngVector);
private:
	//std::queue<WordDataEngVie*> addedWord;
	std::queue<std::pair<std::string, std::string>> addedEEWord;
	std::queue<std::pair<std::string, std::string>> addedEVWord;
	std::queue<std::pair<std::string, std::string>> addedVEWord;

	sf::Texture addScreenTex, dataSetTex, addOptTex, cancelTex;
	sf::Sprite addScreen, dataSet, addOpt, cancel;

	Textbox wordBar;

	DisplayBox noteBox;
	DisplayBox displayBox;

	sf::Text dataSetText;
	sf::Text addOptText;

	Button backButton;
	Button addButton;
	Button dataSetButton;
	Button addOptButton;
	Button cancelButton;

	int currentDataSetID;
	/*
		0: EngEng
		1: EngVie
		2: VieEng
	*/

	int currentAddOptID;
	/*
		0: From keyboard
		1: From text file
	*/

	EditBox addBox;
	int currentEditAreaID;
	bool isAdding;

	bool isEndScreen;
private:
	void initBackground(sf::RenderWindow& window);
	void initWordBar(sf::Font& font);
	void initAddBox(const sf::Font& font, sf::Sprite& background);
	void initTextToEdit(const sf::String& theWord, const sf::String& theWordType,
		const sf::String& theWordDef, const sf::String& theWordExample);
	void initBackButton(sf::Font& font);
	void initCancelButton(sf::Font& font);
	void initAddButton(sf::Font& font);
	void initDataSetText(sf::Font& font);
	void initDataSetButton(sf::Font& font);
	void initAddOptText(sf::Font& font);
	void initAddOptButton(sf::Font& font);
	void initDisplayBox(sf::Font& font);
	void initNoteBox(sf::Font& font);
	void changeDataSet();
	void changeAddOpt();
};

#endif