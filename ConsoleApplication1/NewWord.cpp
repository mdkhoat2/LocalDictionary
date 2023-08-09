#include "NewWord.h"

void NewWord::saveAddedWord() {
    saveAddedEEWord();
    saveAddedEVWord();
    saveAddedVEWord();
}

// EE

void NewWord::addNewEEWord(EngTrieNode*& root, std::string& word, std::string& wordInfo,
    std::vector<WordDataEngVie>& engEngVector) {
    std::string newWordInfo = formatEngEngWordInfo(wordInfo);
    WordDataEngVie theItem;
    extractEngEngData(theItem, word, newWordInfo);
    engEngVector.push_back(theItem);
	trieInsert(root, word, engEngVector.size() - 1, 0);
    addedEEWord.push({word, newWordInfo});
}

bool NewWord::addEEFromTextFile(EngTrieNode*& root, std::string& inputWord, std::string& wordInfo,
    std::vector<WordDataEngVie>& engEngVector) {
    std::ifstream fin("data/add_remove/tests/EE/" + inputWord + ".txt");
    if (!fin.is_open()) {
        std::cout << "Could not open " + inputWord + ".txt file!\n";
        fin.close();
        return false;
    }
    std::string line, word;

    while (std::getline(fin, line)) {
        if (line[0] != ' ')  // this is a word
            word = line; // Read the word
        
        else // this is the definition area
        {
            // Count leading spaces
            int i = 0;
            while (line[i] == ' ')
                ++i;
            // Read the word's information
            // If there are 5 blanks then this line is the start of a new definition
            if (i == 5)
            {
                // Check if there is any word type
                int j = i;
                std::string wordType;
                while (line[j] != ' ' && j < line.length())
                {
                    wordType += line[j];
                    ++j;
                }
                // If it is a word type
                if (isValidWordType(wordType))
                {
                    // If it is the first word type
                    if (wordInfo.empty())
                        wordInfo += wordType + "\n";
                    // If it is not the first word type
                    else
                        wordInfo += "\n" + wordType + "\n";

                    if (j + 3 < line.length())
                    {
                        // If that word type has more than 1 definition
                        if (line[j + 1] == '1' && j + 4 < line.length())
                            wordInfo += line.substr(j + 4);
                        // If that word type has only 1 definition
                        else
                            wordInfo += line.substr(j + 3);
                    }

                }

                // If it is the word "See"
                else if (wordType == "See" && i < line.length())
                    wordInfo += line.substr(i);
                // If it is a number (which means that the word has more than 1 definition for a word type)
                else if (isdigit(line[i]) && i + 3 < line.length())
                {
                    wordInfo += "\n" + line.substr(i + 3);
                }

            }
            // If there are more than 5 blanks then it is just a normal line of a definition
            else if (i > 5 && i < line.length())
            {
                wordInfo += " " + line.substr(i);
            }
            else
            {
                std::cout << "Something goes wrong!" << std::endl;
            }
        }
    }
    if (wordInfo.empty()) {
        fin.close();
        return false;
    }
    separateEngEngExample(wordInfo);
    addNewEEWord(root, word, wordInfo, engEngVector);
    fin.close();
    return true;
}

void NewWord::saveAddedEEWord() {
	if (addedEEWord.empty()) return;

	std::ofstream fout("data/add_remove/Added Words/EE.txt");
	if (!fout.is_open()) {
        std::cout << "Could not open EE.txt file!\n";
		fout.close();
		return;
	}
    while (!addedEEWord.empty()) {
        std::string word = addedEEWord.front().first;
        if (word != "") {
            fout << word << std::endl;
            std::string newWordInfo = addedEEWord.front().second;
            fout << newWordInfo << std::endl;
        }
        addedEEWord.pop();
    }
	fout.close();
}

void NewWord::loadAddedEEWord(EngTrieNode*& root, std::vector<WordDataEngVie>& engEngVector) {
    std::ifstream fin("data/add_remove/Added Words/EE.txt");
    if (!fin.is_open()) {
        std::cout << "Could not open EE.txt file!\n";
        fin.close();
        return;
    }
    std::string line, word, wordInfo;
    int count = 0;
    while (std::getline(fin, line))
    {
        if (line[0] == '*') { // this is a word type
            if (!wordInfo.empty()) wordInfo += '\n';
            wordInfo += line.substr(1); 
        }
        else if (line[0] == '-') { // this is a word definition
            wordInfo += '\n' + line.substr(1);
        }
        else if (line[0] == '=') { // this is a word example
            if (line[1] == ' ') wordInfo += ';' + line.substr(1);
            else wordInfo += line.substr(1);
        }
        else { // this is a word 
            if (count == 0) // Read first word
            {
                ++count;
                word = line;
            }
            else
            {
                // insert the previous word with its definition
                addNewEEWord(root, word, wordInfo, engEngVector);
                word = line;
                wordInfo.clear();
            }
        }
    }
    if (word.empty()) {
        fin.close();
        return;
    }
    addNewEEWord(root, word, wordInfo, engEngVector); // insert last word
    fin.close();
}

// EV

void NewWord::addNewEVWord(EngTrieNode*& root, std::string& word, std::string& wordInfo,
    std::vector<WordDataEngVie>& engVieVector) {
    WordDataEngVie theItem;
    extractEngVieData(theItem, word, wordInfo);
    engVieVector.push_back(theItem);
    trieInsert(root, word, engVieVector.size() - 1, 1);
    addedEVWord.push({ word, wordInfo });
}

bool NewWord::addEVFromTextFile(EngTrieNode*& root, std::string& inputWord, std::string& wordInfo,
    std::vector<WordDataEngVie>& engVieVector) {
    std::ifstream fin("data/add_remove/tests/EV/" + inputWord + ".txt");
    if (!fin.is_open()) {
        std::cout << "Could not open " + inputWord + ".txt file!\n";
        fin.close();
        return false;
    }
    std::string line, word;
    while (std::getline(fin, line))
    {
        // this is the line containing the word
        if (line[0] == '@')
        {
            int i = 1;
            while (i < line.length())
            {
                if (line[i] == '/' || line[i] == '=' || line[i] == '(' || line[i] == ')'
                    || line[i] == '[' || line[i] == ']' || line[i] == '&')
                    break;
                else
                {
                    word += line[i];
                    ++i;
                }
            }
            // Pop the space at the end of the current word
            if (word[word.length() - 1] == ' ')
                word.pop_back();
        }
        // this is the line containing the word type, word definitions, ...
        else
        {
            if (wordInfo.empty())
                wordInfo = line;
            else
                wordInfo += "\n" + line;
        }
    }
    if (wordInfo.empty()) {
        fin.close();
        return false;
    }
    addNewEVWord(root, word, wordInfo, engVieVector);
    fin.close();
    return true;
}

void NewWord::saveAddedEVWord() {
    if (addedEVWord.empty()) return;

    std::ofstream fout("data/add_remove/Added Words/EV.txt");
    if (!fout.is_open()) {
        std::cout << "Could not open EV.txt file!\n";
        fout.close();
        return;
    }
    while (!addedEVWord.empty()) {
        std::string word = addedEVWord.front().first;
        if (word != "") {
            fout << word << std::endl;
            std::string wordInfo = addedEVWord.front().second;
            fout << wordInfo << std::endl;
        }
        addedEVWord.pop();
    }
    fout.close();
}

void NewWord::loadAddedEVWord(EngTrieNode*& root, std::vector<WordDataEngVie>& engVieVector) {
    std::ifstream fin("data/add_remove/Added Words/EV.txt");
    if (!fin.is_open()) {
        std::cout << "Could not open EV.txt file!\n";
        fin.close();
        return;
    }
    std::string line, word, wordInfo;
    int count = 0;
    while (std::getline(fin, line))
    {
        if (line[0] == '*' || line[0] == '-' || line[0] == '=') {
            if (wordInfo.empty())
                wordInfo = line;
            else
                wordInfo += "\n" + line;
        }
        else { // this is a word 
            if (count == 0) // Read first word
            {
                ++count;
                word = line;
            }
            else
            {
                // insert the previous word with its definition
                addNewEVWord(root, word, wordInfo, engVieVector);
                word = line;
                wordInfo.clear();
            }
        }
    }
    if (word.empty()) {
        fin.close();
        return;
    }
    addNewEVWord(root, word, wordInfo, engVieVector); // insert last word
    fin.close();
}

// VE

void NewWord::addNewVEWord(EngTrieNode*& root, std::string& word, std::string& wordInfo,
    std::vector<WordDataEngVie>& vieEngVector) {
    WordDataEngVie theItem;
    extractVieEngData(theItem, word, wordInfo);
    vieEngVector.push_back(theItem);
    trieInsert(root, word, vieEngVector.size() - 1, 2);
    addedVEWord.push({ word, wordInfo });
}

bool NewWord::addVEFromTextFile(EngTrieNode*& root, std::string& inputWord, std::string& wordInfo,
    std::vector<WordDataEngVie>& vieEngVector) {
    std::ifstream fin("data/add_remove/tests/VE/" + inputWord + ".txt");
    if (!fin.is_open()) {
        std::cout << "Could not open " + inputWord + ".txt file!\n";
        fin.close();
        return false;
    }
    std::string line, word;
    while (std::getline(fin, line))
    {
        // this is the line containing the word
        if (line[0] == '@') {
            if (line.length() >= 2)
                word = line.substr(1);
        }
        // this is the line containing the word type, word definitions, ...
        else
        {
            if (wordInfo.empty())
                wordInfo = line;
            else
                wordInfo += "\n" + line;
        }
    }
    if (wordInfo.empty()) {
        fin.close();
        return false;
    }
    addNewVEWord(root, word, wordInfo, vieEngVector);
    fin.close();
    return true;
}

void NewWord::saveAddedVEWord() {
    if (addedVEWord.empty()) return;

    std::ofstream fout("data/add_remove/Added Words/VE.txt");
    if (!fout.is_open()) {
        std::cout << "Could not open VE.txt file!\n";
        fout.close();
        return;
    }
    while (!addedVEWord.empty()) {
        std::string word = addedVEWord.front().first;
        if (word != "") {
            fout << word << std::endl;
            std::string wordInfo = addedVEWord.front().second;
            fout << wordInfo << std::endl;
        }
        addedVEWord.pop();
    }
    fout.close();
}

void NewWord::loadAddedVEWord(EngTrieNode*& root, std::vector<WordDataEngVie>& vieEngVector) {
    std::ifstream fin("data/add_remove/Added Words/VE.txt");
    if (!fin.is_open()) {
        std::cout << "Could not open VE.txt file!\n";
        fin.close();
        return;
    }
    std::string line, word, wordInfo;
    int count = 0;
    while (std::getline(fin, line))
    {
        if (line[0] == '*' || line[0] == '-' || line[0] == '=') {
            if (wordInfo.empty())
                wordInfo = line;
            else
                wordInfo += "\n" + line;
        }
        else { // this is a word 
            if (count == 0) // Read first word
            {
                ++count;
                word = line;
            }
            else
            {
                // insert the previous word with its definition
                addNewVEWord(root, word, wordInfo, vieEngVector);
                word = line;
                wordInfo.clear();
            }
        }
    }
    if (word.empty()) {
        fin.close();
        return;
    }
    addNewVEWord(root, word, wordInfo, vieEngVector); // insert last word
    fin.close();
}

// UI

NewWord::NewWord(sf::Font& font, sf::Font& font2, sf::RenderWindow& window) :
    wordBar(20, sf::Color::Black, sf::Color::Transparent, true),
    backButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    addButton("", { 35, 35 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    dataSetButton("      EN - EN", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Black),
    noteBox({ 72, 240 }, { 100, 610 }, sf::Color::Transparent, sf::Color::Black),
    displayBox({ 72, 340 }, { 780, 610 }, sf::Color::Transparent, sf::Color::Black),
    isEndScreen(false),
    currentDataSetID(0)
{
    initBackground(window);
    initBackButton(font);
    initAddButton(font);
    initDataSetButton(font);
    initWordBar(font);
    initDisplayBox(font2);
    initNoteBox(font2);
    initDataSetText(font);
}

void NewWord::initBackground(sf::RenderWindow& window)
{
    // Load background from file
    if (!addScreenTex.loadFromFile("background/add.jpg"))
        std::cout << "add not found!\n";
    addScreenTex.setSmooth(true);
    addScreen.setTexture(addScreenTex);

    // Scale the background to fit window
    float scaleX = static_cast<float>(window.getSize().x) / addScreenTex.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / addScreenTex.getSize().y;
    addScreen.setScale(scaleX, scaleY);

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

void NewWord::initWordBar(sf::Font& font) {
    wordBar.setPosition({ 125, 180 });
    wordBar.setBoxPosition({ 74, 158 });
    wordBar.setBoxSize({ 800, 68 });
    wordBar.setLimit(true, 65); //set limit to 65 characters
    wordBar.setFont(font);
}

void NewWord::initBackButton(sf::Font& font) {
    backButton.setFont(font);
    backButton.setPosition({ 972, 163 });
    backButton.setOutlineThickness(2);
}

void NewWord::initAddButton(sf::Font& font) {
    addButton.setFont(font);
    addButton.setPosition({ 882, 175 });
    addButton.setOutlineThickness(2);
}

void NewWord::initDataSetText(sf::Font& font)
{
    dataSetText.setFont(font);
    dataSetText.setPosition({ 972, 50 });
    dataSetText.setCharacterSize(20);
    dataSetText.setFillColor(sf::Color::Black);
}

void NewWord::initDataSetButton(sf::Font& font) {
    dataSetButton.setFont(font);
    dataSetButton.setPosition({ 972, 72 });
    dataSetButton.setOutlineThickness(2);
    dataSetButton.setStyle(sf::Text::Style::Bold);
}

void NewWord::initDisplayBox(sf::Font& font) {
    displayBox.setFont(font);
    displayBox.setCharacterSize(25);
}

void NewWord::initNoteBox(sf::Font& font) {
    noteBox.setFont(font);
    noteBox.setCharacterSize(25);
}

void NewWord::changeDataSet()
{
    // Clear note box
    noteBox.clearEngEngData();

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

void NewWord::handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen, EngTrieNode*& engEngRoot,
    std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector,
    std::vector<WordDataEngVie>& vieEngVector) {
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
            // Clear note box
            noteBox.clearEngEngData();

            // Clear word data before change data set
            if (currentDataSetID == 0)
                displayBox.clearEngEngData();
            else if (currentDataSetID == 1)
                displayBox.clearEngVieData();
            else if (currentDataSetID == 2)
                displayBox.clearVieEngData();
            endScreen = true;
            isEndScreen = endScreen;
        }
        else if (addButton.isMouseOver(window)) {
            std::string inputWord = wordBar.getText();
            if (currentDataSetID == 0)
                addInEngEngDict(inputWord, engEngRoot, engEngVector);
            else if (currentDataSetID == 1)
                addInEngVieDict(inputWord, engEngRoot, engVieVector);
            else if (currentDataSetID == 2)
                addInVieEngDict(inputWord, engEngRoot, vieEngVector);
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

void NewWord::update(sf::RenderWindow& window) {
    if (!isEndScreen) {
        backButton.update(window);
        addButton.update(window);
        dataSetButton.update(window);
        noteBox.update(window);
        displayBox.update(window);
    }
}

void NewWord::render(sf::RenderWindow& window) {
    if (!isEndScreen) {
        window.clear(sf::Color::White);
        window.draw(addScreen);
        window.draw(dataSet);
        wordBar.drawTo(window);
        backButton.drawTo(window);
        addButton.drawTo(window);
        dataSetButton.drawTo(window);
        noteBox.drawTo(window);
        displayBox.drawTo(window);
    }
}

void NewWord::setEndScreen(bool value) {
    isEndScreen = value;
}

void NewWord::addInEngEngDict(std::string& inputWord, EngTrieNode*& engEngRoot,
    std::vector<WordDataEngVie>& engEngVector) {
    int wordIndex = filterAndSearch(engEngRoot, inputWord, 0);
    if (wordIndex != -1) {
        // Console
        std::cout << "The word has already existed" << "\n";
        std::cout << wordIndex << std::endl;
        // UI
        noteBox.showExistedDefinitions();
        displayBox.getWordDataEngEng(inputWord, wordIndex, engEngVector);
    }
    else {
        std::string wordInfo;
        if (addEEFromTextFile(engEngRoot, inputWord, wordInfo, engEngVector)) {
            // Console
            std::cout << "The word has been imported" << "\n";
            // UI
            noteBox.showNewDefinitions();
        }
        else {
            std::cout << "Cannot find the word" << "\n";
            noteBox.showNoEngEngDefinitions();
            displayBox.clearEngEngData();
        }
    }
}

void NewWord::addInEngVieDict(std::string& inputWord, EngTrieNode*& engEngRoot,
    std::vector<WordDataEngVie>& engVieVector) {
    int wordIndex = filterAndSearch(engEngRoot, inputWord, 1);
    if (wordIndex != -1) {
        // Console
        std::cout << "Tu vung da co trong tu dien" << "\n";
        // UI
        noteBox.showExistedEngVieDefinitions();
        displayBox.getWordDataEngVie(inputWord, wordIndex, engVieVector);
    }
    else {
        std::string wordInfo;
        if (addEVFromTextFile(engEngRoot, inputWord, wordInfo, engVieVector)) {
            // Console
            std::cout << "Tu vung moi da duoc them" << "\n";
            // UI
            noteBox.showNewEngVieDefinitions();
        }
        else {
            std::cout << "Khong the tim thay tu vung" << "\n";
            noteBox.showNoEngVieDefinitions();
            displayBox.clearEngVieData();
        }
    }
}

void NewWord::addInVieEngDict(std::string& inputWord, EngTrieNode*& engEngRoot, 
    std::vector<WordDataEngVie>& vieEngVector) {
    int wordIndex = filterAndSearch(engEngRoot, inputWord, 2);
    if (wordIndex != -1) {
        // Console
        std::cout << "The word has already existed" << "\n";
        // UI
        noteBox.showExistedVieEngDefinitions();
        displayBox.getWordDataVieEng(inputWord, wordIndex, vieEngVector);
    }
    else {
        std::string wordInfo;
        if (addVEFromTextFile(engEngRoot, inputWord, wordInfo, vieEngVector)) {
            // Console
            std::cout << "The word has been imported" << "\n";
            // UI
            noteBox.showNewVieEngDefinitions();
        }
        else {
            std::cout << "Cannot find the word" << "\n";
            noteBox.showNoVieEngDefinitions();
            displayBox.clearVieEngData();
        }
    }
}
