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
    void setCurrentDataSet(int theID);

    // For Add words
    void showExistedDefinitions();
    void showNewDefinitions();

    // For Remove words
    void showDeletionReConfirmation();
    void showDeleteSuccessfully();
    
    // For Eng-Eng (updated)
    void initEngEngFirstDef();
    void showNextEngEngDef();
    void showPrevEngEngDef();
    void showNoEngEngDefinitions();
    void clearEngEngData();
    void setEngEngUIText();

    // For Eng-Vie
    void initEngVieFirstDef();
    void showNextEngVieDef();
    void showPrevEngVieDef();
    void showNoEngVieDefinitions();
    void clearEngVieData();
    void setEngVieUIText();

    // For Vie-Eng
    void initVieEngFirstDef();
    void showNextVieEngDef();
    void showPrevVieEngDef();
    void showNoVieEngDefinitions();
    void clearVieEngData();
    void setVieEngUIText();

    //For Emoji
    void showEmojiDefinition(std::string& inputWord, std::string& wordInfor);
    void showNoEmojiDefinition();
    void clearEmoji();
    void setEmojiMode(bool value);
    bool getEmojiMode();

    // Functions for next and prev buttons
    bool isMouseOverNextButton(sf::RenderWindow& window);
    bool isMouseOverPrevButton(sf::RenderWindow& window);
    bool nextButtonDrawn();
    bool prevButtonDrawn();
    void setNextButtonPos(float xIn, float yIn);
    void setPrevButtonPos(float xIn, float yIn);
    sf::Vector2u getNextButtonTexSize() const;
    sf::Vector2u getPrevButtonTexSize() const;
    const sf::Vector2f& getNextButtonScale() const;
    const sf::Vector2f& getPrevButtonScale() const;
    

    // Accessors
    const sf::String& getWord() const;
    const sf::String& getWordType() const;
    const sf::String& getWordDef() const;
    const sf::String& getWordExample() const;

    // Receive change from edit definition screen
    void receiveEditText(std::string& editWordType, std::string& editWordDef, std::string& editWordExample);
    
private:
    sf::RectangleShape theBox;

    sf::Text word;
    sf::Text wordType;
    sf::Text wordDef;
    sf::Text wordExample;
    //sf::Text emojiText;

    WordDataEngVie* EEData;
    int EEDefID;
    int EEDefNum;

    WordDataEngVie* engVieData; // for Eng-Vie data set only
    int engVieDefID;
    int engVieDefNum;

    WordDataEngVie* vieEngData; // for Vie-Eng data set only
    int vieEngDefID;
    int vieEngDefNum;
    sf::Texture emojiTexture;
    sf::Sprite emojiImage;
    bool showNextButton;
    bool showPrevButton;
    sf::Texture nextButtonTex;
    sf::Texture prevButtonTex;
    sf::Sprite nextButtonSprite;
    sf::Sprite prevButtonSprite;
    //sf::Font Font;
    bool emojiDefinition;
    int currentDataSetID;
};




#endif
