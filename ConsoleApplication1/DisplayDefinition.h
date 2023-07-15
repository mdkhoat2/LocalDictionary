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
    void setText(const sf::String& str);
    void setText(WordData& theWordData);
    void setCharacterSize(unsigned int size);

    void update(sf::RenderWindow& window);
    void drawTo(sf::RenderWindow& window);

    bool isMouseOver(sf::RenderWindow& window);

    void showNextDefButton();
    void showPrevDefButton();
    void wrapText();

private:
    sf::RectangleShape theBox;
    sf::Text definitionText;
    std::vector<sf::Text*> wordTypes;
    std::vector<sf::Text*> wordDefs[4]; 
    unsigned int wordTypeSize;
    unsigned int wordDefSize;
    
    Button* nextDefButton;
    Button* prevDefButton;
};




#endif