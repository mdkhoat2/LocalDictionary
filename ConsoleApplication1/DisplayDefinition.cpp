#include <sstream>
#include <string>
#include "DisplayDefinition.h"

DisplayBox::DisplayBox(const sf::Vector2f& pos, const sf::Vector2f& size, 
    const sf::Color& backColor, const sf::Color& textColor) : 
    curWordData(nullptr),
    curWordDefPtr(nullptr),
    nextButton(nullptr),
    prevButton(nullptr),
    curWordTypeID(0),
    curWordDefID(1),
    wordType(),
    wordDef(),
    word(),
    showNextButton(false),
    showPrevButton(false),
    numOfDefs(0)
{
    theBox.setPosition(pos);
    float xText = pos.x + 20.f;
    float yText = pos.y + 20.f;
    word.setPosition(xText, yText);
    wordType.setPosition(xText, yText + 50.f);
    wordDef.setPosition(xText, yText + 90.f);

    theBox.setSize(size);

    theBox.setFillColor(backColor);
    word.setFillColor(textColor);
    wordType.setFillColor(textColor);
    wordDef.setFillColor(textColor);

    word.setStyle(sf::Text::Bold);
    wordType.setStyle(sf::Text::Bold | sf::Text::Italic);
    wordDef.setStyle(sf::Text::Regular);
}

DisplayBox::~DisplayBox()
{
    delete nextButtonTex;
    delete prevButtonTex;
    delete nextButtonSprite;
    delete prevButtonSprite;
    delete curWordDefPtr;
    delete curWordData;
}

void DisplayBox::setPosition(const sf::Vector2f &pos)
{
    theBox.setPosition(pos);
    float xText = pos.x + 20.f;
    float yText = pos.y + 20.f;
    word.setPosition(xText, yText);
    wordType.setPosition(xText, yText + 50.f);
    wordDef.setPosition(xText, yText + 90.f);
}

void DisplayBox::setPosition(float xIn, float yIn)
{
    theBox.setPosition(xIn, yIn);
    float xText = xIn + 20.f;
    float yText = yIn + 20.f;
    word.setPosition(xText, yText);
    wordType.setPosition(xText, yText + 50.f);
    wordDef.setPosition(xText, yText + 90.f);
}

void DisplayBox::setBackColor(const sf::Color &color)
{
    theBox.setFillColor(color);
}

void DisplayBox::setSize(const sf::Vector2f &size)
{
    theBox.setSize(size);
}

void DisplayBox::setFont(const sf::Font &font)
{
    word.setFont(font);
    wordType.setFont(font);
    wordDef.setFont(font);
}

void DisplayBox::setCharacterSize(unsigned int size)
{
    word.setCharacterSize(size + 10);
    wordType.setCharacterSize(size);
    wordDef.setCharacterSize(size);
}

void DisplayBox::update(sf::RenderWindow &window)
{
    
}

void DisplayBox::drawTo(sf::RenderWindow &window)
{
    window.draw(theBox);
    window.draw(word);
    window.draw(wordType);
    window.draw(wordDef);
    if(nextButtonSprite && showNextButton)
    {
        window.draw(*nextButtonSprite);
    }
        
    if(prevButtonSprite && showPrevButton)
    {
        window.draw(*prevButtonSprite);
    }
        
}

void DisplayBox::getWordData(std::string &inputWord, std::string &wordInfo)
{
    if(!curWordData)
    {
        curWordData = new WordData;
        extractWordData(*curWordData, inputWord, wordInfo);
    }
    else // delete old word data
    {
        delete curWordData;
        if(nextButtonSprite)
        {
            showNextButton = false;
        }
        if(prevButtonSprite)
        {
            showPrevButton = false;
        }
        curWordData = new WordData;
        extractWordData(*curWordData, inputWord, wordInfo);
    }
    numOfDefs = countNumOfDefs(*curWordData);
    initFirstDef();
}

void DisplayBox::wrapText(sf::Text& theText)
{
    std::string str = theText.getString();
    std::string wrappedStr;
    unsigned int charSize = theText.getCharacterSize();

    std::string word;
    std::istringstream iss(str);
    std::string line;
    theText.setString("");

    while (iss >> word) {
        theText.setString(line + " " + word);
        if (theText.getLocalBounds().width > theBox.getLocalBounds().width - 40.f) {
            wrappedStr += line + '\n';
            line = word;
        } else {
            line += (line.empty() ? "" : " ") + word;
        }
    }

    wrappedStr += line;
    theText.setString(wrappedStr);
}

void DisplayBox::initFirstDef()
{
    // initialize the text to display
    word.setString(curWordData->word);

    curWordDefID = 1;
    for(int i = 0; i < 4; ++i)
    {
        if(curWordData->defListHead[i] != nullptr)
        {
            curWordTypeID = i;
            curWordDefPtr = curWordData->defListHead[i];
            break;
        }
    }
    // initialize the buttons
    if(numOfDefs > 1)
    {
        nextButtonTex = new sf::Texture();
        if(!nextButtonTex->loadFromFile("background/next-button.png"))
            std::cout << "Cannot load next button texture" << std::endl;
        nextButtonTex->setSmooth(true);
        prevButtonTex = new sf::Texture();
        if(!prevButtonTex->loadFromFile("background/prev-button.png"))
            std::cout << "Cannot load prev button texture" << std::endl;
        prevButtonTex->setSmooth(true);
        nextButtonSprite = new sf::Sprite();
        nextButtonSprite->setTexture(*nextButtonTex);
        prevButtonSprite = new sf::Sprite();
        prevButtonSprite->setTexture(*prevButtonTex);
        
        // std::cout << nextButtonTex->getSize().x << " " << nextButtonTex->getSize().y << std::endl;
        // std::cout << prevButtonTex->getSize().x << " " << prevButtonTex->getSize().y << std::endl;

        nextButtonSprite->setPosition(700, 600);
        nextButtonSprite->setScale(0.3f, 0.3f);
        showNextButton = true;

        prevButtonSprite->setPosition(560, 600);
        prevButtonSprite->setScale(0.3f, 0.3f);
        showPrevButton = false;
        
    }
    setUIText();
}

void DisplayBox::setUIText()
{
    // Word type
    if(curWordTypeID == 0)
        wordType.setString("noun");
    else if(curWordTypeID == 1)
        wordType.setString("verb");
    else if(curWordTypeID == 2)
        wordType.setString("adjective");
    else
        wordType.setString("adverb");
    // Word definition corresponding to that word type
    wordDef.setString(curWordDefPtr->wordDef);
    wrapText(wordDef);
}

void DisplayBox::showNextDef()
{
    ++curWordDefID;
    // If there are another definitions of the current word type
    if(curWordDefPtr->next != nullptr)
    {
        curWordDefPtr = curWordDefPtr->next;
    }
    // Need to search for definition of other word types
    else 
    {
        for(int i = curWordTypeID + 1; i < 4; ++i)
        {
            if(curWordData->defListHead[i] != nullptr)
            {
                curWordTypeID = i;
                curWordDefPtr = curWordData->defListHead[curWordTypeID];
                break;
            }
        }
    }
    setUIText();
    if(curWordDefID > 1)
        showPrevButton = true;
    if(curWordDefID == numOfDefs)
        showNextButton = false;
}

void DisplayBox::showPrevDef()
{
    --curWordDefID;
    // If it is not the first definition of the current word type
    if(curWordDefPtr != curWordData->defListHead[curWordTypeID])
    {
        WordDefNode* targetPtr = curWordData->defListHead[curWordTypeID];
        while(targetPtr->next != curWordDefPtr)
            targetPtr = targetPtr->next;
        curWordDefPtr = targetPtr;
    }
    // Need to search for definitions of previous word types
    else
    {
        for(int i = curWordTypeID - 1; i >= 0; --i)
        {
            if(curWordData->defListHead[i] != nullptr)
            {
                // Get the last definition in this list
                curWordTypeID = i;
                WordDefNode* targetPtr = curWordData->defListHead[curWordTypeID];
                while(targetPtr->next != nullptr)
                    targetPtr = targetPtr->next;
                curWordDefPtr = targetPtr;
                break;
            }
        }
    }
    setUIText();
    // Change status of buttons
    if(curWordDefID < numOfDefs)
        showNextButton = true;
    if(curWordDefID == 1)
        showPrevButton = false;
}

void DisplayBox::showNoDefinitions()
{
    if(curWordDefPtr)
    {
        delete curWordDefPtr;
        curWordDefPtr = nullptr;
    }
    if(curWordData)
    {
        delete curWordData;
        curWordData = nullptr;
    }
    
    if(nextButtonSprite)
    {
        showNextButton = false;
    }
    if(prevButtonSprite)
    {
        showPrevButton = false;
    }
    word.setString("No Definitions Found!");
    wordType.setString("");
    wordDef.setString("");
}

bool DisplayBox::isMouseOverNextButton(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if(nextButtonSprite)
        return nextButtonSprite->getGlobalBounds().contains(mousePos.x, mousePos.y);
    return false;
}

bool DisplayBox::isMouseOverPrevButton(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if(prevButtonSprite)
        return prevButtonSprite->getGlobalBounds().contains(mousePos.x, mousePos.y);
    return false;
}

bool DisplayBox::nextButtonDrawn()
{
    return showNextButton;
}

bool DisplayBox::prevButtonDrawn()
{
    return showPrevButton;
}
