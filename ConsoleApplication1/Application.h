#ifndef APPLICATION_H
#define APPLICATION_H

#include "Button.h"
#include "Textbox.h"
#include "Trie.h"

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

    sf::Font font;

    sf::Event event;

    Textbox searchBar;
    Button searchButton;

    TrieNode* engEngRoot;
private:
    void initWindow();
    void initBackground();
    void initFont();
    void initSearchBar();
    void initSearchButton();
};

#endif