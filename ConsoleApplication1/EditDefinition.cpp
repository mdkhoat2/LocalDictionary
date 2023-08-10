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
    succeededTimeMax = sf::seconds(1.5f);
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
    if (currentDataSetID == 0)
		dataSetButton.setString("      EN - EN");
	else if (currentDataSetID == 1)
		dataSetButton.setString("      EN - VI");
	else if (currentDataSetID == 2)
		dataSetButton.setString("      VI - EN");
	else
		dataSetButton.setString("      Emoji");
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