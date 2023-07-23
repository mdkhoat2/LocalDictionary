
#include "Button.h"

class EditDefinitionScreen
{
public:
    EditDefinitionScreen(sf::Font& font, sf::Sprite& background);
    void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window, sf::Sprite& background);
public:
    void setEndScreen(bool value);
    void setCurrentDataSetID(int theID);
    bool isMouseOverCancelButton(sf::RenderWindow& window);
    bool isMouseOverSaveButton(sf::RenderWindow& window);
private:
    sf::Texture cancelButtonTex;
    sf::Sprite cancelButton;
    sf::Texture saveButtonTex;
    sf::Sprite saveButton;
    sf::Font font;

    Button dataSetButton;

    bool isEndScreen;
    int currentDataSetID;

private:
    void initCancelButton(const sf::Font& font);
    void initSaveButton(const sf::Font& font);
    void initDataSetButton(const sf::Font& font);
};