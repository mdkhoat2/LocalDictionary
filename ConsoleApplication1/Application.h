#ifndef APPLICATION_H
#define APPLICATION_H

#include "button.h"
#include "textbox.h"

class Application
{
public:
    Application();
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
private:
    void initWindow();
    void initBackground();
    void initFont();
    void initSearchBar();
    void initSearchButton();
};

#endif