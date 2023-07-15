#include <sstream>
#include <string>
#include "DisplayDefinition.h"

DisplayBox::DisplayBox(const sf::Vector2f& pos, const sf::Vector2f& size, 
    const sf::Color& backColor, const sf::Color& textColor) : 
    nextDefButton(nullptr),
    prevDefButton(nullptr),
    wordDefSize(15),
    wordTypeSize(25)
{
    theBox.setPosition(pos);
    float xText = pos.x + 20.f;
    float yText = pos.y + 20.f;
    definitionText.setPosition(xText, yText);
    theBox.setSize(size);
    theBox.setFillColor(backColor);
    definitionText.setFillColor(textColor);
}

DisplayBox::~DisplayBox()
{
    delete nextDefButton;
    delete prevDefButton;
    for(int i = 0; i < wordTypes.size(); ++i)
    {
        delete wordTypes[i];
    }
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < wordDefs[i].size(); ++j)
            delete wordDefs[i][j];
    }
}

void DisplayBox::setPosition(const sf::Vector2f &pos)
{
    theBox.setPosition(pos);
    float xText = pos.x + 20.f;
    float yText = pos.y + 20.f;
    definitionText.setPosition(xText, yText);
}

void DisplayBox::setPosition(float xIn, float yIn)
{
    theBox.setPosition(xIn, yIn);
    float xText = xIn + 20.f;
    float yText = yIn + 20.f;
    definitionText.setPosition(xText, yText);
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
    definitionText.setFont(font);
}

void DisplayBox::setText(const sf::String &str)
{
    definitionText.setString(str);
    wrapText();
}

void DisplayBox::setText(WordData &theWordData)
{
    for(int i = 0; i < 4; ++i)
    {
        if(theWordData.defListHead[i] == nullptr)
            continue;
        if(i == 0)
        {
            sf::Text* theWordType = new sf::Text;
            theWordType->setStyle(sf::Text::Italic | sf::Text::Bold);
            theWordType->setString("noun");
            wordTypes.push_back(theWordType);
        }
        else if(i == 1)
        {
            sf::Text* theWordType = new sf::Text;
            theWordType->setStyle(sf::Text::Italic | sf::Text::Bold);
            theWordType->setString("verb");
            wordTypes.push_back(theWordType);
        }
        else if(i == 2)
        {
            sf::Text* theWordType = new sf::Text;
            theWordType->setStyle(sf::Text::Italic | sf::Text::Bold);
            theWordType->setString("adjective");
            wordTypes.push_back(theWordType);
        }
        else
        {
            sf::Text* theWordType = new sf::Text;
            theWordType->setStyle(sf::Text::Italic | sf::Text::Bold);
            theWordType->setString("adverb");
            wordTypes.push_back(theWordType);
        }
        WordDefNode* cur = theWordData.defListHead[i];
        int count = 1;
        while(cur != nullptr)
        {
            sf::Text* theText = new sf::Text;
            std::string theString = std::to_string(count) + ". " + theWordData.defListHead[i]->wordDef;
            theText->setString(theString);
            theText->setStyle(sf::Text::Regular);
            wordDefs[i].push_back(theText);
        }
    }
}

void DisplayBox::setCharacterSize(unsigned int size)
{
    definitionText.setCharacterSize(size);
}

void DisplayBox::update(sf::RenderWindow &window)
{
    sf::Color grey(0, 0, 0, 120);
    if (isMouseOver(window)) {
		theBox.setOutlineColor(grey);
	}
    else {
		theBox.setOutlineColor(sf::Color::Transparent);
	}
}

void DisplayBox::drawTo(sf::RenderWindow &window)
{
    window.draw(theBox);
    window.draw(definitionText);
    if(nextDefButton)
        nextDefButton->drawTo(window);
    if(prevDefButton)
        prevDefButton->drawTo(window);
}

bool DisplayBox::isMouseOver(sf::RenderWindow &window)
{
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;

    int btnPosX = theBox.getPosition().x;
    int btnPosY = theBox.getPosition().y;

    int btnxPosWidth = theBox.getPosition().x + theBox.getSize().x;
    int btnyPosHeight = theBox.getPosition().y + theBox.getSize().y;

    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        return true;
    }
    return false;
}

void DisplayBox::showNextDefButton()
{
    if(!nextDefButton)
        nextDefButton = new Button("NEXT", {20, 20}, 14, sf::Color::Green, sf::Color::White);
    
}

void DisplayBox::showPrevDefButton()
{
    if(!prevDefButton)
        prevDefButton = new Button("NEXT", {20, 20}, 14, sf::Color::Green, sf::Color::White);
}

void DisplayBox::wrapText()
{
    std::string str = definitionText.getString();
    std::string wrappedStr;
    unsigned int charSize = definitionText.getCharacterSize();

    std::string word;
    std::istringstream iss(str);
    std::string line;
    definitionText.setString("");

    while (iss >> word) {
        definitionText.setString(line + " " + word);
        if (definitionText.getLocalBounds().width > theBox.getLocalBounds().width - 40.f) {
            wrappedStr += line + '\n';
            line = word;
        } else {
            line += (line.empty() ? "" : " ") + word;
        }
    }

    wrappedStr += line;
    definitionText.setString(wrappedStr);
}
