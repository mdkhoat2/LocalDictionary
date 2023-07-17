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
    

private:
    sf::Text* curDataSetText;
    sf::Font* textFont;
    sf::Texture* dataSetBarTex;
    sf::Sprite* dataSetBar;
    Button* switchButton;
};


#endif