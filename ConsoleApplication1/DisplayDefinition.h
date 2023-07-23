#ifndef DISPLAYDEFINITION_H
#define DISPLAYDEFINITION_H

#include <vector>
#include "Button.h"
#include "WordData.h"

class DisplayBox
{
public:
    DisplayBox(const sf::Vector2f& pos, const sf::Vector2f& size, 
    const sf::Color& backColor, const sf::Color& textColor);
    ~DisplayBox();
    void setPosition(const sf::Vector2f& pos);
    void setPosition(float xIn, float yIn);
    void setBackColor(const sf::Color& color);
    void setSize(const sf::Vector2f& size);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);

    void update(sf::RenderWindow& window);
    void drawTo(sf::RenderWindow& window);

    void getWordDataEngEng(std::string& inputWord, std::string& wordInfo);
    void getWordDataEngVie(std::string& inputWord, std::string& wordInfo);
    void getWordDataVieEng(std::string& inputWord, std::string& wordInfo);

    void wrapText(sf::Text& theText);
    void adjustTextPosition();
    // For Eng-Eng
    void initFirstDef();
    void setUIText();
    void showNextDef();
    void showPrevDef();
    void showNoDefinitions();
    void clearEngEngData();

    void showExistedDefinitions();
    void showNewDefinitions();

    // For Eng-Vie
    void initEngVieFirstDef();
    void showNextEngVieDef();
    void showPrevEngVieDef();
    void showNoEngVieDefinitions();
    void clearEngVieData();

    // For Vie-Eng
    void initVieEngFirstDef();
    void showNextVieEngDef();
    void showPrevVieEngDef();
    void showNoVieEngDefinitions();
    void clearVieEngData();

    bool isMouseOverNextButton(sf::RenderWindow& window);
    bool isMouseOverPrevButton(sf::RenderWindow& window);
    bool nextButtonDrawn();
    bool prevButtonDrawn();

    // Accessors
    const sf::String& getWord() const;
    const sf::String& getWordType() const;
    const sf::String& getWordDef() const;
    const sf::String& getWordExample() const;
    
private:
    sf::RectangleShape theBox;
    
    sf::Text word;
    sf::Text wordType;
    sf::Text wordDef;
    sf::Text wordExample;

    int engEngTypeID;
    int engEngDefID;
    WordDefNode* engEngPtr;
    WordData* engEngData; // for Eng-Eng data set only
    int engEngDefNum;

    WordDataEngVie* engVieData; // for Eng-Vie data set only
    int engVieDefID;
    int engVieDefNum;

    WordDataEngVie* vieEngData; // for Vie-Eng data set only
    int vieEngDefID;
    int vieEngDefNum;

    bool showNextButton;
    bool showPrevButton;
    sf::Texture nextButtonTex;
    sf::Texture prevButtonTex;
    sf::Sprite nextButtonSprite;
    sf::Sprite prevButtonSprite;
};



#endif