#include "NewWord.h"

void NewWord::addNewWord(EngTrieNode*& root, std::string& word, std::string& wordInfo) {
	trieInsert(root, word, wordInfo, 0);
	WordData tmp;
	extractWordData(tmp, word, wordInfo);
	addedWord.push(tmp);
}

void NewWord::addFromTextFile(EngTrieNode*& root, std::string& inputWord, std::string& wordInfo) {
    std::ifstream fin("data/" + inputWord + ".txt");
    if (!fin.is_open()) {
        fin.close();
        return;
    }
    std::string line, word;
    bool moreThan1Def = false;
    int count = 0;

    while (std::getline(fin, line)) {
        if (line[0] != ' ') { // this is a word
            if (count == 0) { // Read the word
                ++count;
                word = line;
            }
        }
        else {
            // Skip leading spaces
            int i = 0;
            while (line[i] == ' ')
                ++i;
            // Read the word's information
            // The first line will definitely contain the word type
            if (wordInfo.empty()) {
                std::string wordType;
                while (line[i] != ' ')
                    wordType += line[i++];
                if (isdigit(line[i + 1]))
                    moreThan1Def = true;
                wordInfo += wordType + "\n" + line.substr(i + 1);
            }
            else {
                // Check for "X:" which indicates another meaning of the same word type
                int j = i;
                std::string numStr;
                while (line[j] != ':' && j < line.length())
                    numStr += line[j++];
                if (isNumber(numStr) && moreThan1Def)
                    wordInfo += "\n" + line.substr(i);
                else {
                    // Check for any other word type
                    std::string wordType;
                    while (line[i] != ' ' && i < line.length())
                        wordType += line[i++];
                    // If the word has another word type
                    if (isValidWordType(wordType)) {
                        wordInfo += "\n" + wordType + "\n" + line.substr(i + 1);
                    }
                    // If it is a normal line
                    else if (line[i] == ' ') {
                        wordInfo += " " + wordType + line.substr(i);
                    }
                    // If the line contains only 1 word that is not a word type
                    else {
                        wordInfo += " " + wordType;
                    }
                }
            }
        }
    }
    addNewWord(root, word, wordInfo);
    fin.close();
}

void NewWord::saveAddedWord() {
	if (addedWord.empty()) return;

	std::ofstream fout("data/Added Words.txt");
	if (!fout.is_open()) {
		fout.close();
		return;
	}

	while (!addedWord.empty()) {
		WordData tmp = addedWord.front();
		fout << tmp.word << std::endl;
		for (int i = 0; i < 4; ++i) {
			if (tmp.defListHead[i]) {
				fout << "     ";
				switch (i) {
				case 0:
					fout << "n ";
					break;
				case 1:
					fout << "v ";
					break;
				case 2:
					fout << "adj ";
					break;
				case 3:
					fout << "adv ";
					break;
				}
				if (tmp.defListHead[i]->next) {
					WordDefNode* cur = tmp.defListHead[i];
					int count = 1;
					while (cur) {
						fout << count << ": " << cur->wordDef << std::endl; 
						++count;
						cur = cur->next;
					}
				}
				else fout << " : " << tmp.defListHead[i]->wordDef << std::endl;
			}
		}
		addedWord.pop();
	}

	fout.close();
}

void NewWord::loadAddedWord(EngTrieNode*& root) {
    std::ifstream fin("data/Added Words.txt");
    
    std::string line, word, wordInfo;
    bool moreThan1Def = false;
    int count = 0;

    while (std::getline(fin, line))
    {
        if (line[0] != ' ') // this is a word
        {
            if (count == 0) // Read first word
            {
                ++count;
                word = line;
            }
            else
            {
                // insert the previous word with its definition
                addNewWord(root, word, wordInfo);
                word = line;
                wordInfo.clear();
                moreThan1Def = false;
            }
        }
        else
        {
            // Skip leading spaces
            int i = 0;
            while (line[i] == ' ')
                ++i;
            // Read the word's information
            // The first line will definitely contain the word type
            if (wordInfo.empty())
            {
                std::string wordType;
                while (line[i] != ' ')
                    wordType += line[i++];
                if (isdigit(line[i + 1]))
                    moreThan1Def = true;
                wordInfo += wordType + "\n" + line.substr(i + 1);
            }
            else
            {
                // Check for "X:" which indicates another meaning of the same word type
                int j = i;
                std::string numStr;
                while (line[j] != ':' && j < line.length())
                    numStr += line[j++];
                if (isNumber(numStr) && moreThan1Def)
                    wordInfo += "\n" + line.substr(i);
                else
                {
                    // Check for any other word type
                    std::string wordType;
                    while (line[i] != ' ' && i < line.length())
                        wordType += line[i++];
                    // If the word has another word type
                    if (isValidWordType(wordType))
                    {
                        wordInfo += "\n" + wordType + "\n" + line.substr(i + 1);
                    }
                    // If it is a normal line
                    else if (line[i] == ' ')
                    {
                        wordInfo += " " + wordType + line.substr(i);
                    }
                    // If the line contains only 1 word that is not a word type
                    else
                    {
                        wordInfo += " " + wordType;
                    }
                }
            }
        }
    }
    addNewWord(root, word, wordInfo);
    fin.close();
}

// UI

NewWord::NewWord(sf::Font& font, sf::RenderWindow& window) :
    wordBar(20, sf::Color::Black, sf::Color::Transparent, true),
    //defBar(20, sf::Color::Black, sf::Color::Transparent, true),
    backButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    addButton("", { 35, 35 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    noteBox({ 72, 240 }, { 100, 610 }, sf::Color::Transparent, sf::Color::Black),
    displayBox({ 72, 340 }, { 780, 610 }, sf::Color::Transparent, sf::Color::Black),
    isEndScreen(false)
{
    initBackground(window);
    //initFont(font);
    initBackButton(font);
    initAddButton(font);
    initWordBar(font);
    initDisplayBox(font);
    initNoteBox(font);
    //initDefBar(font);
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

}

//void NewWord::initFont(sf::Font font) {
//    // Load font from file
//    if (!font.loadFromFile("font/SF-Pro-Rounded-Regular.otf"))
//        std::cout << "Font not found!\n";
//}

void NewWord::initWordBar(sf::Font& font) {
    wordBar.setPosition({ 125, 180 });
    wordBar.setBoxPosition({ 74, 158 });
    wordBar.setBoxSize({ 800, 68 });
    wordBar.setLimit(true, 65); //set limit to 65 characters
    wordBar.setFont(font);
}

//void NewWord::initDefBar(sf::Font& font) {
//    defBar.setPosition({ 125, 278 });
//    defBar.setBoxPosition({ 74, 240 });
//    defBar.setBoxSize({ 880, 610 });
//    defBar.setLimit(true, 1000); //set limit to 1000 characters
//    defBar.setFont(font);
//}

void NewWord::initBackButton(sf::Font& font) {
    backButton.setFont(font);
    backButton.setPosition({ 972, 163 });
    backButton.setOutlineThickness(2);
}

void NewWord::initAddButton(sf::Font& font) {
    backButton.setFont(font);
    addButton.setPosition({ 882, 175 });
    addButton.setOutlineThickness(2);
}

void NewWord::initDisplayBox(sf::Font& font) {
    displayBox.setFont(font);
    displayBox.setCharacterSize(30);
}

void NewWord::initNoteBox(sf::Font& font) {
    noteBox.setFont(font);
    noteBox.setCharacterSize(30);
}

void NewWord::handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen, EngTrieNode*& engEngRoot) {
    if (event.type == sf::Event::TextEntered) {
        wordBar.typedOn(event);
        //defBar.typedOn(event);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (wordBar.isMouseOver(window))
            wordBar.setSelected(true);
        else
            wordBar.setSelected(false);
        /*if (defBar.isMouseOver(window))
            defBar.setSelected(true);
        else
            defBar.setSelected(false);*/
        if (backButton.isMouseOver(window)) {
            endScreen = true;
            isEndScreen = endScreen;
        }
        else if (addButton.isMouseOver(window)) {
            std::string inputWord = wordBar.getText();
            std::string wordInfo;
            //std::string wordInfo = filterAndSearch(engEngRoot, inputWord, 0);
            //if (!wordInfo.empty()) {
            //    // Console
            //    std::cout << "The word has already existed" << "\n";
            //    WordData theWordData;
            //    extractWordData(theWordData, inputWord, wordInfo);
            //    theWordData.consolePrint();
            //    // UI
            //    noteBox.showExistedDefinitions();
            //    displayBox.getWordData(inputWord, wordInfo);

            //}
            //else {
                addFromTextFile(engEngRoot, inputWord, wordInfo);
                // Console
                std::cout << "The word has been imported" << "\n";
                WordData theWordData;
                extractWordData(theWordData, inputWord, wordInfo);
                theWordData.consolePrint();
                // UI
                noteBox.showNewDefinitions();
                displayBox.getWordDataEngEng(inputWord, wordInfo);
            //}
        }
        else if (displayBox.nextButtonDrawn() && displayBox.isMouseOverNextButton(window))
        {
            displayBox.showNextDef();
        }
        else if (displayBox.prevButtonDrawn() && displayBox.isMouseOverPrevButton(window))
        {
            displayBox.showPrevDef();
        }
    }
}

void NewWord::update(sf::RenderWindow& window) {
    if (!isEndScreen) {
        backButton.update(window);
        addButton.update(window);
        noteBox.update(window);
        displayBox.update(window);
    }
}

void NewWord::render(sf::RenderWindow& window) {
    if (!isEndScreen) {
        window.draw(addScreen);
        wordBar.drawTo(window);
        //defBar.drawTo(window);
        backButton.drawTo(window);
        addButton.drawTo(window);
        noteBox.drawTo(window);
        displayBox.drawTo(window);
    }
}

void NewWord::setEndScreen(bool value) {
    isEndScreen = value;
}
