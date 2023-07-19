#include <sstream>
#include <string>
#include "DisplayDefinition.h"

DisplayBox::DisplayBox(const sf::Vector2f& pos, const sf::Vector2f& size, 
    const sf::Color& backColor, const sf::Color& textColor) : 
    theBox(),
    word(),
    wordType(),
    wordDef(),
    engEngTypeID(0),
    engEngDefID(1),
    engEngPtr(nullptr),
    engEngData(nullptr),
    engEngDefNum(0),
    engVieData(nullptr),
    engVieDefID(0),
    showNextButton(false),
    showPrevButton(false),
    nextButtonTex(),
    prevButtonTex(),
    nextButtonSprite(),
    prevButtonSprite(),
    wordExample(),
    showExample(false)
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

    if(!nextButtonTex.loadFromFile("background/next-button.png"))
        std::cout << "Cannot load next button texture" << std::endl;
    nextButtonTex.setSmooth(true);

    if(!prevButtonTex.loadFromFile("background/prev-button.png"))
        std::cout << "Cannot load prev button texture" << std::endl;
    prevButtonTex.setSmooth(true);

    nextButtonSprite.setTexture(nextButtonTex);
    nextButtonSprite.setTextureRect(sf::IntRect(63, 45, 110, 110));

    prevButtonSprite.setTexture(prevButtonTex);
    prevButtonSprite.setTextureRect(sf::IntRect(65, 45, 110, 110));
    
    // std::cout << nextButtonTex->getSize().x << " " << nextButtonTex->getSize().y << std::endl;
    // std::cout << prevButtonTex->getSize().x << " " << prevButtonTex->getSize().y << std::endl;

    nextButtonSprite.setPosition(700, 700);
    nextButtonSprite.setScale(0.5f, 0.5f);
    showNextButton = false;

    prevButtonSprite.setPosition(620, 700);
    prevButtonSprite.setScale(0.5f, 0.5f);
    showPrevButton = false;

    // Eng Vie word data
}

DisplayBox::~DisplayBox()
{
    delete engEngData;
    delete engVieData;
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
    if(showNextButton)
    {
        window.draw(nextButtonSprite);
    }
        
    if(showPrevButton)
    {
        window.draw(prevButtonSprite);
    }
        
}

void DisplayBox::getWordDataEngEng(std::string &inputWord, std::string &wordInfo)
{
    if(engEngData == nullptr)
    {
        engEngData = new WordData;
        extractWordData(*engEngData, inputWord, wordInfo);
    }
    else // delete old word data
    {
        delete engEngData;
        showNextButton = false;
        showPrevButton = false;
        engEngData = new WordData;
        extractWordData(*engEngData, inputWord, wordInfo);
    }
    engEngDefNum = countNumOfDefs(*engEngData);
    initFirstDef();
}

void DisplayBox::wrapText(sf::Text& theText)
{
    std::string str = theText.getString();
    std::string wrappedStr;

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
    word.setString(engEngData->word);

    engEngDefID = 1;
    for(int i = 0; i < 4; ++i)
    {
        if(engEngData->defListHead[i] != nullptr)
        {
            engEngTypeID = i;
            engEngPtr = engEngData->defListHead[i];
            break;
        }
    }
    // initialize the buttons
    if(engEngDefNum > 1)
    {
        showNextButton = true;
    }
    setUIText();
}

void DisplayBox::setUIText()
{
    // Word type
    if(engEngTypeID == 0)
        wordType.setString("noun");
    else if(engEngTypeID == 1)
        wordType.setString("verb");
    else if(engEngTypeID == 2)
        wordType.setString("adjective");
    else
        wordType.setString("adverb");
    // Word definition corresponding to that word type
    wordDef.setString(engEngPtr->wordDef);
    wrapText(wordDef);
}

void DisplayBox::showNextDef()
{
    ++engEngDefID;
    // If there are another definitions of the current word type
    if(engEngPtr->next != nullptr)
    {
        engEngPtr = engEngPtr->next;
    }
    // Need to search for definition of other word types
    else 
    {
        for(int i = engEngTypeID + 1; i < 4; ++i)
        {
            if(engEngData->defListHead[i] != nullptr)
            {
                engEngTypeID = i;
                engEngPtr = engEngData->defListHead[engEngTypeID];
                break;
            }
        }
    }
    setUIText();
    if(engEngDefID > 1)
        showPrevButton = true;
    if(engEngDefID == engEngDefNum)
        showNextButton = false;
}

void DisplayBox::showPrevDef()
{
    --engEngDefID;
    // If it is not the first definition of the current word type
    if(engEngPtr != engEngData->defListHead[engEngTypeID])
    {
        WordDefNode* targetPtr = engEngData->defListHead[engEngTypeID];
        while(targetPtr->next != engEngPtr)
            targetPtr = targetPtr->next;
        engEngPtr = targetPtr;
    }
    // Need to search for definitions of previous word types
    else
    {
        for(int i = engEngTypeID - 1; i >= 0; --i)
        {
            if(engEngData->defListHead[i] != nullptr)
            {
                // Get the last definition in this list
                engEngTypeID = i;
                WordDefNode* targetPtr = engEngData->defListHead[engEngTypeID];
                while(targetPtr->next != nullptr)
                    targetPtr = targetPtr->next;
                engEngPtr = targetPtr;
                break;
            }
        }
    }
    setUIText();
    // Change status of buttons
    if(engEngDefID < engEngDefNum)
        showNextButton = true;
    if(engEngDefID == 1)
        showPrevButton = false;
}

void DisplayBox::showNoDefinitions()
{
    if(engEngData)
    {
        delete engEngData;
        engEngData = nullptr;
    }
    showNextButton = false;
    showPrevButton = false;

    word.setString("No Definitions Found!");
    wordType.setString("");
    wordDef.setString("");
}

bool DisplayBox::isMouseOverNextButton(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return nextButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool DisplayBox::isMouseOverPrevButton(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return prevButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool DisplayBox::nextButtonDrawn()
{
    return showNextButton;
}

bool DisplayBox::prevButtonDrawn()
{
    return showPrevButton;
}
