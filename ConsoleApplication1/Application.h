#ifndef APPLICATION_H
#define APPLICATION_H
#pragma once
#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"
#include "History.h"
#include "NewWord.h"
#include "RemoveWord.h"
#include "EditDefinition.h"
#include "DisplayDefinition.h"
#include "Favourite.h"
#include "SwitchDataSet.h"
#include "SearchDefinition.h"
#include "ProposeWord.h"
#include "Explore.h"
#include "RandomWord.h"
#include "RandomDef.h"

class Application
{
public:
    enum class ScreenState
    {
        MainScreen,
        OptionsScreen,
        AddScreen,
        RemoveScreen,
        EditDefinitionScreen,
        FavouriteScreen,
        SearchDefinitionScreen,
        RandomWordScreen,
        HistoryScreen,
        RandomDefScreen
    };
public:
    Application();
    ~Application();
    void loadEngEngDict();
    void loadEngVieDict();
    void loadVieEngDict();
    void loadEmojiDict();
    void run();
public:
    void handleEvent();
    void update();
    void render();
public:
    void searchInEngEngDict(std::string& inputWord, bool isForRandom);
    void searchInEngVieDict(std::string& inputWord, bool isForRandom);
    void searchInVieEngDict(std::string& inputWord, bool isForRandom);
    void searchInEmojiDict(std::string& inputWord, bool isForRandom);
public:
    void resetEverything();
    void resetHistoryAll();
    void resetEditDef();
    void resetFavorite();
    void clearFile(std::string filename);
private:
    sf::VideoMode videoMode;
    sf::RenderWindow window;

    sf::Texture mainScreenTex;
    sf::Sprite mainScreen;

    sf::Texture screenWithOptionsTex;
    sf::Sprite screenWithOptions;

    sf::Texture loadingScreenTexture;
    sf::Sprite loadingScreen;

    ScreenState currentScreen;

    int currentDataSetID;
        /*
            0: EngEng
            1: EngVie
            2: VieEng
            3: Emoji
        */
    int resetCount;

    sf::Font font;
    sf::Font font2;
    sf::Font font3;

    sf::Event event;

    Textbox searchBar;
    sf::Text dataSetText;

    Button searchButton;
    Button menuButton;
    Button dataSetButton;
    Button addButton;
    Button deleteButton;
    Button editDefButton;
    Button favouritebutton;
    Button searchDefButton;
    Button favouriteFlag;
    Button exploreButton;
    Button randomWordButton;
    Button randomDefButton;
    Button resetButton;
    Button fullHistoryButton;

    Favourite *favourite;
    History history;
    History history1;
    History history2;
    History history3;
    DisplayBox displayBox;

    EngTrieNode* engEngRoot;
    std::vector<WordDataEngVie> engEngVector;
    std::vector<WordDataEngVie> engVieVector;
    std::vector<WordDataEngVie> vieEngVector;
    std::vector<std::string> emojiVector;

    EditDefinitionScreen* editDefScreen;
    NewWord* newWord;
    RemoveWord* removeWord;
    SearchDefinitionScreen* searchDefScreen;
    ProposeWord* proposedWord;
    FavouriteOnMainAndOptionScreen* favouriteMain;
    RandomWord* randomWord;
    HistoryScreen* historyScreen;
    RandomDef* randomDef;
private:
    void initWindow();
    void initBackground();
    void initFont();
    void initSearchBar();
    void initSearchButton();
    void initDataSetText();
    void initDataSetButton();
    void initMenuButton();
    void initAddButton();
    void initDeleteButton();
    void initEditDefButton();
    void initDisplayBox();
    void initFavouriteButton();
    void initSearchDefButton();
    void initExploreButton();
    void initRandomWordButton();
	void initRandomDefButton();
    void initResetButton();
    void initFullHistoryButton();
    void changeDataSet();
    void loadAllHistory();
    void drawHistory();
    void initfavouriteFlag();
    void explore();
};


#endif
