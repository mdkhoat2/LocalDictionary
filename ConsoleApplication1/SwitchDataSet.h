#ifndef SWITCHDATASET_H
#define SWITCHDATASET_H

#include <string>
#include "Button.h"

class DataSetBar
{
public:
    DataSetBar();
    ~DataSetBar();
    void initVariables();
    bool isMouseOverSwitchButton(sf::RenderWindow& window);
    void setFont(const sf::Font& font);
    const sf::String& getCurrentDataSet();

    void update(sf::RenderWindow& window);
    void drawTo(sf::RenderWindow& window);
    
    void changeCurDataSet();

private:
    sf::Text* curDataSetText;
    sf::Font* textFont;
    sf::Texture* dataSetBarTex;
    sf::Sprite* dataSetBar;
    sf::CircleShape* switchButton;
    /*
        Data set ID:
        0: English - English
        1: English - Vietnamese
        2: Vietnamese - English
        3: Emojis
    */
    int curDataSetID;
};


#endif