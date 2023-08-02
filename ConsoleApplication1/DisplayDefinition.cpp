#include <sstream>
#include <fstream>
#include <string>
#include "DisplayDefinition.h"

DisplayBox::DisplayBox(const sf::Vector2f& pos, const sf::Vector2f& size, 
    const sf::Color& backColor, const sf::Color& textColor) : 
    theBox(),
    word(),
    wordType(),
    wordDef(),
    wordExample(),
    engVieData(nullptr),
    engVieDefID(0),
    engVieDefNum(0),
    vieEngData(nullptr),
    vieEngDefID(0),
    vieEngDefNum(0),
    showNextButton(false),
    showPrevButton(false),
    emojiDefinition(false),
    nextButtonTex(),
    prevButtonTex(),
    nextButtonSprite(),
    prevButtonSprite(),
    EEData(nullptr),
    EEDefID(0),
    EEDefNum(0),
    currentDataSetID(0)
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
    nextButtonSprite.setTextureRect(sf::IntRect(65, 46, 86, 85));
    nextButtonSprite.setScale(0.5f, 0.5f);

    prevButtonSprite.setTexture(prevButtonTex);
    prevButtonSprite.setTextureRect(sf::IntRect(65, 46, 86, 85));
    prevButtonSprite.setScale(0.5f, 0.5f);

    nextButtonSprite.setPosition(870, 800);
    
    showNextButton = false;

    prevButtonSprite.setPosition(100, 800);
    
    showPrevButton = false;
    //Font.loadFromFile("font/seguiemj.ttf"); //this font is Windows 10 default font for emoji
    //setEmoji();
}

DisplayBox::~DisplayBox()
{
    delete EEData;
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
    if (emojiDefinition==true)
    {
       // emojiDefinition = false;
        window.draw(emojiImage);
    }
    if(showNextButton)
    {
        window.draw(nextButtonSprite);
    }
        
    if(showPrevButton)
    {
        window.draw(prevButtonSprite);
    }
        
}

void DisplayBox::getWordDataEngEng(std::string &inputWord, int& wordIndex, std::vector<WordDataEngVie>& engEngVector)
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
    if(EEData == nullptr)
    {
        EEData = new WordDataEngVie;
        EEData->word = engEngVector[wordIndex].word;
        for(int i = 0; i < engEngVector[wordIndex].defList.size(); ++i)
        {
            EEData->defList.push_back(engEngVector[wordIndex].defList[i]);
        }
    }
    else
    {
        delete EEData;
        showNextButton = false;
        showPrevButton = false;
        EEData = new WordDataEngVie;
        EEData->word = engEngVector[wordIndex].word;
        for(int i = 0; i < engEngVector[wordIndex].defList.size(); ++i)
        {
            EEData->defList.push_back(engEngVector[wordIndex].defList[i]);
        }
    }
    // Check if the word has any edited definition(s)
    loadEditFromFile(*EEData, 0);
    EEDefNum = EEData->defList.size();
    initEngEngFirstDef();
}

void DisplayBox::getWordDataEngVie(std::string& inputWord, int& wordIndex, std::vector<WordDataEngVie>& engVieVector)
{
    // delete old data of other data sets
    if(EEData)
    {
        delete EEData;
        EEData = nullptr;
    }
    if(vieEngData)
    {
        delete vieEngData;
        vieEngData = nullptr;
    }
    if(engVieData == nullptr)
    {
        engVieData = new WordDataEngVie;
        engVieData->word = engVieVector[wordIndex].word;
        for(int i = 0; i < engVieVector[wordIndex].defList.size(); ++i)
        {
            engVieData->defList.push_back(engVieVector[wordIndex].defList[i]);
        }
    }
    else // delete old word data
    {
        delete engVieData;
        showNextButton = false;
        showPrevButton = false;
        engVieData = new WordDataEngVie;
        engVieData->word = engVieVector[wordIndex].word;
        for(int i = 0; i < engVieVector[wordIndex].defList.size(); ++i)
        {
            engVieData->defList.push_back(engVieVector[wordIndex].defList[i]);
        }
    }
    loadEditFromFile(*engVieData, 1);
    engVieDefNum = engVieData->defList.size();
    initEngVieFirstDef();
}

void DisplayBox::getWordDataVieEng(std::string& inputWord, int& wordIndex, std::vector<WordDataEngVie>& vieEngVector)
{
    // delete old data of other data sets
    if(EEData)
    {
        delete EEData;
        EEData = nullptr;
    }
    if(engVieData)
    {
        delete engVieData;
        engVieData = nullptr;
    }
    if(vieEngData == nullptr)
    {
        vieEngData = new WordDataEngVie;
        vieEngData->word = vieEngVector[wordIndex].word;
        for(int i = 0; i < vieEngVector[wordIndex].defList.size(); ++i)
        {
            vieEngData->defList.push_back(vieEngVector[wordIndex].defList[i]);
        }
    }
    else // delete old word data
    {
        delete vieEngData;
        showNextButton = false;
        showPrevButton = false;
        vieEngData = new WordDataEngVie;
        vieEngData->word = vieEngVector[wordIndex].word;
        for(int i = 0; i < vieEngVector[wordIndex].defList.size(); ++i)
        {
            vieEngData->defList.push_back(vieEngVector[wordIndex].defList[i]);
        }
    }
    loadEditFromFile(*vieEngData, 2);
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

void DisplayBox::adjustTextPosition()
{
    sf::FloatRect wordBounds = word.getGlobalBounds();
    wordType.setPosition(wordType.getPosition().x, wordBounds.top + wordBounds.height + 20.f);
    sf::FloatRect wordTypeBounds = wordType.getGlobalBounds();
    wordDef.setPosition(wordDef.getPosition().x, wordTypeBounds.top + wordTypeBounds.height + 20.f);
    sf::FloatRect wordDefBounds = wordDef.getGlobalBounds();
    wordExample.setPosition(wordExample.getPosition().x, wordDefBounds.top + wordDefBounds.height + 20.f);
}

void DisplayBox::setCurrentDataSet(int theID)
{
    currentDataSetID = theID;
}

void DisplayBox::initEngEngFirstDef()
{
    word.setString(EEData->word);
    EEDefID = 0;
    setEngEngUIText();
    // Initialize the buttons
    if(EEDefNum > 1)
        showNextButton = true;
}

void DisplayBox::showNextEngEngDef()
{
    ++EEDefID;
    setEngEngUIText();
    // Update buttons
    if(EEDefID > 0)
        showPrevButton = true;
    if(EEDefID == EEDefNum-1)
        showNextButton = false;
}

void DisplayBox::showPrevEngEngDef()
{
    --EEDefID;
    setEngEngUIText();
    // Update buttons
    if(EEDefID < EEDefNum-1)
        showNextButton = true;
    if(EEDefID == 0)
        showPrevButton = false;
}

void DisplayBox::showNoEngEngDefinitions()
{
    if(EEData)
    {
        delete EEData;
        EEData = nullptr;
        EEDefID = 0;
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
    if(EEData)
    {
        delete EEData;
        EEData = nullptr;
        EEDefID = 0;
    }

    word.setString("");
    wordType.setString("");
    wordDef.setString("");
    wordExample.setString("");

    showNextButton = false;
    showPrevButton = false;
}

void DisplayBox::setEngEngUIText()
{
    if(!EEData->defList[EEDefID].wordType.empty())
    {
        wordType.setString(EEData->defList[EEDefID].wordType);
        wrapText(wordType);
    }
    else
        wordType.setString("");
    wordDef.setString(EEData->defList[EEDefID].defAndExample.first);
    wrapText(wordDef);
    if(!EEData->defList[EEDefID].defAndExample.second.empty())
    {
        wordExample.setString(EEData->defList[EEDefID].defAndExample.second);
        wrapText(wordExample);
    }
    else
        wordExample.setString("");
    // Adjust text position
    adjustTextPosition();
}

void DisplayBox::initEngVieFirstDef()
{
    word.setString(engVieData->word);

    engVieDefID = 0;
    setEngVieUIText();
    // Initialize the buttons
    if(engVieDefNum > 1)
        showNextButton = true;
}

void DisplayBox::showNextEngVieDef()
{
    ++engVieDefID;
    setEngVieUIText();
    // Update buttons
    if(engVieDefID > 0)
        showPrevButton = true;
    if(engVieDefID == engVieDefNum-1)
        showNextButton = false;
}

void DisplayBox::showPrevEngVieDef()
{
    --engVieDefID;
    setEngVieUIText();
    // Update buttons
    if(engVieDefID < engVieDefNum-1)
        showNextButton = true;
    if(engVieDefID == 0)
        showPrevButton = false;
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

void DisplayBox::setEngVieUIText()
{
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
    // Adjust text position
    adjustTextPosition();
}

void DisplayBox::initVieEngFirstDef()
{
    word.setString(vieEngData->word);

    vieEngDefID = 0;
    setVieEngUIText();
    // Initialize the buttons
    if(vieEngDefNum > 1)
        showNextButton = true;
}

void DisplayBox::showNextVieEngDef()
{
    ++vieEngDefID;
    setVieEngUIText();
    // Update buttons
    if(vieEngDefID > 0)
        showPrevButton = true;
    if(vieEngDefID == vieEngDefNum-1)
        showNextButton = false;
}

void DisplayBox::showPrevVieEngDef()
{
    --vieEngDefID;
    setVieEngUIText();
    // Update buttons
    if(vieEngDefID < vieEngDefNum-1)
        showNextButton = true;
    if(vieEngDefID == 0)
        showPrevButton = false;
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
        vieEngDefID = 0;
    }
    showNextButton = false;
    showPrevButton = false;
    word.setString("");
    wordType.setString("");
    wordDef.setString("");
    wordExample.setString("");  
}

void DisplayBox::setVieEngUIText()
{
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
    // Adjust text position
    adjustTextPosition();
}

void DisplayBox::showExistedDefinitions() {
    if (EEData)
    {
        delete EEData;
        EEData = nullptr;
    }
    showNextButton = false;
    showPrevButton = false;

    word.setString("The Word Has Already Existed!");
    wordType.setString("");
    wordDef.setString("");
}

void DisplayBox::showNewDefinitions() {
    if (EEData)
    {
        delete EEData;
        EEData = nullptr;
    }
    showNextButton = false;
    showPrevButton = false;

    word.setString("New Word Imported Successfully!");
    wordType.setString("");
    wordDef.setString("");
}

void DisplayBox::showDeletionReConfirmation() {
    if (EEData)
    {
        delete EEData;
        EEData = nullptr;
    }
    showNextButton = false;
    showPrevButton = false;

    word.setString("Are you sure to delete this word?");
    wordType.setString("");
    wordDef.setString("");
}

void DisplayBox::showDeleteSuccessfully() {
    if (EEData)
    {
        delete EEData;
        EEData = nullptr;
    }
    showNextButton = false;
    showPrevButton = false;

    word.setString("Delete Successfully!");
    wordType.setString("");
    wordDef.setString("");
}

void DisplayBox::showCancelSuccessfully() {
    if (EEData)
    {
        delete EEData;
        EEData = nullptr;
    }
    showNextButton = false;
    showPrevButton = false;

    word.setString("Action Cancelled");
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

void DisplayBox::setNextButtonPos(float xIn, float yIn)
{
    nextButtonSprite.setPosition(xIn, yIn);
}

void DisplayBox::setPrevButtonPos(float xIn, float yIn)
{
    prevButtonSprite.setPosition(xIn, yIn);
}

sf::Vector2u DisplayBox::getNextButtonTexSize() const
{
    return nextButtonTex.getSize();
}

sf::Vector2u DisplayBox::getPrevButtonTexSize() const
{
    return prevButtonTex.getSize();
}

const sf::Vector2f &DisplayBox::getNextButtonScale() const
{
    return nextButtonSprite.getScale();
}

const sf::Vector2f &DisplayBox::getPrevButtonScale() const
{
    return prevButtonSprite.getScale();
}

void DisplayBox::showEmojiDefinition(std::string& inputWord, int& emojiIndex, std::vector<std::string>& emojiVector)
{
    std::string wordInfor = emojiVector[emojiIndex];
    std::string emoji = "0x"+ wordInfor;
    std::string imagePath = wordInfor;
    for (int i = 0; i < imagePath.length(); i++)
    {
        if (imagePath[i] == ' ')imagePath[i] = '-';
        else imagePath[i] = tolower(imagePath[i]);
    }
    if (!emojiTexture.loadFromFile("data/images/"+imagePath+".png"))
    {
        showNoEmojiDefinition();
    }
    emojiTexture.setSmooth(true);
    emojiImage.setTexture(emojiTexture);
    emojiImage.setScale(sf::Vector2f(175.f / emojiTexture.getSize().x, 175.f / emojiTexture.getSize().y));
    emojiImage.setPosition(130, 300);
    std::string word1 = inputWord;
    for (int i = 0; i < word1.length(); i++)
    {
        word1[i] = tolower(word1[i]);
    }
    word.setString(word1);
}
void DisplayBox::clearEmoji()
{
    emojiDefinition = false;
    word.setString("");
}
void DisplayBox::setEmojiMode(bool value)
{
    emojiDefinition = value;
}
bool DisplayBox::getEmojiMode()
{
    return emojiDefinition;
}
void DisplayBox::showNoEmojiDefinition()
{
    word.setString("No emoji matches this definition.");
    wordType.setString("");
    wordDef.setString("");
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

void DisplayBox::receiveEditText(std::string &editWordType, std::string &editWordDef, std::string &editWordExample)
{
    // Change current word data and UI text
    // Remove '\n' characters due to word-wrapping
    removeEndLineInString(editWordDef);
    if(currentDataSetID == 0)
    {
        EEData->defList[EEDefID].wordType = editWordType;
        EEData->defList[EEDefID].defAndExample.first = editWordDef;
        EEData->defList[EEDefID].defAndExample.second = editWordExample;
        EEData->defList[EEDefID].isEdited = true;
        setEngEngUIText();
        saveEditToFile(*EEData, currentDataSetID);
    }
    else if(currentDataSetID == 1)
    {
        engVieData->defList[engVieDefID].wordType = editWordType;
        engVieData->defList[engVieDefID].defAndExample.first = editWordDef;
        engVieData->defList[engVieDefID].defAndExample.second = editWordExample;
        engVieData->defList[engVieDefID].isEdited = true;
        saveEditToFile(*engVieData, currentDataSetID);
        setEngVieUIText();
    }
    else if(currentDataSetID == 2)
    {
        vieEngData->defList[vieEngDefID].wordType = editWordType;
        vieEngData->defList[vieEngDefID].defAndExample.first = editWordDef;
        vieEngData->defList[vieEngDefID].defAndExample.second = editWordExample;
        vieEngData->defList[vieEngDefID].isEdited = true;
        saveEditToFile(*vieEngData, currentDataSetID);
        setVieEngUIText();
    }
}
