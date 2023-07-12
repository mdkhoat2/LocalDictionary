
#include "Button.h"

class EditDefinitionScreen
{
public:
    EditDefinitionScreen();
    void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
public:
    void setEndScreen(bool value);
private:
    Button backButton;
    bool isEndScreen;
};