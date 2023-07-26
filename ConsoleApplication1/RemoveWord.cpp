#include "RemoveWord.h"

void RemoveWord::removeWord(EngTrieNode*& root, std::string word) {
    trieRemove(root, word, 0);
    std::string tmp = word;
    removedWord.push(tmp);
}

void RemoveWord::saveRemovedWord() {
    if (removedWord.empty()) return;

    std::ofstream fout("data/Removed Words.txt");
    if (!fout.is_open()) {
        fout.close();
        return;
    }

    while (!removedWord.empty()) {
        std::string tmp = removedWord.front();
        fout << tmp << std::endl;
        removedWord.pop();
    }

    fout.close();
}

void RemoveWord::loadRemovedWord(EngTrieNode*& root) {
    std::ifstream fin("data/Removed Words.txt");

    std::string word;

    while (std::getline(fin, word))
        trieRemove(root, word, 0);
    fin.close();
}

// UI

RemoveWord::RemoveWord(sf::Font& font, sf::RenderWindow& window) :
    wordBar(20, sf::Color::Black, sf::Color::Transparent, true),
    backButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    removeButton("", { 35, 35 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    dataSetButton("      EN - EN", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Black),
    noteBox({ 72, 240 }, { 100, 610 }, sf::Color::Transparent, sf::Color::Black),
    displayBox({ 72, 340 }, { 780, 610 }, sf::Color::Transparent, sf::Color::Black),
    isEndScreen(false),
    currentDataSetID(0)
{
    initBackground(window);
    initBackButton(font);
    initRemoveButton(font);
    initDataSetButton(font);
    initWordBar(font);
    initDisplayBox(font);
    initNoteBox(font);
    initDataSetText(font);
}

void RemoveWord::initBackground(sf::RenderWindow& window)
{
    // Load background from file
    if (!removeScreenTex.loadFromFile("background/remove.jpg"))
        std::cout << "add not found!\n";
    removeScreenTex.setSmooth(true);
    removeScreen.setTexture(removeScreenTex);

    // Scale the background to fit window
    float scaleX = static_cast<float>(window.getSize().x) / removeScreenTex.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / removeScreenTex.getSize().y;
    removeScreen.setScale(scaleX, scaleY);

    // Load image from file
    if (!dataSetTex.loadFromFile("background/data-set.png"))
        std::cout << "data-set not found!\n";
    dataSetTex.setSmooth(true);
    dataSet.setTexture(dataSetTex);

    // Scale the image
    scaleX = static_cast<float>(185.f) / dataSetTex.getSize().x;
    scaleY = static_cast<float>(92.f) / dataSetTex.getSize().y;
    dataSet.setScale(scaleX, scaleY);
    // Set the image's position
    dataSet.setPosition({ 956, 56 });

}

void RemoveWord::initWordBar(sf::Font& font) {
    wordBar.setPosition({ 125, 180 });
    wordBar.setBoxPosition({ 74, 158 });
    wordBar.setBoxSize({ 800, 68 });
    wordBar.setLimit(true, 65); //set limit to 65 characters
    wordBar.setFont(font);
}

void RemoveWord::initBackButton(sf::Font& font) {
    backButton.setFont(font);
    backButton.setPosition({ 972, 163 });
    backButton.setOutlineThickness(2);
}

void RemoveWord::initRemoveButton(sf::Font& font) {
    removeButton.setFont(font);
    removeButton.setPosition({ 882, 175 });
    removeButton.setOutlineThickness(2);
}

void RemoveWord::initDataSetText(sf::Font& font)
{
    dataSetText.setFont(font);
    dataSetText.setPosition({ 972, 50 });
    dataSetText.setCharacterSize(20);
    dataSetText.setFillColor(sf::Color::Black);
}

void RemoveWord::initDataSetButton(sf::Font& font) {
    dataSetButton.setFont(font);
    dataSetButton.setPosition({ 972, 72 });
    dataSetButton.setOutlineThickness(2);
    dataSetButton.setStyle(sf::Text::Style::Bold);
}

void RemoveWord::initDisplayBox(sf::Font& font) {
    displayBox.setFont(font);
    displayBox.setCharacterSize(30);
}

void RemoveWord::initNoteBox(sf::Font& font) {
    noteBox.setFont(font);
    noteBox.setCharacterSize(30);
}

void RemoveWord::changeDataSet()
{
    // Clear word data before change data set
    if (currentDataSetID == 0)
        displayBox.clearEngEngData();
    else if (currentDataSetID == 1)
        displayBox.clearEngVieData();
    //else if (currentDataSetID == 2)
        //displayBox.clearVieEngData();

    // Start changing data set
    if (currentDataSetID == 3)
        currentDataSetID = 0;
    else
        ++currentDataSetID;

    if (currentDataSetID == 0)
        dataSetButton.setString("      EN - EN");
    else if (currentDataSetID == 1)
        dataSetButton.setString("      EN - VI");
    else if (currentDataSetID == 2)
        dataSetButton.setString("      VI - EN");
    else
        dataSetButton.setString("      Emoji");
}

void RemoveWord::handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen, EngTrieNode*& engEngRoot) {
    if (event.type == sf::Event::TextEntered) {
        wordBar.typedOn(event);
        //defBar.typedOn(event);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (wordBar.isMouseOver(window))
            wordBar.setSelected(true);
        else
            wordBar.setSelected(false);
        if (backButton.isMouseOver(window)) {
            endScreen = true;
            isEndScreen = endScreen;
        }
        else if (removeButton.isMouseOver(window)) {
            std::string inputWord = wordBar.getText();
            if (currentDataSetID == 0)
                removeInEngEngDict(inputWord, engEngRoot);
            else if (currentDataSetID == 1)
                removeInEngVieDict(inputWord, engEngRoot);
            else if (currentDataSetID == 2)
                removeInVieEngDict(inputWord, engEngRoot);
        }
        else if (displayBox.nextButtonDrawn() && displayBox.isMouseOverNextButton(window))
        {
            if (currentDataSetID == 0)
                displayBox.showNextEngEngDef();
            else if (currentDataSetID == 1)
                displayBox.showNextEngVieDef();
            else if (currentDataSetID == 2)
                displayBox.showNextVieEngDef();
        }
        else if (displayBox.prevButtonDrawn() && displayBox.isMouseOverPrevButton(window))
        {
            if (currentDataSetID == 0)
                displayBox.showPrevEngEngDef();
            else if (currentDataSetID == 1)
                displayBox.showPrevEngVieDef();
            else if (currentDataSetID == 2)
                displayBox.showPrevVieEngDef();
        }
        else if (dataSetButton.isMouseOver(window))
            changeDataSet();
    }
}

void RemoveWord::update(sf::RenderWindow& window) {
    if (!isEndScreen) {
        backButton.update(window);
        removeButton.update(window);
        dataSetButton.update(window);
        //noteBox.update(window);
        //displayBox.update(window);
    }
}

void RemoveWord::render(sf::RenderWindow& window) {
    if (!isEndScreen) {
        window.clear(sf::Color::White);
        window.draw(removeScreen);
        window.draw(dataSet);
        wordBar.drawTo(window);
        backButton.drawTo(window);
        removeButton.drawTo(window);
        dataSetButton.drawTo(window);
        //noteBox.drawTo(window);
        //displayBox.drawTo(window);
    }
}

void RemoveWord::setEndScreen(bool value) {
    isEndScreen = value;
}

void RemoveWord::removeInEngEngDict(std::string& inputWord, EngTrieNode*& engEngRoot) {
    removeWord(engEngRoot, inputWord);
}

void RemoveWord::removeInEngVieDict(std::string& inputWord, EngTrieNode*& engEngRoot) {
}

void RemoveWord::removeInVieEngDict(std::string& inputWord, EngTrieNode*& engEngRoot) {

}
