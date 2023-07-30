#ifndef SEARCHDEFINITION_H
#define SEARCHDEFINITION_H

#include "Button.h"
#include "Textbox.h"
#include "WordData.h"

class WordDisplayBox
{
public:
    WordDisplayBox(const sf::Vector2f& pos, const sf::Vector2f& size, 
    const sf::Color& backColor, const sf::Color& textColor);
    ~WordDisplayBox();
    void update(sf::RenderWindow& window);
    void drawTo(sf::RenderWindow& window);

    void setPosition(const sf::Vector2f& pos);
    void setPosition(float xIn, float yIn);
    void setBackColor(const sf::Color& color);
    void setSize(const sf::Vector2f& size);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);
    void setCurrentDataSet(int theID);
    void clearData();
    bool isDataEmpty();
    void insertDataPair(std::pair<std::string, EngVieDef>& thePair);

    void wrapText(sf::Text& theText);
    void adjustTextPosition();
    void setUIText();
    void initFirstWord();
    void showNextWord();
    void showPrevWord();
    void showNoWord();
    void clearUIText();

    // For next and prev buttons
    bool isMouseOverNextButton(sf::RenderWindow& window);
    bool isMouseOverPrevButton(sf::RenderWindow& window);
    bool nextButtonDrawn();
    bool prevButtonDrawn();
private:
    sf::RectangleShape theBox;

    sf::Text word;
    sf::Text wordType;
    sf::Text wordDef;

    sf::Text word2;
    sf::Text wordType2;
    sf::Text wordDef2;

    std::vector<std::pair<std::string, EngVieDef>> wordArr;
    int firstWordID;
    int wordNum;

    bool showNextButton;
    bool showPrevButton;
    sf::Texture nextButtonTex;
    sf::Texture prevButtonTex;
    sf::Sprite nextButtonSprite;
    sf::Sprite prevButtonSprite;

    int currentDataSetID;
};

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