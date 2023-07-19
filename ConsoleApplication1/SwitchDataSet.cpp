
#include "SwitchDataSet.h"

DataSetBox::DataSetBox() :
    dataSetButton(nullptr),
    dataSetText(nullptr),
    curDataSetID(0)
{
    initVariables();
}

DataSetBox::~DataSetBox()
{
    delete dataSetButton;
    delete dataSetText;
}

void DataSetBox::initVariables()
{
    // Initialize switch button;
    dataSetButton = new Button("      EN - EN", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Black);
    dataSetButton->setPosition(sf::Vector2f(972, 72));
    // Initialize text
    dataSetText = new sf::Text;
    dataSetText->setString("EN - EN");
    dataSetText->setCharacterSize(25);
    dataSetText->setFillColor(sf::Color::Black);
}
//
//bool DataSetBox::isMouseOverSwitchButton(sf::RenderWindow &window)
//{
//    
//}

void DataSetBox::setFont(const sf::Font &font)
{
    if(dataSetText)
        dataSetText->setFont(font);
}

int DataSetBox::getCurrentDataSetID()
{
    return curDataSetID;
}

void DataSetBox::drawTo(sf::RenderWindow &window)
{
    if(dataSetButton)
        dataSetButton->drawTo(window);
    if(dataSetText)
        window.draw(*dataSetText);
}

void DataSetBox::changeCurDataSet()
{
    if(curDataSetID == 3)
        curDataSetID = 0;
    else
        ++curDataSetID;
    if(curDataSetID == 0)
    {
        dataSetText->setString("EN - EN");
    }
    else if(curDataSetID == 1)
    {
        dataSetText->setString("EN - VI");
    }
    else if(curDataSetID == 2)
    {
        dataSetText->setString("VI - EN");
    }
    else if(curDataSetID == 3)
    {
        dataSetText->setString("EMOJI");
    }
}
