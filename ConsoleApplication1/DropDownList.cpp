
#include "DropDownList.h"


DropDownList::DropDownList(float x, float y, float width, float height,
    std::vector<std::string> names, unsigned numOfElements, unsigned defaultIndex) 
    : showList(false), keyTimeMax(1.2f), keyTime(0.f)
{
    activeElement = new Button(names[defaultIndex], sf::Vector2f(width, height), 
    20, sf::Color::Blue, sf::Color::Black);
    activeElement->setPosition(x, y);
    for(int i = 0; i < numOfElements; ++i)
    {
        Button* newButton = new Button(names[i], sf::Vector2f(width, height), 20, 
        sf::Color::Blue, sf::Color::Black);
        newButton->setPosition(x, y + (i+1) * height);
        list.push_back(newButton);
    }
}

DropDownList::~DropDownList()
{
    delete activeElement;
    activeElement = nullptr;
    for(int i = 0; i < list.size(); ++i)
    {
        delete list[i];
        list[i] = nullptr;
    }
}

const unsigned DropDownList::getActiveElementID()
{
    return 0;
}

const bool DropDownList::getKeyTime()
{
    if(keyTime >= keyTimeMax)
    {
        keyTime = 0.f;
        return true;
    }
    return false;
}

void DropDownList::setFont(sf::Font &theFont)
{
    activeElement->setFont(theFont);
    for(int i = 0; i < list.size(); ++i)
    {
        list[i]->setFont(theFont);
    }
}

void DropDownList::updateKeyTime()
{
    if(keyTime < keyTimeMax)
        keyTime += 0.1f;
}

void DropDownList::update(sf::RenderWindow &window)
{
    updateKeyTime();
    if(activeElement->isPressed(window))
    {
        if(showList)
            showList = false;
        else
            showList = true;
    }

    if(showList)
    {
        for(auto &i: list)
        {
            if(i->isPressed(window) && getKeyTime())
            {
                showList = false;
                activeElement->setText(i->getText());
            }
        }
    }
}

void DropDownList::drawTo(sf::RenderWindow& window)
{
    activeElement->drawTo(window);
    if(showList)
    {
        for(auto &i: list)
            i->drawTo(window);
    }

}
