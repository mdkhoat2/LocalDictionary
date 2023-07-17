#include "NewWord.h"

void NewWord::addNewWord(EngTrieNode*& root, std::string word, std::string wordInfo, std::queue<WordData> addedWord) {
	trieInsert(root, word, wordInfo);
	WordData tmp;
	extractWordData(tmp, word, wordInfo);
	addedWord.push(tmp);
}

void NewWord::saveAddedWord(std::queue<WordData> addedWord) {
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
                trieInsert(root, word, wordInfo);
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
    trieInsert(root, word, wordInfo); // Insert last word
    fin.close();
}

// UI

NewWord::NewWord() :
    backButton("", { 50, 50 }, 20, sf::Color::Red, sf::Color::Transparent),
    addButton("", { 50, 50 }, 20, sf::Color::Green, sf::Color::Transparent),
    wordBar(20, sf::Color::Black, sf::Color::Blue, true),
    defBar(20, sf::Color::Black, sf::Color::Blue, true),
    isEndScreen(false)
{
    initFont();
    initBackButton();
    initAddButton();
    initWordBar();
    initDefBar();
}

void NewWord::initFont() {
    // Load font from file
    if (!font.loadFromFile("font/SF-Pro-Rounded-Regular.otf"))
        std::cout << "Font not found!\n";
}

void NewWord::initWordBar() {
    wordBar.setPosition({ 101, 172 });
    wordBar.setBoxPosition({ 50, 150 });
    wordBar.setBoxSize({ 800, 68 });
    wordBar.setLimit(true, 65); //set limit to 65 characters
    wordBar.setFont(font);
}

void NewWord::initDefBar() {
    defBar.setPosition({ 101, 322 });
    defBar.setBoxPosition({ 50, 300 });
    defBar.setBoxSize({ 800, 400 });
    defBar.setLimit(true, 1000); //set limit to 1000 characters
    defBar.setFont(font);
}

void NewWord::initBackButton() {
    backButton.setFont(font);
    backButton.setPosition({ 50, 50 });
    backButton.setOutlineThickness(2);
}

void NewWord::initAddButton() {
    backButton.setFont(font);
    addButton.setPosition({ 150, 50 });
    addButton.setOutlineThickness(2);
}

void NewWord::handleEvent(sf::Event event, sf::RenderWindow& window, bool& endScreen) {
    if (event.type == sf::Event::TextEntered) {
        wordBar.typedOn(event);
        defBar.typedOn(event);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (wordBar.isMouseOver(window))
            wordBar.setSelected(true);
        else
            wordBar.setSelected(false);
        if (defBar.isMouseOver(window))
            defBar.setSelected(true);
        else
            defBar.setSelected(false);
        if (backButton.isMouseOver(window)) {
            endScreen = true;
            isEndScreen = endScreen;
        }
    }
}

void NewWord::update(sf::RenderWindow& window) {
    if (!isEndScreen) {
        backButton.update(window);
        addButton.update(window);
    }
}

void NewWord::render(sf::RenderWindow& window) {
    if (!isEndScreen) {
        wordBar.drawTo(window);
        defBar.drawTo(window);
        backButton.drawTo(window);
        addButton.drawTo(window);
    }
}

void NewWord::setEndScreen(bool value) {
    isEndScreen = value;
}
