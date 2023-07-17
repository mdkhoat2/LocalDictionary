#ifndef DISPLAYDEFINITION_H
#define DISPLAYDEFINITION_H

#include "Button.h"
#include "WordData.h"

class DisplayBox
{
public:
    DisplayBox(const sf::Vector2f& pos, const sf::Vector2f& size, 
    const sf::Color& backColor, const sf::Color& textColor);
    ~DisplayBox();
    void setPosition(const sf::Vector2f& pos);
    void setPosition(float xIn, float yIn);
    void setBackColor(const sf::Color& color);
    void setSize(const sf::Vector2f& size);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);

    void update(sf::RenderWindow& window);
    void drawTo(sf::RenderWindow& window);

    void getWordData(std::string& inputWord, std::string& wordInfo);

    void wrapText(sf::Text& theText);
    void initFirstDef();
    void setUIText();
    void showNextDef();
    void showPrevDef();
    void showNoDefinitions();

    bool isMouseOverNextButton(sf::RenderWindow& window);
    bool isMouseOverPrevButton(sf::RenderWindow& window);
    bool nextButtonDrawn();
    bool prevButtonDrawn();
    
private:
    sf::RectangleShape theBox;
    
    sf::Text word;
    sf::Text wordType;
    sf::Text wordDef;

    int curWordTypeID;
    int curWordDefID;
    WordDefNode* curWordDefPtr;

    WordData* curWordData;
    int numOfDefs;

    bool showNextButton;
    bool showPrevButton;
    sf::Texture* nextButtonTex;
    sf::Texture* prevButtonTex;
    sf::Sprite* nextButtonSprite;
    sf::Sprite* prevButtonSprite;
};




#endif