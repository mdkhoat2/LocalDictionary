#ifndef SWITCHDATASET_H
#define SWITCHDATASET_H

#include <string>
#include "Button.h"

class DataSetBox
{
public:
    DataSetBox();
    ~DataSetBox();
    void initVariables();
    bool isMouseOverSwitchButton(sf::RenderWindow& window);
    void setFont(const sf::Font& font);
    int getCurrentDataSetID();

    void update(sf::RenderWindow& window);
    void drawTo(sf::RenderWindow& window);
    
    void changeCurDataSet();

private:
    sf::Text* dataSetText;
    Button* dataSetButton;
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