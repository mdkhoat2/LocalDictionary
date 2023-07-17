
#include "SwitchDataSet.h"

DataSetBar::DataSetBar() :
    dataSetBarTex(nullptr),
    dataSetBar(nullptr),
    switchButton(nullptr),
    curDataSetText(nullptr)
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
    dataSetBar->setScale(0.5f, 0.5f);
    dataSetBar->setPosition(sf::Vector2f(420.f, 60.f));
    // Initialize switch button;
    switchButton = new Button("", {40, 40}, 20, sf::Color::Transparent, sf::Color::Transparent);
    switchButton->setPosition(sf::Vector2f(750.f, 75.f));
    // Initialize text
    curDataSetText = new sf::Text;
    curDataSetText->setString("ENGLISH - ENGLISH");
    curDataSetText->setCharacterSize(25);
    float xText = dataSetBar->getPosition().x + 48.f;
    float yText = dataSetBar->getPosition().y + 22.f;
    curDataSetText->setPosition(xText, yText);
    curDataSetText->setFillColor(sf::Color::Black);
    textFont = new sf::Font;
    if(!textFont->loadFromFile("font/SF-Pro-Display-Medium.otf"))
        std::cout << "Cannot load text for data set bar" << std::endl;
    curDataSetText->setFont(*textFont);
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
        switchButton->drawTo(window);
    if(curDataSetText)
        window.draw(*curDataSetText);
}
