#ifndef WORDDISPLAYBOX_H
#define WORDDISPLAYBOX_H

#include "Button.h"
#include "Textbox.h"
#include "WordData.h"

// Use for to display words when Search definition
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





#endif