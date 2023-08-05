#ifndef APPLICATION_H
#define APPLICATION_H

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
        SearchDefinitionScreen
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
    void searchInEngEngDict(std::string& inputWord);
    void searchInEngVieDict(std::string& inputWord);
    void searchInVieEngDict(std::string& inputWord);
    void searchInEmojiDict(std::string& inputWord);
private:
    sf::VideoMode videoMode;
    sf::RenderWindow window;

    sf::Texture mainScreenTex;
    sf::Sprite mainScreen;

    sf::Texture screenWithOptionsTex;
    sf::Sprite screenWithOptions;

    ScreenState currentScreen;

    int currentDataSetID;
        /*
            0: EngEng
            1: EngVie
            2: VieEng
            3: Emoji
        */

    sf::Font font;
    sf::Font font2;

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

    Favourite *favourite;
    History history;
    History history1;
    History history2;
    History history3;
    DisplayBox displayBox;

    EngTrieNode* engEngRoot;
    std::vector<std::string> engEngVector;
    std::vector<std::string> engVieVector;
    std::vector<std::string> vieEngVector;
    std::vector<std::string> emojiVector;

    EditDefinitionScreen* editDefScreen;
    NewWord* newWord;
    RemoveWord* removeWord;
    SearchDefinitionScreen* searchDefScreen;
    ProposeWord* proposedWord;
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
    void changeDataSet();
    void loadAllHistory();
    void drawHistory();
};


#endif