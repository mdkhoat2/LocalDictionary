#ifndef APPLICATION_H
#define APPLICATION_H

#include "Button.h"
#include "Textbox.h"
#include "Trie.h"
#include "WordData.h"
#include "History.h"

class Application
{
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

    bool isMainScreen = true;

    sf::Font font;

    sf::Event event;

    Textbox searchBar;
    Button searchButton;
    Button menuButton;
    Button addButton;
    History history;

    EngTrieNode* engEngRoot;
    VieTrieNode* vieEngRoot;
private:
    void initWindow();
    void initBackground();
    void initFont();
    void initSearchBar();
    void initSearchButton();
    void initMenuButton();
    void initAddButton();
};

#endif