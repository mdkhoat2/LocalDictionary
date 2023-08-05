
#include "WordDisplayBox.h"

WordDisplayBox::WordDisplayBox(const sf::Vector2f &pos, const sf::Vector2f &size, 
const sf::Color &backColor, const sf::Color &textColor) :
    theBox(),
    word(),
    wordType(),
    wordDef(),
    word2(),
    wordType2(),
    wordDef2(),
    showNextButton(false),
    showPrevButton(false),
    nextButtonTex(),
    nextButtonSprite(),
    prevButtonTex(),
    prevButtonSprite(),
    currentDataSetID(0),
    firstWordID(0),
    wordNum(0) 
{
    theBox.setPosition(pos);
    float xText = pos.x + 30.f;
    float yText = pos.y + 30.f;
    word.setPosition(xText, yText);
    wordType.setPosition(xText, yText + 40.f);
    wordDef.setPosition(xText, yText + 90.f);

    word2.setPosition(xText, yText + 110.f);
    wordType2.setPosition(xText, yText + 160.f);
    wordDef2.setPosition(xText, yText + 200.f);

    theBox.setSize(size);

    theBox.setFillColor(backColor);
    word.setFillColor(textColor);
    wordType.setFillColor(textColor);
    wordDef.setFillColor(textColor);

    word2.setFillColor(textColor);
    wordType2.setFillColor(textColor);
    wordDef2.setFillColor(textColor);

    word.setStyle(sf::Text::Bold);
    wordType.setStyle(sf::Text::Regular);
    wordDef.setStyle(sf::Text::Regular);

    word2.setStyle(sf::Text::Bold);
    wordType2.setStyle(sf::Text::Regular);
    wordDef2.setStyle(sf::Text::Regular);

    if(!nextButtonTex.loadFromFile("background/next-button.png"))
        std::cout << "Cannot load next button texture" << std::endl;
    nextButtonTex.setSmooth(true);

    if(!prevButtonTex.loadFromFile("background/prev-button.png"))
        std::cout << "Cannot load prev button texture" << std::endl;
    prevButtonTex.setSmooth(true);

    nextButtonSprite.setTexture(nextButtonTex);
    nextButtonSprite.setTextureRect(sf::IntRect(65, 46, 86, 85));
    nextButtonSprite.setScale(0.5f, 0.5f);

    prevButtonSprite.setTexture(prevButtonTex);
    prevButtonSprite.setTextureRect(sf::IntRect(65, 46, 86, 85));
    prevButtonSprite.setScale(0.5f, 0.5f);

    nextButtonSprite.setPosition(870, 800);
    
    showNextButton = false;

    prevButtonSprite.setPosition(100, 800);
    
    showPrevButton = false;
}

WordDisplayBox::~WordDisplayBox()
{

}

void WordDisplayBox::update(sf::RenderWindow &window)
{

}

void WordDisplayBox::drawTo(sf::RenderWindow &window)
{
    window.draw(theBox);
    window.draw(word);
    window.draw(wordType);
    window.draw(wordDef);
    window.draw(word2);
    window.draw(wordType2);
    window.draw(wordDef2);
    if(showNextButton)
        window.draw(nextButtonSprite);
    if(showPrevButton)
        window.draw(prevButtonSprite);
}

void WordDisplayBox::setPosition(const sf::Vector2f &pos)
{
    theBox.setPosition(pos);
    float xText = pos.x + 20.f;
    float yText = pos.y + 20.f;
    word.setPosition(xText, yText);
    wordType.setPosition(xText, yText + 50.f);
    wordDef.setPosition(xText, yText + 90.f);

    word2.setPosition(xText, yText + 110.f);
    wordType2.setPosition(xText, yText + 160.f);
    wordDef2.setPosition(xText, yText + 200.f);
}

void WordDisplayBox::setPosition(float xIn, float yIn)
{
    theBox.setPosition(xIn, yIn);
    float xText = xIn + 20.f;
    float yText = yIn + 20.f;
    word.setPosition(xText, yText);
    wordType.setPosition(xText, yText + 50.f);
    wordDef.setPosition(xText, yText + 90.f);

    word2.setPosition(xText, yText + 110.f);
    wordType2.setPosition(xText, yText + 160.f);
    wordDef2.setPosition(xText, yText + 200.f);
}

void WordDisplayBox::setBackColor(const sf::Color &color)
{
    theBox.setFillColor(color);
}

void WordDisplayBox::setSize(const sf::Vector2f &size)
{
    theBox.setSize(size);
}

void WordDisplayBox::setFont(const sf::Font &font)
{
    word.setFont(font);
    wordType.setFont(font);
    wordDef.setFont(font);

    word2.setFont(font);
    wordType2.setFont(font);
    wordDef2.setFont(font);
}

void WordDisplayBox::setCharacterSize(unsigned int size)
{
    word.setCharacterSize(size + 10);
    wordType.setCharacterSize(size);
    wordDef.setCharacterSize(size);

    word2.setCharacterSize(size + 10);
    wordType2.setCharacterSize(size);
    wordDef2.setCharacterSize(size);
}

void WordDisplayBox::setCurrentDataSet(int theID)
{
    currentDataSetID = theID;
}

void WordDisplayBox::clearData()
{
    for(int i = 0; i < wordArr.size(); ++i)
    {
        wordArr[i].first.clear();
        wordArr[i].second.clear();
    }
    wordArr.clear();
}

bool WordDisplayBox::isDataEmpty()
{
    return wordArr.empty();
}

void WordDisplayBox::insertDataPair(std::pair<std::string, EngVieDef> &thePair)
{
    wordArr.push_back(thePair);
}

void WordDisplayBox::wrapText(sf::Text &theText)
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
            if (theText.getLocalBounds().width > theBox.getLocalBounds().width - 30.f) {
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

void WordDisplayBox::adjustTextPosition()
{
    sf::FloatRect wordBounds1 = word.getGlobalBounds();
    wordType.setPosition(wordType.getPosition().x, wordBounds1.top + wordBounds1.height + 20.f);
    sf::FloatRect wordTypeBounds1 = wordType.getGlobalBounds();
    wordDef.setPosition(wordDef.getPosition().x, wordTypeBounds1.top + wordTypeBounds1.height + 20.f);

    sf::FloatRect wordDefBounds1 = wordDef.getGlobalBounds();
    word2.setPosition(word2.getPosition().x, wordDefBounds1.top + wordDefBounds1.height + 40.f);
    sf::FloatRect wordBounds2 = word2.getGlobalBounds();
    wordType2.setPosition(wordType2.getPosition().x, wordBounds2.top + wordBounds2.height + 20.f);
    sf::FloatRect wordTypeBounds2 = wordType2.getGlobalBounds();
    wordDef2.setPosition(wordDef2.getPosition().x, wordTypeBounds2.top + wordTypeBounds2.height + 20.f);
}

void WordDisplayBox::setUIText()
{
    // Word 1
    if(!wordArr[firstWordID].first.empty())
    {
        word.setString(wordArr[firstWordID].first);
        wrapText(word);
    }
    else
        word.setString("");
    // Word type 1
    if(!wordArr[firstWordID].second.wordType.empty())
    {
        wordType.setString(wordArr[firstWordID].second.wordType);
        wrapText(wordType);
    }
    else
        wordType.setString("");
    // Word definition 1
    if(!wordArr[firstWordID].second.defAndExample.first.empty())
    {
        wordDef.setString(wordArr[firstWordID].second.defAndExample.first);
        wrapText(wordDef);
    }
    else
        wordDef.setString("");
    
    if(firstWordID < wordNum - 1)
    {
        // Word 2
        if(!wordArr[firstWordID+1].first.empty())
        {
            word2.setString(wordArr[firstWordID+1].first);
            wrapText(word2);
        }
        else
            word2.setString("");
        // Word type 2
        if(!wordArr[firstWordID+1].second.wordType.empty())
        {
            wordType2.setString(wordArr[firstWordID+1].second.wordType);
            wrapText(wordType2);
        }
        else
            wordType2.setString("");
        // Word definition 2
        if(!wordArr[firstWordID+1].second.defAndExample.first.empty())
        {
            wordDef2.setString(wordArr[firstWordID+1].second.defAndExample.first);
            wrapText(wordDef2);
        }
        else
            wordDef2.setString("");
    }
    // There are odd number of words
    else
    {
        word2.setString("");
        wordType2.setString("");
        wordDef2.setString("");
    }

    // Adjust text position
    adjustTextPosition();
}

void WordDisplayBox::initFirstWord()
{
    wordNum = wordArr.size();
    firstWordID = 0;
    setUIText();
    if(wordNum > 2)
        showNextButton = true;

}

void WordDisplayBox::showNextWord()
{
    firstWordID += 2;
    setUIText();
    // Update buttons
    if(firstWordID >= 2)
        showPrevButton = true;
    if(firstWordID == wordNum-2 || firstWordID == wordNum-1)
        showNextButton = false;
}

void WordDisplayBox::showPrevWord()
{
    firstWordID -= 2;
    setUIText();
    // Update buttons
    if(firstWordID < wordNum-2)
        showNextButton = true;
    if(firstWordID == 0)
        showPrevButton = false;
}

void WordDisplayBox::showNoWord()
{
    clearData();
    firstWordID = 0;
    wordNum = 0;

    if(currentDataSetID == 0 || currentDataSetID == 2)
        word.setString("No words found!");
    else if(currentDataSetID == 1)
        word.setString("Khong tim thay tu phu hop!");
    wordType.setString("");
    wordDef.setString("");
    word2.setString("");
    wordType2.setString("");
    wordDef2.setString("");
}

void WordDisplayBox::clearUIText()
{
    word.setString("");
    wordType.setString("");
    wordDef.setString("");

    word2.setString("");
    wordType2.setString("");
    wordDef2.setString("");
}

bool WordDisplayBox::isMouseOverNextButton(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return nextButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool WordDisplayBox::isMouseOverPrevButton(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return prevButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool WordDisplayBox::nextButtonDrawn()
{
    return showNextButton;
}

bool WordDisplayBox::prevButtonDrawn()
{
    return showPrevButton;
}