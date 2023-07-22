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
        FavouriteScreen
    };
public:
    Application();
    ~Application();
    void loadEngEngDict();
    void loadEngVieDict();
    void loadVieEngDict();
    void run();
public:
    void handleEvent();
    void update();
    void render();
public:
    void searchInEngEngDict(std::string& inputWord);
    void searchInEngVieDict(std::string& inputWord);
    void searchInVieEngDict(std::string& inputWord);
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

    Favourite *favourite;
    History history;
    DisplayBox displayBox;

    EngTrieNode* engEngRoot;

    EditDefinitionScreen* editDefScreen;
    NewWord* newWord;
    RemoveWord* removeWord;
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
    void changeDataSet();
};

#endif