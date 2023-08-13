#include "RemoveWord.h"

void RemoveWord::saveRemovedWord() {
    saveRemovedEEWord();
    saveRemovedEVWord();
    saveRemovedVEWord();
}

void RemoveWord::resetRemove(EngTrieNode*& root) {
    std::string tmp;
    while (!removedEEWord.empty()) {
        tmp = removedEEWord.front();
        if (tmp != "")
            trieUnhide(root, tmp, 0);
        removedEEWord.pop();
    }
    while (!removedEVWord.empty()) {
        tmp = removedEVWord.front();
        if (tmp != "")
            trieUnhide(root, tmp, 1);
        removedEVWord.pop();
    }
    while (!removedVEWord.empty()) {
        tmp = removedVEWord.front();
        if (tmp != "")
            trieUnhide(root, tmp, 2);
        removedVEWord.pop();
    }
    std::ofstream fout("data/add_remove/Removed Words/EE.txt");
    if (!fout.is_open())
        fout.close();
    fout << "";
    fout.close();
    fout.open("data/add_remove/Removed Words/EV.txt");
    if (!fout.is_open())
        fout.close();
    fout << "";
    fout.close();
    fout.open("data/add_remove/Removed Words/VE.txt");
    if (!fout.is_open())
        fout.close();
    fout << "";
    fout.close();
}

// EE

void RemoveWord::removeEEWord(EngTrieNode*& root, std::string word) {
    trieHide(root, word, 0);
    removedEEWord.push(word);
}

void RemoveWord::saveRemovedEEWord() {
    if (removedEEWord.empty()) return;

    std::ofstream fout("data/add_remove/Removed Words/EE.txt");
    if (!fout.is_open()) {
        std::cout << "Could not open EE.txt file!";
        fout.close();
        return;
    }

    while (!removedEEWord.empty()) {
        std::string tmp = removedEEWord.front();
        if (tmp != "") 
            fout << tmp << std::endl;
        removedEEWord.pop();
    }
    fout.close();
}

void RemoveWord::loadRemovedEEWord(EngTrieNode*& root) {
    std::ifstream fin("data/add_remove/Removed Words/EE.txt");
    if (!fin.is_open()) {
        std::cout << "Could not open EE.txt file!";
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
    fin.close();
}

// EV

void RemoveWord::removeEVWord(EngTrieNode*& root, std::string word) {
    trieHide(root, word, 1);
    removedEVWord.push(word);
}

void RemoveWord::saveRemovedEVWord() {
    if (removedEVWord.empty()) return;

    std::ofstream fout("data/add_remove/Removed Words/EV.txt");
    if (!fout.is_open()) {
        std::cout << "Could not open EV.txt file!";
        fout.close();
        return;
    }

    while (!removedEVWord.empty()) {
        std::string tmp = removedEVWord.front();
        if (tmp != "")
            fout << tmp << std::endl;
        removedEVWord.pop();
    }
    fout.close();
}

void RemoveWord::loadRemovedEVWord(EngTrieNode*& root) {
    std::ifstream fin("data/add_remove/Removed Words/EV.txt");
    if (!fin.is_open()) {
        std::cout << "Could not open EV.txt file!";
        fin.close();
        return;
    }
    std::string line, word;
    while (std::getline(fin, line)) {
        if (line[0] == ' ') // this is an empty space
            continue;
        else {
            word = line;
            removeEVWord(root, word);
        }
    }
    fin.close();
}

// VE

void RemoveWord::removeVEWord(EngTrieNode*& root, std::string word) {
    trieHide(root, word, 2);
    removedVEWord.push(word);
}

void RemoveWord::saveRemovedVEWord() {
    if (removedVEWord.empty()) return;

    std::ofstream fout("data/add_remove/Removed Words/VE.txt");
    if (!fout.is_open()) {
        std::cout << "Could not open VE.txt file!";
        fout.close();
        return;
    }

    while (!removedVEWord.empty()) {
        std::string tmp = removedVEWord.front();
        if (tmp != "")
            fout << tmp << std::endl;
        removedVEWord.pop();
    }
    fout.close();
}

void RemoveWord::loadRemovedVEWord(EngTrieNode*& root) {
    std::ifstream fin("data/add_remove/Removed Words/VE.txt");
    if (!fin.is_open()) {
        std::cout << "Could not open VE.txt file!";
        fin.close();
        return;
    }
    std::string line, word;
    while (std::getline(fin, line)) {
        if (line[0] == ' ') // this is an empty space
            continue;
        else {
            word = line;
            removeVEWord(root, word);
        }
    }
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
    else if (currentDataSetID == 2)
        displayBox.clearVieEngData();

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
            else if (currentDataSetID == 1) {
                int wordIndex = filterAndSearch(engEngRoot, inputWord, 1);
                if (wordIndex != -1) {
                    // Console
                    std::cout << "Da tim thay tim vung!" << "\n";
                    std::cout << wordIndex << std::endl;

                    wordTmp = inputWord;
                    isDeleting = true;

                    //UI
                    noteBox.showEVDeletionReConfirmation();
                    displayBox.getWordDataEngVie(inputWord, wordIndex, engVieVector);
                }
                else {
                    std::cout << "Khong the tim thay tim vung" << "\n";
                    noteBox.showNoEngVieDefinitions();
                    displayBox.clearEngVieData();
                }
            }
            else if (currentDataSetID == 2) {
                int wordIndex = filterAndSearch(engEngRoot, inputWord, 2);
                if (wordIndex != -1) {
                    // Console
                    std::cout << "The word  is found!" << "\n";
                    std::cout << wordIndex << std::endl;

                    wordTmp = inputWord;
                    isDeleting = true;

                    //UI
                    noteBox.showVEDeletionReConfirmation();
                    displayBox.getWordDataVieEng(inputWord, wordIndex, vieEngVector);
                }
                else {
                    std::cout << "Cannot find the word" << "\n";
                    noteBox.showNoVieEngDefinitions();
                    displayBox.clearVieEngData();
                }
            }
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
            wordTmp.clear();
            if (currentDataSetID == 0)
                noteBox.showCancelSuccessfully();
            else if (currentDataSetID == 1)
                noteBox.showEVCancelSuccessfully();
            else if (currentDataSetID == 2)
                noteBox.showVECancelSuccessfully();
        }
        else if (isDeleting && confirmButton.isMouseOver(window)) {
            isDeleting = false;
            if (currentDataSetID == 0) {
                displayBox.clearEngEngData();
                removeEEWord(engEngRoot, wordTmp);
                noteBox.showDeleteSuccessfully();
            }
            else if (currentDataSetID == 1) {
                displayBox.clearEngVieData();
                removeEVWord(engEngRoot, wordTmp);
                noteBox.showEVDeleteSuccessfully();
            }
            else if (currentDataSetID == 2) {
                displayBox.clearVieEngData();
                removeVEWord(engEngRoot, wordTmp);
                noteBox.showVEDeleteSuccessfully();
            }
            wordTmp.clear();
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
