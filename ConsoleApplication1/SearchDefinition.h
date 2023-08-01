#ifndef SEARCHDEFINITION_H
#define SEARCHDEFINITION_H

#include "WordDisplayBox.h"

class SearchDefinitionScreen
{
public:
    SearchDefinitionScreen(sf::Font& font1, sf::Font& font2, sf::RenderWindow& window);
    void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    void setCurrentDataSetID(int theID);
    void setEndScreen(bool val);

    void insertEngEngItem(std::string& word, std::string& wordInfo);
    void insertEngVieItem(std::string& word, std::string& wordInfo);
    void insertVieEngItem(std::string& word, std::string& wordInfo);

    void searchInEngEngItems(std::string& inputDef);
    void searchInEngVieItems(std::string& inputDef);
    void searchInVieEngItems(std::string& inputDef);
private:
    std::vector<WordDataEngVie> EEItems;
    std::vector<WordDataEngVie> EVItems;
    std::vector<WordDataEngVie> VEItems;

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

    WordDisplayBox displayBox;
private:
    void initBackground(sf::RenderWindow& window);
    void initSearchBar(sf::Font& font);
    void initSearchButton(sf::Font& font);
    void initBackButton(sf::Font& font);
    void initDataSetButton(sf::Font& font);
    void initDisplayBox(sf::Font &font);
    void changeDataSet();
};



#endif