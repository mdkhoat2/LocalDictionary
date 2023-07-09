#ifndef DROPDOWNLIST_H_INCLUDED
#define DROPDOWNLIST_H_INCLUDED

#include <vector>
#include "Button.h"

class DropDownList
{
public:
    DropDownList(float x, float y, float width, float height, 
    std::vector<std::string> names, unsigned numOfElements, unsigned defaultIndex = 0);
    ~DropDownList();

    // Accessors
    const unsigned getActiveElementID();
    const bool getKeyTime();

    // Setters
    void setFont(sf::Font& theFont);

    // Functions
    void updateKeyTime();
    void update(sf::RenderWindow& window);
    void drawTo(sf::RenderWindow& window);

private:
    sf::Font font;
    Button* activeElement;
    std::vector<Button*> list;
    bool showList;

    float keyTime;
    float keyTimeMax;
};


#endif // DROPDOWNLIST_H_INCLUDED
