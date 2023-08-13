
#include "EditBox.h"

EditBox::EditBox(const sf::Vector2f& pos, const sf::Vector2f& size, 
    const sf::Color& backColor, const sf::Color& textColor) :
    theBox(),
    word(),
    wordTypeArea(25, sf::Color::Black, sf::Color::Transparent, false),
    wordDefArea(25, sf::Color::Black, sf::Color::Transparent, false),
    wordExampleArea(25, sf::Color::Black, sf::Color::Transparent, false),
    wordTypePlaceholder(),
    wordDefPlaceholder(),
    wordExamplePlaceholder()
{
    theBox.setPosition(pos);
    float xText = pos.x + 30.f;
    float yText = pos.y + 30.f;
    word.setPosition(xText, yText);
    wordTypeArea.setPosition(xText, yText + 40.f);
    wordDefArea.setPosition(xText, yText + 90.f);
    wordExampleArea.setPosition(xText, yText + 250.f);

    theBox.setSize(size);

    theBox.setFillColor(backColor);
    word.setFillColor(textColor);
    wordTypeArea.setTextColor(textColor);
    wordDefArea.setTextColor(textColor);
    wordExampleArea.setTextColor(sf::Color(128, 128, 128));

    word.setStyle(sf::Text::Bold);
    wordTypeArea.setStyle(sf::Text::Regular);
    wordDefArea.setStyle(sf::Text::Regular);
    wordExampleArea.setStyle(sf::Text::Regular);

    wordTypePlaceholder.setFillColor(sf::Color(128, 128, 128));
    wordTypePlaceholder.setString("Enter word type...");
    wordTypePlaceholder.setCharacterSize(25);

    wordDefPlaceholder.setFillColor(sf::Color(128, 128, 128));
    wordDefPlaceholder.setString("Enter definition...");
    wordDefPlaceholder.setCharacterSize(25);

    wordExamplePlaceholder.setFillColor(sf::Color(128, 128, 128));
    wordExamplePlaceholder.setString("Enter example...");
    wordExamplePlaceholder.setCharacterSize(25);
}

void EditBox::update(sf::RenderWindow &window)
{

}

void EditBox::drawTo(sf::RenderWindow &window)
{
    window.draw(theBox);
    std::string wordStr = word.getString();
    if(!wordStr.empty())
    {
        window.draw(word);
        adjustTextPosition();
        adjustSurroundingTextbox();
        wordTypeArea.drawTo(window);
        wordDefArea.drawTo(window);
        wordExampleArea.drawTo(window);

        if(wordTypeArea.getText().empty())
            window.draw(wordTypePlaceholder);
        if(wordDefArea.getText().empty())
            window.draw(wordDefPlaceholder);
        if(wordExampleArea.getText().empty())
            window.draw(wordExamplePlaceholder);
    }
}

void EditBox::setFont(const sf::Font &font)
{
    word.setFont(font);
    wordTypeArea.setFont(font);
    wordDefArea.setFont(font);
    wordExampleArea.setFont(font);

    wordTypePlaceholder.setFont(font);
    wordDefPlaceholder.setFont(font);
    wordExamplePlaceholder.setFont(font);
}

void EditBox::setPosition(float xIn, float yIn)
{
    theBox.setPosition(xIn, yIn);
    float xText = xIn + 30.f;
    float yText = yIn + 30.f;
    word.setPosition(xText, yText);

    wordTypeArea.setBoxPosition(xIn, yIn + 40.f);
    wordTypeArea.setPosition(xText, yText + 40.f);
    
    wordDefArea.setBoxPosition(xIn, yIn + 90.f);
    wordDefArea.setPosition(xText, yText + 90.f);

    wordExampleArea.setBoxPosition(xIn, yIn + 250.f);
    wordExampleArea.setPosition(xText, yText + 250.f);
}

void EditBox::setBackColor(const sf::Color &color)
{
    theBox.setFillColor(color);
}

void EditBox::setSize(const sf::Vector2f &size)
{
    theBox.setSize(size);
}

void EditBox::setCharacterSize(unsigned int size)
{
    word.setCharacterSize(size + 10);
    wordTypeArea.setCharacterSize(size);
    wordDefArea.setCharacterSize(size);
    wordExampleArea.setCharacterSize(size);

    wordTypePlaceholder.setCharacterSize(size);
    wordDefPlaceholder.setCharacterSize(size);
    wordExamplePlaceholder.setCharacterSize(size);
}

void EditBox::wrapText(sf::Text &theText)
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

void EditBox::adjustTextPosition()
{
    // Spacing between word and word type
    sf::FloatRect wordBounds = word.getGlobalBounds();
    wordTypeArea.setPosition(wordTypeArea.getTextPosition().x, wordBounds.top + wordBounds.height + 20.f);
    wordTypePlaceholder.setPosition(wordTypeArea.getTextPosition().x + 5.f, wordBounds.top + wordBounds.height + 20.f);

    // Spacing between word type and word definition
    sf::FloatRect wordTypeBounds = wordTypeArea.getGlobalBounds();
    if(!wordTypeArea.getText().empty())
    {
        wordDefArea.setPosition(wordDefArea.getTextPosition().x, wordTypeBounds.top + wordTypeBounds.height + 40.f);
        wordDefPlaceholder.setPosition(wordDefArea.getTextPosition().x + 5.f, wordTypeBounds.top + wordTypeBounds.height + 40.f);
    }
    else
    {
        wordDefArea.setPosition(wordDefArea.getTextPosition().x, wordTypeArea.getBoxPosition().y + wordTypeArea.getBoxSize().y + 40.f);
        wordDefPlaceholder.setPosition(wordDefArea.getTextPosition().x + 5.f, wordTypeArea.getBoxPosition().y + wordTypeArea.getBoxSize().y + 40.f);
    }

    // Spacing between word definition and word example
    sf::FloatRect wordDefBounds = wordDefArea.getGlobalBounds();
    if(!wordDefArea.getText().empty())
    {
        wordExampleArea.setPosition(wordExampleArea.getTextPosition().x, wordDefBounds.top + wordDefBounds.height + 40.f);
        wordExamplePlaceholder.setPosition(wordExampleArea.getTextPosition().x + 5.f, wordDefBounds.top + wordDefBounds.height + 40.f);
    }
    else
    {
        wordExampleArea.setPosition(wordExampleArea.getTextPosition().x, wordDefArea.getBoxPosition().y + wordDefArea.getBoxSize().y + 40.f);
        wordExamplePlaceholder.setPosition(wordExampleArea.getTextPosition().x + 5.f, wordDefArea.getBoxPosition().y + wordDefArea.getBoxSize().y + 40.f);
    }
}

void EditBox::initTextToEdit(const sf::String &theWord, const sf::String &theWordType, const sf::String &theWordDef, const sf::String &theWordExample)
{
    word.setString(theWord);
    wordTypeArea.setText(theWordType);
    if(theWordDef != "(Choose 'edit definition' to add a new definition!)"
    && theWordDef != "- (This definition has been deleted!)")
        wordDefArea.setText(theWordDef);
    else
        wordDefArea.setText("");
    // Do not get the text "Example:" because it is just for display
    if(isPrefix("Example:\n", theWordExample))
        wordExampleArea.setText(theWordExample.substring(9));
}

void EditBox::adjustSurroundingTextbox()
{
    // Word type
    sf::FloatRect wordBounds = word.getGlobalBounds();
    std::string typeText = wordTypeArea.getText();
    if(!typeText.empty())
        wordTypeArea.setBoxSize(sf::Vector2f(theBox.getSize().x - 25, wordBounds.height + 14));
    else
        wordTypeArea.setBoxSize(sf::Vector2f(theBox.getSize().x - 25, 40));
    wordTypeArea.setOutlineColor(sf::Color::Black);
    wordTypeArea.setOutlineThickness(2.0f);
    wordTypeArea.setBoxPosition(wordTypeArea.getTextPosition().x - 5, wordTypeArea.getTextPosition().y - 5);
    // Word definition
    sf::FloatRect wordDefBounds = wordDefArea.getGlobalBounds();
    std::string defText = wordDefArea.getText();
    if(!defText.empty())
        wordDefArea.setBoxSize(sf::Vector2f(theBox.getSize().x - 25, wordDefBounds.height + 14));
    else
        wordDefArea.setBoxSize(sf::Vector2f(theBox.getSize().x - 25, 40));
    wordDefArea.setOutlineColor(sf::Color::Black);
    wordDefArea.setOutlineThickness(2.0f);
    wordDefArea.setBoxPosition(wordDefArea.getTextPosition().x - 5, wordDefArea.getTextPosition().y - 5);
    // Word example
    sf::FloatRect wordExampleBounds = wordExampleArea.getGlobalBounds();
    std::string exampleText = wordExampleArea.getText();
    if(!exampleText.empty())
        wordExampleArea.setBoxSize(sf::Vector2f(theBox.getSize().x - 25, wordExampleBounds.height + 14));
    else
        wordExampleArea.setBoxSize(sf::Vector2f(theBox.getSize().x - 25, 40));
    wordExampleArea.setOutlineColor(sf::Color::Black);
    wordExampleArea.setOutlineThickness(2.0f);
    wordExampleArea.setBoxPosition(wordExampleArea.getTextPosition().x - 5, wordExampleArea.getTextPosition().y - 5);
}

bool EditBox::isMouseOverWordTypeArea(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return wordTypeArea.getBoxGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool EditBox::isMouseOverWordDefArea(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return wordDefArea.getBoxGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool EditBox::isMouseOverWordExampleArea(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return wordExampleArea.getBoxGlobalBounds().contains(mousePos.x, mousePos.y);
}

void EditBox::setSelectedWordTypeArea(bool val)
{
    wordTypeArea.setSelected(val);
}

void EditBox::setSelectedWordDefArea(bool val)
{
    wordDefArea.setSelected(val);
}

void EditBox::setSelectedWordExampleArea(bool val)
{
    wordExampleArea.setSelected(val);
}

bool EditBox::isWordTypeAreaSelected()
{
    return wordTypeArea.isSelect();
}

bool EditBox::isWordDefAreaSelected()
{
    return wordDefArea.isSelect();
}

bool EditBox::isWordExampleAreaSelected()
{
    return wordExampleArea.isSelect();
}

void EditBox::wordTypeAreaTypedOn(sf::Event input)
{
    wordTypeArea.typedOn(input);
}

void EditBox::wordDefAreaTypedOn(sf::Event input)
{
    wordDefArea.typedOn(input);
}

void EditBox::wordExampleAreaTypedOn(sf::Event input)
{
    wordExampleArea.typedOn(input);
}

std::string EditBox::getWordType()
{
    return wordTypeArea.getText();
}

std::string EditBox::getWordDef()
{
    return wordDefArea.getText();
}

std::string EditBox::getWordExample()
{
    return wordExampleArea.getText();
}

const sf::Vector2f &EditBox::getPosition() const
{
    return theBox.getPosition();
}

const sf::Vector2f &EditBox::getSize() const
{
    return theBox.getSize();
}