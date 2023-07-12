#include <iostream>
#include "EditDefinition.h"

EditDefinitionScreen::EditDefinitionScreen() :
    backButton("BACK", {50, 50}, 20, sf::Color::Green, sf::Color::White),
    isEndScreen(false)
{
}

void EditDefinitionScreen::handleEvent(sf::Event event, sf::RenderWindow &window, bool& endScreen)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(backButton.isMouseOver(window))
        {
            endScreen = true;
            isEndScreen = endScreen;
        }
    }
}

void EditDefinitionScreen::update(sf::RenderWindow& window)
{
    if(!isEndScreen)
        backButton.update(window);
}

void EditDefinitionScreen::render(sf::RenderWindow &window)
{
    if(!isEndScreen)
        backButton.drawTo(window);
}

void EditDefinitionScreen::setEndScreen(bool value)
{
    isEndScreen = value;
}
