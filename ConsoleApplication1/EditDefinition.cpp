#include <iostream>
#include "EditDefinition.h"

EditDefinitionScreen::EditDefinitionScreen(sf::Font& font, sf::Sprite& background) : 
    isEndScreen(false),
    currentDataSetID(0),
    cancelButtonTex(),
    cancelButton(),
    dataSetButton("      EN - EN", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Black)
{
    initCancelButton(font);
    initDataSetButton(font);
    initSaveButton(font);
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
    }
}

void EditDefinitionScreen::update(sf::RenderWindow& window)
{
    dataSetButton.update(window);
}

void EditDefinitionScreen::render(sf::RenderWindow &window, sf::Sprite& background)
{
    if(!isEndScreen)
    {
        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(cancelButton);
        window.draw(saveButton);
        dataSetButton.drawTo(window);
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

void EditDefinitionScreen::initCancelButton(const sf::Font &font)
{
    // Cancel button
    if(!cancelButtonTex.loadFromFile("background/cancel-button.png"))
        std::cout << "Cannot load cancel button texture\n";
    cancelButtonTex.setSmooth(true);
    cancelButton.setTexture(cancelButtonTex);
    cancelButton.setScale(0.4f, 0.4f);
    cancelButton.setPosition(450, 650);
}

void EditDefinitionScreen::initSaveButton(const sf::Font &font)
{
    // Save button
    if(!saveButtonTex.loadFromFile("background/save-button.png"))
        std::cout << "Cannot load save button texture\n";
    saveButtonTex.setSmooth(true);
    saveButton.setTexture(saveButtonTex);
    saveButton.setScale(0.4f, 0.4f);
    saveButton.setPosition(200, 650);
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
