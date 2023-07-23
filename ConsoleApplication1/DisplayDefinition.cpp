#include <sstream>
#include <string>
#include "DisplayDefinition.h"

DisplayBox::DisplayBox(const sf::Vector2f& pos, const sf::Vector2f& size, 
    const sf::Color& backColor, const sf::Color& textColor) : 
    theBox(),
    word(),
    wordType(),
    wordDef(),
    wordExample(),
    engEngTypeID(0),
    engEngDefID(1),
    engEngPtr(nullptr),
    engEngData(nullptr),
    engEngDefNum(0),
    engVieData(nullptr),
    engVieDefID(0),
    engVieDefNum(0),
    vieEngData(nullptr),
    vieEngDefID(0),
    vieEngDefNum(0),
    showNextButton(false),
    showPrevButton(false),
    nextButtonTex(),
    prevButtonTex(),
    nextButtonSprite(),
    prevButtonSprite()
{
    theBox.setPosition(pos);
    float xText = pos.x + 30.f;
    float yText = pos.y + 30.f;
    word.setPosition(xText, yText);
    wordType.setPosition(xText, yText + 40.f);
    wordDef.setPosition(xText, yText + 90.f);
    wordExample.setPosition(xText, yText + 250.f);

    theBox.setSize(size);

    theBox.setFillColor(backColor);
    word.setFillColor(textColor);
    wordType.setFillColor(textColor);
    wordDef.setFillColor(textColor);
    wordExample.setFillColor(sf::Color(128, 128, 128));

    word.setStyle(sf::Text::Bold);
    wordType.setStyle(sf::Text::Regular);
    wordDef.setStyle(sf::Text::Regular);
    wordExample.setStyle(sf::Text::Regular);

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

    nextButtonSprite.setPosition(870, 800);
    nextButtonSprite.setScale(0.5f, 0.5f);
    showNextButton = false;

    prevButtonSprite.setPosition(100, 800);
    prevButtonSprite.setScale(0.5f, 0.5f);
    showPrevButton = false;

}

DisplayBox::~DisplayBox()
{
    delete engEngData;
    delete engVieData;
    delete vieEngData;
}

void DisplayBox::setPosition(const sf::Vector2f &pos)
{
    theBox.setPosition(pos);
    float xText = pos.x + 20.f;
    float yText = pos.y + 20.f;
    word.setPosition(xText, yText);
    wordType.setPosition(xText, yText + 50.f);
    wordDef.setPosition(xText, yText + 90.f);
    wordExample.setPosition(xText, yText + 130.f);
}

void DisplayBox::setPosition(float xIn, float yIn)
{
    theBox.setPosition(xIn, yIn);
    float xText = xIn + 20.f;
    float yText = yIn + 20.f;
    word.setPosition(xText, yText);
    wordType.setPosition(xText, yText + 50.f);
    wordDef.setPosition(xText, yText + 90.f);
    wordExample.setPosition(xText, yText + 130.f);
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
    wordExample.setFont(font);
}

void DisplayBox::setCharacterSize(unsigned int size)
{
    word.setCharacterSize(size + 10);
    wordType.setCharacterSize(size);
    wordDef.setCharacterSize(size);
    wordExample.setCharacterSize(size);
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
    window.draw(wordExample);
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
    // delete old data of other data sets
    if(engVieData)
    {
        delete engVieData;
        engVieData = nullptr;
    }
    if(vieEngData)
    {
        delete vieEngData;
        vieEngData = nullptr;
    }
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

void DisplayBox::getWordDataEngVie(std::string &inputWord, std::string &wordInfo)
{
    // delete old data of other data sets
    if(engEngData)
    {
        delete engEngData;
        engEngData = nullptr;
    }
    if(vieEngData)
    {
        delete vieEngData;
        vieEngData = nullptr;
    }
    if(engVieData == nullptr)
    {
        engVieData = new WordDataEngVie;
        extractEngVieData(*engVieData, inputWord, wordInfo);
    }
    else // delete old word data
    {
        delete engVieData;
        showNextButton = false;
        showPrevButton = false;
        engVieData = new WordDataEngVie;
        extractEngVieData(*engVieData, inputWord, wordInfo);
    }
    engVieDefNum = engVieData->defList.size();
    initEngVieFirstDef();
}

void DisplayBox::getWordDataVieEng(std::string &inputWord, std::string &wordInfo)
{
    // delete old data of other data sets
    if(engEngData)
    {
        delete engEngData;
        engEngData = nullptr;
    }
    if(engVieData)
    {
        delete engVieData;
        engVieData = nullptr;
    }
    if(vieEngData == nullptr)
    {
        vieEngData = new WordDataEngVie;
        extractVieEngData(*vieEngData, inputWord, wordInfo);
    }
    else // delete old word data
    {
        delete vieEngData;
        showNextButton = false;
        showPrevButton = false;
        vieEngData = new WordDataEngVie;
        extractVieEngData(*vieEngData, inputWord, wordInfo);
    }
    vieEngDefNum = vieEngData->defList.size();
    initVieEngFirstDef();
}

void DisplayBox::wrapText(sf::Text& theText)
{
    std::string str = theText.getString();
    std::string wrappedStr;

    std::istringstream iss(str);
    std::string word;
    std::string line;

    // Clear theText before wrapping
    theText.setString("");

    while (std::getline(iss, word, '\n')) {
        // Process each line separately
        if (!line.empty()) {
            // Add the previous line to the wrapped text and start a new line
            wrappedStr += line + '\n';
            line.clear();
        }
        std::istringstream lineIss(word);
        while (lineIss >> word) {
            // Set theText with the current line + the next word
            theText.setString(line + (line.empty() ? "" : " ") + word);
            if (theText.getLocalBounds().width > theBox.getLocalBounds().width - 40.f) {
                // Add the current line to the wrapped text and start a new line
                wrappedStr += line + '\n';
                line = word;
            } else {
                // Continue adding words to the current line
                line += (line.empty() ? "" : " ") + word;
            }
        }
    }

    // Add the last line to the wrapped text
    wrappedStr += line;

    // Set theText with the wrapped text
    theText.setString(wrappedStr);
}

void DisplayBox::adjustTextPosition()
{
    sf::FloatRect wordBounds = word.getGlobalBounds();
    wordType.setPosition(wordType.getPosition().x, wordBounds.top + wordBounds.height + 20.f);
    sf::FloatRect wordTypeBounds = wordType.getGlobalBounds();
    wordDef.setPosition(wordDef.getPosition().x, wordTypeBounds.top + wordTypeBounds.height + 20.f);
    sf::FloatRect wordDefBounds = wordDef.getGlobalBounds();
    wordExample.setPosition(wordExample.getPosition().x, wordDefBounds.top + wordDefBounds.height + 20.f);
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
    wordExample.setString(engEngPtr->wordExample);
    wrapText(wordExample);
    // Adjust text position
    adjustTextPosition();
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
        engEngPtr = nullptr;
    }
    showNextButton = false;
    showPrevButton = false;

    word.setString("No Definitions Found!");
    wordType.setString("");
    wordDef.setString("");
    wordExample.setString("");
}

void DisplayBox::clearEngEngData()
{
    if(engEngData)
    {
        delete engEngData;
        engEngData = nullptr;
        engEngPtr = nullptr;
    }

    word.setString("");
    wordType.setString("");
    wordDef.setString("");
    wordExample.setString("");

    showNextButton = false;
    showPrevButton = false;
}

void DisplayBox::initEngVieFirstDef()
{
    word.setString(engVieData->word);

    engVieDefID = 0;
    if(!engVieData->defList[0].wordType.empty())
    {
        wordType.setString(engVieData->defList[0].wordType);
        wrapText(wordType);
    }
    else
        wordType.setString("");
    wordDef.setString(engVieData->defList[0].defAndExample.first);
    wrapText(wordDef);
    if(!engVieData->defList[0].defAndExample.second.empty())
    {
        wordExample.setString(engVieData->defList[0].defAndExample.second);
        wrapText(wordExample);
    }
    else
        wordExample.setString("");
    // Initialize the buttons
    if(engVieDefNum > 1)
        showNextButton = true;
    // Adjust text position
    adjustTextPosition();
}

void DisplayBox::showNextEngVieDef()
{
    ++engVieDefID;
    if(!engVieData->defList[engVieDefID].wordType.empty())
    {
        wordType.setString(engVieData->defList[engVieDefID].wordType);
        wrapText(wordType);
    }
    else
        wordType.setString("");
    wordDef.setString(engVieData->defList[engVieDefID].defAndExample.first);
    wrapText(wordDef);
    if(!engVieData->defList[engVieDefID].defAndExample.second.empty())
    {
        wordExample.setString(engVieData->defList[engVieDefID].defAndExample.second);
        wrapText(wordExample);
    }
    else
        wordExample.setString("");
    // Update buttons
    if(engVieDefID > 0)
        showPrevButton = true;
    if(engVieDefID == engVieDefNum-1)
        showNextButton = false;
    // Adjust text position
    adjustTextPosition();
}

void DisplayBox::showPrevEngVieDef()
{
    --engVieDefID;
    if(!engVieData->defList[engVieDefID].wordType.empty())
    {
        wordType.setString(engVieData->defList[engVieDefID].wordType);
        wrapText(wordType);
    }
    else
        wordType.setString("");
    wordDef.setString(engVieData->defList[engVieDefID].defAndExample.first);
    wrapText(wordDef);
    if(!engVieData->defList[engVieDefID].defAndExample.second.empty())
    {
        wordExample.setString(engVieData->defList[engVieDefID].defAndExample.second);
        wrapText(wordExample);
    }
    else
        wordExample.setString("");
    // Update buttons
    if(engVieDefID < engVieDefNum-1)
        showNextButton = true;
    if(engVieDefID == 0)
        showPrevButton = false;
    // Adjust text position
    adjustTextPosition();
}

void DisplayBox::showNoEngVieDefinitions()
{
    if(engVieData)
    {
        delete engVieData;
        engVieData = nullptr;
        engVieDefID = 0;
    }
    showNextButton = false;
    showPrevButton = false;
    word.setString("Khong tim thay dinh nghia!");
    wordType.setString("");
    wordDef.setString("");
    wordExample.setString("");  
}

void DisplayBox::clearEngVieData()
{
    if(engVieData)
    {
        delete engVieData;
        engVieData = nullptr;
        engVieDefID = 0;
    }
    showNextButton = false;
    showPrevButton = false;
    word.setString("");
    wordType.setString("");
    wordDef.setString("");
    wordExample.setString("");  
}

void DisplayBox::initVieEngFirstDef()
{
    word.setString(vieEngData->word);

    vieEngDefID = 0;
    if(!vieEngData->defList[0].wordType.empty())
    {
        wordType.setString(vieEngData->defList[0].wordType);
        wrapText(wordType);
    }
    else
        wordType.setString("");
    wordDef.setString(vieEngData->defList[0].defAndExample.first);
    wrapText(wordDef);
    if(!vieEngData->defList[0].defAndExample.second.empty())
    {
        wordExample.setString(vieEngData->defList[0].defAndExample.second);
        wrapText(wordExample);
    }
    else
        wordExample.setString("");
    // Initialize the buttons
    if(vieEngDefNum > 1)
        showNextButton = true;
    // Adjust text position
    adjustTextPosition();
}

void DisplayBox::showNextVieEngDef()
{
    ++vieEngDefID;
    if(!vieEngData->defList[vieEngDefID].wordType.empty())
    {
        wordType.setString(vieEngData->defList[vieEngDefID].wordType);
        wrapText(wordType);
    }
    else
        wordType.setString("");
    wordDef.setString(vieEngData->defList[vieEngDefID].defAndExample.first);
    wrapText(wordDef);
    if(!vieEngData->defList[vieEngDefID].defAndExample.second.empty())
    {
        wordExample.setString(vieEngData->defList[vieEngDefID].defAndExample.second);
        wrapText(wordExample);
    }
    else
        wordExample.setString("");
    // Update buttons
    if(vieEngDefID > 0)
        showPrevButton = true;
    if(vieEngDefID == vieEngDefNum-1)
        showNextButton = false;
    // Adjust text position
    adjustTextPosition();
}

void DisplayBox::showPrevVieEngDef()
{
    --vieEngDefID;
    if(!vieEngData->defList[vieEngDefID].wordType.empty())
    {
        wordType.setString(vieEngData->defList[vieEngDefID].wordType);
        wrapText(wordType);
    }
    else
        wordType.setString("");
    wordDef.setString(vieEngData->defList[vieEngDefID].defAndExample.first);
    wrapText(wordDef);
    if(!vieEngData->defList[vieEngDefID].defAndExample.second.empty())
    {
        wordExample.setString(vieEngData->defList[vieEngDefID].defAndExample.second);
        wrapText(wordExample);
    }
    else
        wordExample.setString("");
    // Update buttons
    if(vieEngDefID < vieEngDefNum-1)
        showNextButton = true;
    if(vieEngDefID == 0)
        showPrevButton = false;
    // Adjust text position
    adjustTextPosition();
}

void DisplayBox::showNoVieEngDefinitions()
{
    if(vieEngData)
    {
        delete vieEngData;
        vieEngData = nullptr;
        vieEngDefID = 0;
    }
    showNextButton = false;
    showPrevButton = false;
    word.setString("No Definitions Found!");
    wordType.setString("");
    wordDef.setString("");
    wordExample.setString("");  
}

void DisplayBox::clearVieEngData()
{
    if(vieEngData)
    {
        delete vieEngData;
        vieEngData = nullptr;
        engVieDefID = 0;
    }
    showNextButton = false;
    showPrevButton = false;
    word.setString("");
    wordType.setString("");
    wordDef.setString("");
    wordExample.setString("");  
}

void DisplayBox::showExistedDefinitions() {
    if (engEngData)
    {
        delete engEngData;
        engEngData = nullptr;
    }
    showNextButton = false;
    showPrevButton = false;

    word.setString("The Word Has Already Existed!");
    wordType.setString("");
    wordDef.setString("");
}

void DisplayBox::showNewDefinitions() {
    if (engEngData)
    {
        delete engEngData;
        engEngData = nullptr;
    }
    showNextButton = false;
    showPrevButton = false;

    word.setString("New Word Imported Successfully!");
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

const sf::String &DisplayBox::getWord() const
{
    return word.getString();
}

const sf::String &DisplayBox::getWordType() const
{
    return wordType.getString();
}

const sf::String &DisplayBox::getWordDef() const
{
    return wordDef.getString();
}

const sf::String &DisplayBox::getWordExample() const
{
    return wordExample.getString();
}
