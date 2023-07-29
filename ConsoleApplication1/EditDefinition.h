#ifndef EDITDEFINITION_H
#define EDITDEFINITION_H

#include "Button.h"
#include "Textbox.h"
#include "WordData.h"

class EditBox
{
public:
    EditBox(const sf::Vector2f& pos, const sf::Vector2f& size, 
    const sf::Color& backColor, const sf::Color& textColor);
    void update(sf::RenderWindow& window);
    void drawTo(sf::RenderWindow& window);
public:
    void setFont(const sf::Font& font);
    void setPosition(float xIn, float yIn);
    void setBackColor(const sf::Color& color);
    void setSize(const sf::Vector2f& size);
    void setCharacterSize(unsigned int size);
    void wrapText(sf::Text& theText);
    void adjustTextPosition();
    void initTextToEdit(const sf::String& theWord, const sf::String& theWordType, 
    const sf::String& theWordDef, const sf::String& theWordExample);
    void adjustSurroundingTextbox();

    bool isMouseOverWordTypeArea(sf::RenderWindow& window);
    bool isMouseOverWordDefArea(sf::RenderWindow& window);
    bool isMouseOverWordExampleArea(sf::RenderWindow& window);

    void setSelectedWordTypeArea(bool val);
    void setSelectedWordDefArea(bool val);
    void setSelectedWordExampleArea(bool val);

    bool isWordTypeAreaSelected();
    bool isWordDefAreaSelected();
    bool isWordExampleAreaSelected();

    void wordTypeAreaTypedOn(sf::Event input);
    void wordDefAreaTypedOn(sf::Event input);
    void wordExampleAreaTypedOn(sf::Event input);

    // Accessors
    std::string getWordType();
    std::string getWordDef();
    std::string getWordExample();

    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getSize() const;
private:
    sf::RectangleShape theBox;
    sf::Text word;
    Textbox wordTypeArea;
    Textbox wordDefArea;
    Textbox wordExampleArea;

    sf::Text wordTypePlaceholder;
    sf::Text wordDefPlaceholder;
    sf::Text wordExamplePlaceholder;
};

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