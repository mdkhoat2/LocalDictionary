#ifndef APPLICATION_H
#define APPLICATION_H

#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"
#include "History.h"
#include "EditDefinition.h"
#include "DisplayDefinition.h"

class Application
{
public:
    enum class ScreenState
    {
        MainScreen,
        OptionsScreen,
        EditDefinitionScreen
    };
public:
    Application();
    ~Application();
    void loadEngEngDict();
    void run();
public:
    void handleEvent();
    void update();
    void render();
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
    History history;
    DisplayBox displayBox;

    EngTrieNode* engEngRoot;

    EditDefinitionScreen* editDefScreen;
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
};

#endif