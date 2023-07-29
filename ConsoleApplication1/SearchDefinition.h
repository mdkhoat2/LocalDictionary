#ifndef SEARCHDEFINITION_H
#define SEARCHDEFINITION_H

#include <vector>
#include "Button.h"
#include "Textbox.h"

class SearchDefinitionScreen
{
public:
    SearchDefinitionScreen(sf::Font& font1, sf::Font& font2, sf::RenderWindow& window);
    void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    void setCurrentDataSetID(int theID);
    void setEndScreen(bool val);
private:
    sf::Texture searchScreenTex;
    sf::Sprite searchScreen;
    sf::Texture dataSetTex;
    sf::Sprite dataSet;

    Textbox searchBar;

    Button backButton;
    Button dataSetButton;
    Button searchButton;

    int currentDataSetID;
    bool isEndScreen;
private:
    void initBackground(sf::RenderWindow& window);
    void initSearchBar(sf::Font& font);
    void initSearchButton(sf::Font& font);
    void initBackButton(sf::Font& font);
    void initDataSetButton(sf::Font& font);
    void changeDataSet();
};



#endif