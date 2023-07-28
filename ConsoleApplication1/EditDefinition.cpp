#include <iostream>
#include "EditDefinition.h"

EditDefinitionScreen::EditDefinitionScreen(sf::Font& font, sf::Font& font2, sf::Sprite& background) : 
    isEndScreen(false),
    currentDataSetID(0),
    currentEditAreaID(0),
    cancelButtonTex(),
    cancelButton(),
    saveButtonTex(),
    saveButton(),
    saveSucceededTex(),
    saveSucceeded(),
    showSucceeded(false),
    clock(),
    succeededTimeMax(),
    dataSetButton("      EN - EN", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Black),
    editBox({ 72, 250 }, { 850, 600 }, sf::Color::Transparent, sf::Color::Black),
    cancelButtonHover("", {170.1f, 47.1f}, 20, sf::Color::Transparent, sf::Color::Transparent),
    saveButtonHover("", {170.1f, 47.1f}, 20, sf::Color::Transparent, sf::Color::Transparent)
{
    initCancelButton(font);
    initDataSetButton(font);
    initSaveButton(font);
    initEditBox(font2, background);
    initSaveSucceeded(font);
    succeededTimeMax = sf::seconds(2.0f);
}

void EditDefinitionScreen::handleEvent(sf::Event event, sf::RenderWindow &window, bool& endScreen)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(isMouseOverCancelButton(window))
        {
            endScreen = true;
            isEndScreen = endScreen;
        }

        if(isMouseOverSaveButton(window))
        {
            showSucceeded = true;
            clock.restart();
        }

        if(editBox.isMouseOverWordTypeArea(window))
        {
            currentEditAreaID = 0;
            editBox.setSelectedWordTypeArea(true);
        }
        else
            editBox.setSelectedWordTypeArea(false);

        if(editBox.isMouseOverWordDefArea(window))
        {
            currentEditAreaID = 1;
            editBox.setSelectedWordDefArea(true);
        }
        else
            editBox.setSelectedWordDefArea(false);

        if(editBox.isMouseOverWordExampleArea(window))
        {
            currentEditAreaID = 2;
            editBox.setSelectedWordExampleArea(true);
        }            
        else
            editBox.setSelectedWordExampleArea(false);

        
    }
    else if(event.type == sf::Event::TextEntered)
    {
        if(currentEditAreaID == 0 && editBox.isWordTypeAreaSelected())
        {
            editBox.wordTypeAreaTypedOn(event);
        }
        else if(currentEditAreaID == 1 && editBox.isWordDefAreaSelected())
        {
            editBox.wordDefAreaTypedOn(event);
        }
        else if(currentEditAreaID == 2 && editBox.isWordExampleAreaSelected())
        {
            editBox.wordExampleAreaTypedOn(event);
        }
    }
}

void EditDefinitionScreen::update(sf::RenderWindow& window, bool& endScreen, bool& isSaved
, std::string& editWordType, std::string& editWordDef, std::string& editWordExample)
{
    dataSetButton.update(window);
    sf::Color grey(0, 0, 0, 120);
    if(isMouseOverCancelButton(window))
        cancelButtonHover.setOutlineColor(grey);

    else
        cancelButtonHover.setOutlineColor(sf::Color::Transparent);
    if(isMouseOverSaveButton(window))
        saveButtonHover.setOutlineColor(grey);
    else
        saveButtonHover.setOutlineColor(sf::Color::Transparent);

    if(showSucceeded)
    {
        if(clock.getElapsedTime() >= succeededTimeMax)
        {
            showSucceeded = false;
            editWordType = editBox.getWordType();
            editWordDef = editBox.getWordDef();
            editWordExample = editBox.getWordExample();
            endScreen = true;
            isSaved = true;
            isEndScreen = endScreen;
        }
     
    }
}

void EditDefinitionScreen::render(sf::RenderWindow &window, sf::Sprite& background)
{
    if(!isEndScreen && !showSucceeded)
    {
        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(cancelButton);
        window.draw(saveButton);
        cancelButtonHover.drawTo(window);
        saveButtonHover.drawTo(window);
        dataSetButton.drawTo(window);
        editBox.drawTo(window);
    }
    if(showSucceeded)
    {
        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(cancelButton);
        window.draw(saveButton);
        cancelButtonHover.drawTo(window);
        saveButtonHover.drawTo(window);
        dataSetButton.drawTo(window);
        window.draw(saveSucceeded);
    }
}

void EditDefinitionScreen::setEndScreen(bool value)
{
    isEndScreen = value;
}

void EditDefinitionScreen::setCurrentDataSetID(int theID)
{
    currentDataSetID = theID;
}

bool EditDefinitionScreen::isMouseOverCancelButton(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return cancelButton.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool EditDefinitionScreen::isMouseOverSaveButton(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return saveButton.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void EditDefinitionScreen::initTextToEdit(const sf::String &theWord, const sf::String &theWordType, const sf::String &theWordDef, const sf::String &theWordExample)
{
    editBox.initTextToEdit(theWord, theWordType, theWordDef, theWordExample);
}

std::string EditDefinitionScreen::getEditWordType()
{
    return editBox.getWordType();
}

std::string EditDefinitionScreen::getEditWordDef()
{
    return editBox.getWordDef();
}

std::string EditDefinitionScreen::getEditWordExample()
{
    return editBox.getWordExample();
}

void EditDefinitionScreen::initCancelButton(const sf::Font &font)
{
    // Cancel button
    if(!cancelButtonTex.loadFromFile("background/cancel-button.png"))
        std::cout << "Cannot load cancel button texture\n";
    cancelButtonTex.setSmooth(true);
    cancelButton.setTexture(cancelButtonTex);
    cancelButton.setScale(0.3f, 0.3f);
    cancelButton.setPosition(530, 760);
    // Cancel button hover
    cancelButtonHover.setPosition(cancelButton.getPosition().x + 16.8f, cancelButton.getPosition().y + 16.8f);
    cancelButtonHover.setOutlineThickness(2);
}

void EditDefinitionScreen::initSaveButton(const sf::Font &font)
{
    // Save button
    if(!saveButtonTex.loadFromFile("background/save-button.png"))
        std::cout << "Cannot load save button texture\n";
    saveButtonTex.setSmooth(true);
    saveButton.setTexture(saveButtonTex);
    saveButton.setScale(0.3f, 0.3f);
    saveButton.setPosition(280, 760);
    // Save button hover
    saveButtonHover.setPosition(saveButton.getPosition().x + 16.8f, saveButton.getPosition().y + 16.8f);
    saveButtonHover.setOutlineThickness(2);
}

void EditDefinitionScreen::initDataSetButton(const sf::Font &font)
{
    // Data set button
    dataSetButton.setFont(font);
	dataSetButton.setPosition({ 972, 72 });
	dataSetButton.setOutlineThickness(2);
	dataSetButton.setStyle(sf::Text::Style::Bold);
    if (currentDataSetID == 0)
		dataSetButton.setString("      EN - EN");
	else if (currentDataSetID == 1)
		dataSetButton.setString("      EN - VI");
	else if (currentDataSetID == 2)
		dataSetButton.setString("      VI - EN");
	else
		dataSetButton.setString("      Emoji");
}

void EditDefinitionScreen::initEditBox(const sf::Font &font, sf::Sprite& background)
{
    float scaleX = background.getScale().x;
    float scaleY = background.getScale().y;
    editBox.setPosition(247 * scaleX, 842 * scaleY);
    editBox.setSize(sf::Vector2f(2887 * scaleX, 2019 * scaleY));
    editBox.setFont(font);
    editBox.setCharacterSize(25);
}

void EditDefinitionScreen::initSaveSucceeded(const sf::Font &font)
{
    if(!saveSucceededTex.loadFromFile("background/succeeded.png"))
        std::cout << "Cannot load texture succeeded from file" << std::endl;
    saveSucceededTex.setSmooth(true);
    saveSucceeded.setTexture(saveSucceededTex);
    saveSucceeded.setScale(0.3f, 0.3f);
    saveSucceeded.setPosition(290, 450);
}

/*------------------------EDIT BOX-------------------------*/
EditBox::EditBox(const sf::Vector2f& pos, const sf::Vector2f& size, 
    const sf::Color& backColor, const sf::Color& textColor) :
    theBox(),
    word(),
    wordTypeArea(25, sf::Color::Black, sf::Color::Transparent, false),
    wordDefArea(25, sf::Color::Black, sf::Color::Transparent, false),
    wordExampleArea(25, sf::Color::Black, sf::Color::Transparent, false)
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
    }
}

void EditBox::setFont(const sf::Font &font)
{
    word.setFont(font);
    wordTypeArea.setFont(font);
    wordDefArea.setFont(font);
    wordExampleArea.setFont(font);
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

void EditBox::adjustTextPosition()
{
    sf::FloatRect wordBounds = word.getGlobalBounds();
    wordTypeArea.setPosition(wordTypeArea.getTextPosition().x, wordBounds.top + wordBounds.height + 20.f);
    sf::FloatRect wordTypeBounds = wordTypeArea.getGlobalBounds();
    wordDefArea.setPosition(wordDefArea.getTextPosition().x, wordTypeBounds.top + wordTypeBounds.height + 20.f);
    sf::FloatRect wordDefBounds = wordDefArea.getGlobalBounds();
    wordExampleArea.setPosition(wordExampleArea.getTextPosition().x, wordDefBounds.top + wordDefBounds.height + 20.f);
}

void EditBox::initTextToEdit(const sf::String &theWord, const sf::String &theWordType, const sf::String &theWordDef, const sf::String &theWordExample)
{
    word.setString(theWord);
    wordTypeArea.setText(theWordType);
    wordDefArea.setText(theWordDef);
    wordExampleArea.setText(theWordExample);
}

void EditBox::adjustSurroundingTextbox()
{
    // Word type
    sf::FloatRect wordTypeBounds = word.getGlobalBounds();
    wordTypeArea.setBoxSize(sf::Vector2f(theBox.getSize().x - 25, wordTypeBounds.height + 10));
    wordTypeArea.setOutlineColor(sf::Color::Black);
    wordTypeArea.setOutlineThickness(2.0f);
    wordTypeArea.setBoxPosition(wordTypeArea.getTextPosition().x - 5, wordTypeArea.getTextPosition().y - 5);
    // Word definition
    sf::FloatRect wordDefBounds = wordDefArea.getGlobalBounds();
    wordDefArea.setBoxSize(sf::Vector2f(theBox.getSize().x - 25, wordDefBounds.height + 10));
    wordDefArea.setOutlineColor(sf::Color::Black);
    wordDefArea.setOutlineThickness(2.0f);
    wordDefArea.setBoxPosition(wordDefArea.getTextPosition().x - 5, wordDefArea.getTextPosition().y - 5);
    // Word example
    sf::FloatRect wordExampleBounds = wordExampleArea.getGlobalBounds();
    std::string exampleText = wordExampleArea.getText();
    if(!exampleText.empty())
        wordExampleArea.setBoxSize(sf::Vector2f(theBox.getSize().x - 25, wordExampleBounds.height + 10));
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
