#ifndef EDITDEFINITION_H
#define EDITDEFINITION_H

#include "EditBox.h"

class EditDefinitionScreen
{
public:
    EditDefinitionScreen(sf::Font& font, sf::Font& font2, sf::Sprite& background);
    void handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen);
    void update(sf::RenderWindow& window, bool& endScreen, bool& isSaved, 
    std::string& editWordType, std::string& editWordDef, std::string& editWordExample);
    void render(sf::RenderWindow& window, sf::Sprite& background);
public:
    void setEndScreen(bool value);
    void setCurrentDataSetID(int theID);
    bool isMouseOverCancelButton(sf::RenderWindow& window);
    bool isMouseOverSaveButton(sf::RenderWindow& window);
    void initTextToEdit(const sf::String& theWord, const sf::String& theWordType, 
    const sf::String& theWordDef, const sf::String& theWordExample);
    // Accessors
    std::string getEditWordType();
    std::string getEditWordDef();
    std::string getEditWordExample();
private:
    sf::Texture cancelButtonTex;
    sf::Sprite cancelButton;
    sf::Texture saveButtonTex;
    sf::Sprite saveButton;
    sf::Font font;

    sf::Texture saveSucceededTex;
    sf::Sprite saveSucceeded;
    bool showSucceeded;
    sf::Clock clock;
    sf::Time succeededTimeMax;

    Button dataSetButton;
    Button cancelButtonHover;
    Button saveButtonHover;

    bool isEndScreen;
    int currentDataSetID;
    int currentEditAreaID;

    EditBox editBox;
private:
    void initCancelButton(const sf::Font& font);
    void initSaveButton(const sf::Font& font);
    void initDataSetButton(const sf::Font& font);
    void initEditBox(const sf::Font& font, sf::Sprite& background);
    void initSaveSucceeded(const sf::Font& font);
};


#endif