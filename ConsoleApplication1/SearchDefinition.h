#ifndef SEARCHDEFINITION_H
#define SEARCHDEFINITION_H

#include "WordDisplayBox.h"

class SearchDefinitionScreen
{
public:
    SearchDefinitionScreen(sf::Font& font1, sf::Font& font2, sf::RenderWindow& window);
    void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen, 
    std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector,
    std::vector<WordDataEngVie>& vieEngVector);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    void setCurrentDataSetID(int theID);
    void setEndScreen(bool val);

    void searchInEngEngItems(std::string& inputDef, std::vector<WordDataEngVie>& EEItems);
    void searchInEngVieItems(std::string& inputDef, std::vector<WordDataEngVie>& EVItems);
    void searchInVieEngItems(std::string& inputDef, std::vector<WordDataEngVie>& VEItems);
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