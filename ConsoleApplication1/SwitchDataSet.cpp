
#include "SwitchDataSet.h"

DataSetBar::DataSetBar() :
    dataSetBarTex(nullptr),
    dataSetBar(nullptr),
    switchButton(nullptr),
    curDataSetText(nullptr),
    textFont(nullptr),
    curDataSetID(0)
{
    initVariables();
}

DataSetBar::~DataSetBar()
{
    delete dataSetBarTex;
    delete dataSetBar;
    delete switchButton;
    delete curDataSetText;
    delete textFont;
}

void DataSetBar::initVariables()
{
    dataSetBarTex = new sf::Texture();
    if(!dataSetBarTex->loadFromFile("background/data-set.png"))
        std::cout << "Cannot load data set texture" << std::endl;
    dataSetBarTex->setSmooth(true);
    dataSetBar = new sf::Sprite();
    dataSetBar->setTexture(*dataSetBarTex);
    dataSetBar->setScale(1.f, 1.f);
    dataSetBar->setPosition(sf::Vector2f(420.f, 60.f));
    // Initialize switch button;
    switchButton = new sf::CircleShape(22.f);
    switchButton->setFillColor(sf::Color::Transparent);
    switchButton->setPosition(sf::Vector2f(748.f, 75.f));
    // Initialize text
    curDataSetText = new sf::Text;
    curDataSetText->setString("EN - EN");
    curDataSetText->setCharacterSize(25);
    float xText = dataSetBar->getPosition().x + 44.f;
    float yText = dataSetBar->getPosition().y + 22.f;
    curDataSetText->setPosition(xText, yText);
    curDataSetText->setFillColor(sf::Color::Black);
    textFont = new sf::Font;
    if(!textFont->loadFromFile("font/SF-Pro-Display-Medium.otf"))
        std::cout << "Cannot load text for data set bar" << std::endl;
    curDataSetText->setFont(*textFont);
}

bool DataSetBar::isMouseOverSwitchButton(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if(switchButton)
        return switchButton->getGlobalBounds().contains(mousePos.x, mousePos.y);
    return false;
}

void DataSetBar::setFont(const sf::Font &font)
{
    if(curDataSetText)
        curDataSetText->setFont(font);
}

const sf::String& DataSetBar::getCurrentDataSet()
{
    if(curDataSetText)
        return curDataSetText->getString();
    return sf::String();
}

void DataSetBar::drawTo(sf::RenderWindow &window)
{
    if(dataSetBar)
        window.draw(*dataSetBar);
    if(switchButton)
        window.draw(*switchButton);
    if(curDataSetText)
        window.draw(*curDataSetText);
}

void DataSetBar::changeCurDataSet()
{
    if(curDataSetID == 3)
        curDataSetID = 0;
    else
        ++curDataSetID;
    if(curDataSetID == 0)
    {
        curDataSetText->setString("EN - EN");
    }
    else if(curDataSetID == 1)
    {
        curDataSetText->setString("EN - VI");
    }
    else if(curDataSetID == 2)
    {
        curDataSetText->setString("VI - EN");
    }
    else if(curDataSetID == 3)
    {
        curDataSetText->setString("EMOJI");
    }
}
