#include "RemoveWord.h"

void RemoveWord::removeEEWord(EngTrieNode*& root, std::string word/*, std::string& wordInfo*/) {
    trieHide(root, word, 0);
    //std::string newWordInfo = formatEngEngWordInfo(wordInfo);
    //removedEEWord.push({ word, newWordInfo });
    removedEEWord.push(word);
}

void RemoveWord::saveRemovedEEWord() {
    if (removedEEWord.empty()) return;

    std::ofstream fout("data/add_remove/Removed Words.txt");
    if (!fout.is_open()) {
        std::cout << "Could not open Removed Words.txt file!";
        fout.close();
        return;
    }

    while (!removedEEWord.empty()) {
        //std::string tmp = removedEEWord.front().first;
        std::string tmp = removedEEWord.front();
        if (tmp != "") {
            fout << tmp << std::endl;
            //std::string newWordInfo = removedEEWord.front().second;
            //fout << newWordInfo << std::endl;
        }
        removedEEWord.pop();
    }
    fout.close();
}

void RemoveWord::loadRemovedEEWord(EngTrieNode*& root) {
    std::ifstream fin("data/add_remove/Removed Words.txt");
    if (!fin.is_open()) {
        std::cout << "Could not open Removed Words.txt file!";
        fin.close();
        return;
    }
    std::string line, word;
    while (std::getline(fin, line)) {
        if (line[0] == ' ') // this is an empty space
            continue;
        else {
            word = line;
            removeEEWord(root, word);
        }
    }

    //std::string line, word, wordInfo;
    //int count = 0;
    //while (std::getline(fin, line))
    //{
    //    if (line[0] == '*') { // this is a word type
    //        if (!wordInfo.empty()) wordInfo += '\n';
    //        wordInfo += line.substr(1);
    //    }
    //    else if (line[0] == '-') { // this is a word definition
    //        wordInfo += '\n' + line.substr(1);
    //    }
    //    else if (line[0] == '=') { // this is a word example
    //        if (line[1] == ' ') wordInfo += ';' + line.substr(1);
    //        else wordInfo += line.substr(1);
    //    }
    //    else { // this is a word 
    //        if (count == 0) // Read first word
    //        {
    //            ++count;
    //            word = line;
    //        }
    //        else
    //        {
    //            // remove the previous word with its definition
    //            removeEEWord(root, word, wordInfo);
    //            word = line;
    //            wordInfo.clear();
    //        }
    //    }
    //}
    //if (word.empty()) {
    //    fin.close();
    //    return;
    //}
    //removeEEWord(root, word, wordInfo); // remove last word
    fin.close();
}

// UI

RemoveWord::RemoveWord(sf::Font& font, sf::Font& font2, sf::RenderWindow& window) :
    wordBar(20, sf::Color::Black, sf::Color::Transparent, true),
    backButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    cancelButton("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    removeButton("", { 35, 35 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    confirmButton("", { 40, 40 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    dataSetButton("      EN - EN", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Black),
    noteBox({ 72, 240 }, { 100, 510 }, sf::Color::Transparent, sf::Color::Black),
    displayBox({ 72, 340 }, { 780, 610 }, sf::Color::Transparent, sf::Color::Black),
    isDeleting(false),
    isEndScreen(false),
    currentDataSetID(0)
{
    initBackground(window);
    initBackButton(font);
    initRemoveButton(font);
    initConfirmButton(font);
    initCancelButton(font);
    initDataSetButton(font);
    initWordBar(font);
    initNoteBox(font2);
    initDisplayBox(font2);
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

    // Load data set image from file
    if (!dataSetTex.loadFromFile("background/data-set.png"))
        std::cout << "data-set not found!\n";
    dataSetTex.setSmooth(true);
    dataSet.setTexture(dataSetTex);

    // Scale the data set image
    scaleX = static_cast<float>(185.f) / dataSetTex.getSize().x;
    scaleY = static_cast<float>(92.f) / dataSetTex.getSize().y;
    dataSet.setScale(scaleX, scaleY);
    // Set the data set image's position
    dataSet.setPosition({ 956, 56 });

    // Load cancel image from file
    if (!cancelTex.loadFromFile("background/cancel-button.png"))
        std::cout << "cancel-button not found!\n";
    cancelTex.setSmooth(true);
    cancel.setTexture(cancelTex);

    // Scale cancel the image
    scaleX = static_cast<float>(185.f) / cancelTex.getSize().x;
    scaleY = static_cast<float>(77.f) / cancelTex.getSize().y;
    cancel.setScale(scaleX, scaleY);
    // Set the cancel image's position
    cancel.setPosition({ 956, 237 });


    // Load confirm image from file
    if (!confirmTex.loadFromFile("background/buttondelete.jpg"))
        std::cout << "buttondelete not found!\n";
    confirmTex.setSmooth(true);
    confirm.setTexture(confirmTex);

    // Scale confirm the image
    scaleX = static_cast<float>(47.f) / confirmTex.getSize().x;
    scaleY = static_cast<float>(47.f) / confirmTex.getSize().y;
    confirm.setScale(scaleX, scaleY);
    // Set the confirm image's position
    confirm.setPosition({ 875, 270 });
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

void RemoveWord::initCancelButton(sf::Font& font) {
    cancelButton.setFont(font);
    cancelButton.setPosition({ 972, 253 });
    cancelButton.setOutlineThickness(2);
}

void RemoveWord::initRemoveButton(sf::Font& font) {
    removeButton.setFont(font);
    removeButton.setPosition({ 882, 175 });
    removeButton.setOutlineThickness(2);
}

void RemoveWord::initConfirmButton(sf::Font& font) {
    confirmButton.setFont(font);
    confirmButton.setPosition({ 878, 273 });
    confirmButton.setOutlineThickness(2);
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
    displayBox.setCharacterSize(25);
}

void RemoveWord::initNoteBox(sf::Font& font) {
    noteBox.setFont(font);
    noteBox.setCharacterSize(25);
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

void RemoveWord::handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen, EngTrieNode*& engEngRoot,
std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector,
std::vector<WordDataEngVie>& vieEngVector) {
    if (event.type == sf::Event::TextEntered) {
        wordBar.typedOn(event);
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
            if (currentDataSetID == 0) {
                int wordIndex = filterAndSearch(engEngRoot, inputWord, 0);
                if (wordIndex != -1) {
                    // Console
                    std::cout << "The word  is found!" << "\n";
                    std::cout << wordIndex << std::endl;

                    wordTmp = inputWord;
                    isDeleting = true;

                    //UI
                    noteBox.showDeletionReConfirmation();
                    displayBox.getWordDataEngEng(inputWord, wordIndex, engEngVector);
                }
                else {
                    std::cout << "Cannot find the word" << "\n";
                    noteBox.showNoEngEngDefinitions();
                    displayBox.clearEngEngData();
                }
            }
            /*else if (currentDataSetID == 1)
                removeInEngVieDict(inputWord, engEngRoot);
            else if (currentDataSetID == 2)
                removeInVieEngDict(inputWord, engEngRoot);*/
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
        else if (isDeleting && cancelButton.isMouseOver(window)) {
            isDeleting = false;
            noteBox.showCancelSuccessfully();
            wordTmp.clear();
            wordInfoTmp.clear();
        }
        else if (isDeleting && confirmButton.isMouseOver(window)) {
            isDeleting = false;
            if (currentDataSetID == 0) {
                displayBox.clearEngEngData();
                removeEEWord(engEngRoot, wordTmp);
            }
            /*else if (currentDataSetID == 1)
                removeInEngVieDict(inputWord, engEngRoot);
            else if (currentDataSetID == 2)
                removeInVieEngDict(inputWord, engEngRoot);*/
            noteBox.showDeleteSuccessfully();
            wordTmp.clear();
            wordInfoTmp.clear();
        }
        else if (!isDeleting && dataSetButton.isMouseOver(window))
            changeDataSet();
    }
}

void RemoveWord::update(sf::RenderWindow& window) {
    if (!isEndScreen) {
        backButton.update(window);
        removeButton.update(window);
        dataSetButton.update(window);
        if (isDeleting) {
            cancelButton.update(window);
            confirmButton.update(window);
        }
        noteBox.update(window);
        displayBox.update(window);
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
        if (isDeleting) {
            window.draw(cancel);
            window.draw(confirm);
            cancelButton.drawTo(window);
            confirmButton.drawTo(window);
        }
        noteBox.drawTo(window);
        displayBox.drawTo(window);
    }
}

void RemoveWord::setEndScreen(bool value) {
    isEndScreen = value;
}

bool RemoveWord::removeInEngEngDict(std::string& inputWord, EngTrieNode*& engEngRoot) {
    //std::string wordInfo = filterAndSearch(engEngRoot, inputWord, 0);
    //if (!wordInfo.empty()) {
    //    isDeleting = true;
    //    // Console
    //    std::cout << "The word has already existed" << "\n";
    //    separateEngEngExample(wordInfo);
    //    std::string newWordInfo = formatEngEngWordInfo(wordInfo);
    //    std::cout << newWordInfo << std::endl;
    //    // UI
    //    removeEEWord(engEngRoot, inputWord, wordInfo);
    //}
    //else {
    //    isDeleting = false;
    //    std::cout << "Cannot find the word" << "\n";
    //    noteBox.showNoEngEngDefinitions();
    //    displayBox.clearEngEngData();
    //    return false;
    //}
    return 1;
}

void RemoveWord::removeInEngVieDict(std::string& inputWord, EngTrieNode*& engEngRoot) {
}

void RemoveWord::removeInVieEngDict(std::string& inputWord, EngTrieNode*& engEngRoot) {

}
