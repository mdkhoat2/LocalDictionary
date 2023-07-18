#ifndef APPLICATION_H
#define APPLICATION_H

#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"
#include "History.h"
#include "NewWord.h"
#include "EditDefinition.h"
#include "DisplayDefinition.h"
#include"Favourite.h"
#include "SwitchDataSet.h"

class Application
{
public:
    enum class ScreenState
    {
        MainScreen,
        OptionsScreen,
        AddScreen,
        EditDefinitionScreen
    };
public:
    Application();
    ~Application();
    void loadEngEngDict();
    void loadEngVieDict();
    void run();
public:
    void handleEvent();
    void update();
    void render();
public:
    void searchInEngEngDict(std::string& inputWord);
    void searchInEngVieDict(std::string& inputWord);
private:
    sf::VideoMode videoMode;
    sf::RenderWindow window;

    sf::Texture mainScreenTex;
    sf::Sprite mainScreen;

    sf::Texture screenWithOptionsTex;
    sf::Sprite screenWithOptions;

    ScreenState currentScreen;

    sf::Font font;

    sf::Event event;

    Textbox searchBar;

    Button searchButton;
    Button menuButton;
    Button addButton;
    Button editDefButton;
    Button favouritebutton;

    History history;
    DisplayBox displayBox;
    DataSetBar dataSetBar;

    EngTrieNode* engEngRoot;

    EditDefinitionScreen* editDefScreen;
    NewWord* newWord;
private:
    void initWindow();
    void initBackground();
    void initFont();
    void initSearchBar();
    void initSearchButton();
    void initMenuButton();
    void initAddButton();
    void initEditDefButton();
    void initDisplayBox();
    void initFavouriteButton();
};

#endif