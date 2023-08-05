﻿#pragma once
#include <iostream>
#include <fstream>
#include "Application.h"


Application::Application() :
	videoMode(1200, 900),
	window(videoMode, "Dictionary", sf::Style::Close), //don't clear the close style!!
	searchBar(20, sf::Color::Black, sf::Color::Transparent, true),
	searchButton("", { 35, 35 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	menuButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	addButton("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	deleteButton("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	editDefButton("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	favouritebutton("", { 153,42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	searchDefButton("", { 153,42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	engEngRoot(nullptr),
	history(),
	favourite(nullptr),
	currentScreen(ScreenState::MainScreen),
	editDefScreen(nullptr),
	newWord(nullptr),
	removeWord(nullptr),
	searchDefScreen(nullptr),
	displayBox({ 72, 250 }, { 850, 600 }, sf::Color::Transparent, sf::Color::Black),
	dataSetButton("      EN - EN", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Black),
	proposedWord(nullptr),
	currentDataSetID(0)
{
	initWindow();
	initBackground();
	initFont();
	initSearchBar();
	initSearchButton();
	initDataSetButton();
	initMenuButton();
	initAddButton();
	initDeleteButton();
	initEditDefButton();
	initDisplayBox();
	initFavouriteButton();
	initSearchDefButton();
	loadAllHistory();
}

Application::~Application()
{
	trieDeleteAll(engEngRoot);
	delete editDefScreen;
	delete newWord;
	delete favourite;
	delete removeWord;
	delete searchDefScreen;
}

void Application::loadEngEngDict()
{
	std::ifstream fin("data/EE.txt");
	// Skip the first 59 lines (unnecessary lines)
	std::string line, word, wordInfo;
	int count = 0;
	while (count < 59)
	{
		std::getline(fin, line);
		++count;
	}

    while(std::getline(fin, line))
    {
        if(line[0] != ' ') // this is a word
        {
            if(count == 59) // Read first word
            {   
                ++count;
                word = line;
            }
            else
            {
                // insert the previous word with its definition
                trieInsert(engEngRoot, word, wordInfo, 0);
				separateEngEngExample(wordInfo);
				std::string newWordInfo = formatEngEngWordInfo(wordInfo);
				searchDefScreen->insertEngEngItem(word, newWordInfo);
				if (count <= 11584)
					count++;
				else
					engEngVector.push_back(word);
                word = line;
                wordInfo.clear();
            }
        }
        else // this is the definition area
        {
            // Count leading spaces
            int i = 0;
            while(line[i] == ' ')
                ++i;
            // Read the word's information
            // If there are 5 blanks then this line is the start of a new definition
            if(i == 5)
            {
                // Check if there is any word type
                int j = i;
                std::string wordType;
                while(line[j] != ' ' && j < line.length())
                {
                    wordType += line[j];
                    ++j;
                }
                // If it is a word type
                if(isValidWordType(wordType))
                {
                    // If it is the first word type
                    if(wordInfo.empty())
                        wordInfo += wordType + "\n";
                    // If it is not the first word type
                    else
                        wordInfo += "\n" + wordType + "\n";
                    
                    if(j+3 < line.length())
                    {
                        // If that word type has more than 1 definition
                        if(line[j+1] == '1' && j+4 < line.length())
                            wordInfo += line.substr(j+4);
                        // If that word type has only 1 definition
                        else
                            wordInfo += line.substr(j+3);
                    }

                }
                    
                // If it is the word "See"
                else if(wordType == "See" && i < line.length())
                    wordInfo += line.substr(i);
                // If it is a number (which means that the word has more than 1 definition for a word type)
                else if(isdigit(line[i]) && i+3 < line.length())
                {
                    wordInfo += "\n" + line.substr(i+3);
                }
                
            }
            // If there are more than 5 blanks then it is just a normal line of a definition
            else if(i > 5 && i < line.length())
            {
                wordInfo += " " + line.substr(i);
            }
            else
            {
                std::cout << "Something goes wrong!" << std::endl;
            }
        }
    }
    trieInsert(engEngRoot, word, wordInfo, 0); // Insert last word
	engEngVector.push_back(word);
    fin.close();
    newWord->loadAddedEEWord(engEngRoot);
}

void Application::loadEngVieDict()
{
    std::ifstream fin("data/EV_nonaccent.txt");
    int count = 0;
    std::string line, word, wordInfo;
    // Skip the first unnecessary 15 lines
    while(count < 15)
    {
        std::getline(fin, line);
        ++count;
    }
    while(std::getline(fin, line))
    {
        // this is the line containing the word
        if(line[0] == '@')
        {   
            // If it is the first word
            if(count == 15)
                ++count;
            else
            {   
                // insert previous word and its information
                trieInsert(engEngRoot, word, wordInfo, 1);
                searchDefScreen->insertEngVieItem(word, wordInfo);
                word.clear();
                wordInfo.clear();
            }
            int i = 1;
            while(i < line.length())
            {
                if(line[i] == '/' || line[i] == '=' || line[i] == '(' || line[i] == ')'
                || line[i] == '[' || line[i] == ']' || line[i] == '&')
                    break;
                else
                {
                    word += line[i];
                    ++i;
                }
            }
            // Pop the space at the end of the current word
            if(word[word.length()-1] == ' ')
                word.pop_back();
        }
        // this is the line containing the word type, word definitions, ...
        else
        {
            if(wordInfo.empty())
                wordInfo = line;
            else
                wordInfo += "\n" + line;
        }
    }
    // Insert the last word
    trieInsert(engEngRoot, word, wordInfo, 1);
    fin.close();
}

void Application::loadVieEngDict()
{
    std::ifstream fin("data/VE_nonaccent.txt");
    int count = 0;
    std::string line, word, wordInfo;
    // Skip the first unnecessary 12 lines
    while(count < 12)
    {
        std::getline(fin, line);
        ++count;
    }
    while(std::getline(fin, line))
    {
        // this is the line containing the word
        if(line[0] == '@')
        {   
            // If it is the first word
            if(count == 12)
                ++count;
            else
            {   
                // insert previous word and its information
                trieInsert(engEngRoot, word, wordInfo, 2);
				searchDefScreen->insertVieEngItem(word, wordInfo);
                word.clear();
                wordInfo.clear();
            }
            if(line.length() >= 2)
                word = line.substr(1);
        }
        // this is the line containing the word type, word definitions, ...
        else
        {
            if(wordInfo.empty())
                wordInfo = line;
            else
                wordInfo += "\n" + line;
        }
    }
    // Insert the last word
    trieInsert(engEngRoot, word, wordInfo, 2);
    fin.close();
}

void Application::loadEmojiDict()
{
	std::ifstream inputFile("data/emoji.txt"); 
	if (!inputFile) {
		std::cout << "Falied to open file " << std::endl;
		return;
	}
	std::string line;
	while (std::getline(inputFile, line)) 
	{
		if (line.empty() || line[0] == '#')
			continue;
		std::string emojis; 
		// Find the position of ';' 
		std::size_t separatorPos = line.find_first_of(';');

		// Tách dòng thành hai phần: mã hex và phần còn lại
		std::string hexCode = line.substr(0, separatorPos);
		std::string remainingPart = line.substr(separatorPos + 1);

		// Tìm vị trí của ký tự '#' trong phần còn lại
		std::size_t hashtagPos = remainingPart.find_first_of('#');

		// Tách phần còn lại thành status và từ
		std::string status = remainingPart.substr(1, hashtagPos - 2);
		std::size_t meo = remainingPart.find_first_of(".");

		std::string word = remainingPart.substr(meo + 2);

		//xóa bỏ dấu space
		hexCode = trim(hexCode);
		status = trim(status);
		word = trim(word);
		emojis = hexCode;
		trieInsert(engEngRoot, word, emojis, 3);
	}

	inputFile.close();
}

void Application::initWindow()
{
	sf::Vector2i centerWindow(
		(sf::VideoMode::getDesktopMode().width / 2) - 600,
		(sf::VideoMode::getDesktopMode().height / 2) - 450
	);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);
}

void Application::initBackground()
{
	// Load background from file
	if (!mainScreenTex.loadFromFile("background/background1.jpg"))
		std::cout << "Background1 not found!\n";
	mainScreenTex.setSmooth(true);
	mainScreen.setTexture(mainScreenTex);

	if (!screenWithOptionsTex.loadFromFile("background/background2.jpg"))
		std::cout << "Background2 not found!\n";
	screenWithOptionsTex.setSmooth(true);
	screenWithOptions.setTexture(screenWithOptionsTex);

	// Scale the background to fit window
	float scaleX = static_cast<float>(window.getSize().x) / mainScreenTex.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / mainScreenTex.getSize().y;
	mainScreen.setScale(scaleX, scaleY);


	scaleX = static_cast<float>(window.getSize().x) / screenWithOptionsTex.getSize().x;
	scaleY = static_cast<float>(window.getSize().y) / screenWithOptionsTex.getSize().y;
	screenWithOptions.setScale(scaleX, scaleY);
}

void Application::initFont()
{
	// Load font from file
	if (!font.loadFromFile("font/SF-Pro-Rounded-Regular.otf"))
		std::cout << "Font not found!\n";
	if (!font2.loadFromFile("font/Merriweather-Regular.ttf"))
		std::cout << "Font not found!\n";
}

void Application::initSearchBar()
{
	float scaleX = mainScreen.getScale().x;
	float scaleY = mainScreen.getScale().y;
	searchBar.setPosition({ 125, 180 });
	searchBar.setBoxPosition(sf::Vector2f(247 * scaleX, 536 * scaleY));
	searchBar.setBoxSize(sf::Vector2f(2608 * scaleX, 213 * scaleY));
	searchBar.setLimit(true, 65); //set limit to 65 characters
	searchBar.setFont(font);

}

void Application::initSearchButton()
{
	searchButton.setFont(font);
	searchButton.setPosition({ 882, 175 });
	searchButton.setOutlineThickness(2);
}

void Application::initDataSetText()
{
	dataSetText.setFont(font);
	dataSetText.setPosition({ 972, 50 });
	dataSetText.setCharacterSize(20);
	dataSetText.setFillColor(sf::Color::Black);
}

void Application::initDataSetButton()
{
	dataSetButton.setFont(font);
	dataSetButton.setPosition({ 972, 72 });
	dataSetButton.setOutlineThickness(2);
	dataSetButton.setStyle(sf::Text::Style::Bold);
}

void Application::initMenuButton()
{
	menuButton.setFont(font);
	menuButton.setPosition({ 972, 163 });
	menuButton.setOutlineThickness(2);
}

void Application::initAddButton()
{
	addButton.setFont(font);
	addButton.setPosition({ 972, 253 });
	addButton.setOutlineThickness(2);
}

void Application::initDeleteButton()
{
	deleteButton.setFont(font);
	deleteButton.setPosition({ 972, 310 });
	deleteButton.setOutlineThickness(2);
}

void Application::loadAllHistory()
{
	history.loadHistory("data/historyEE.txt");
	history1.loadHistory("data/historyEV.txt");
	history2.loadHistory("data/historyVE.txt");
	history3.loadHistory("data/historyEmoji.txt");
}

void Application::initEditDefButton()
{
	editDefButton.setFont(font);
	editDefButton.setPosition({ 972, 365 });
	editDefButton.setOutlineThickness(2);
}

void Application::initDisplayBox()
{
	float scaleX = mainScreen.getScale().x;
	float scaleY = mainScreen.getScale().y;
	displayBox.setPosition(247 * scaleX, 842 * scaleY);
	displayBox.setSize(sf::Vector2f(2887 * scaleX, 2019 * scaleY));
	displayBox.setFont(font2);
	displayBox.setCharacterSize(25);
	displayBox.setCurrentDataSet(currentDataSetID);
}

void Application::initFavouriteButton()
{
	favouritebutton.setFont(font);
	favouritebutton.setPosition({ 972, 420 });
	favouritebutton.setOutlineThickness(2);
}

void Application::initSearchDefButton()
{
	searchDefButton.setFont(font);
	searchDefButton.setPosition({ 972, 475 });
	searchDefButton.setOutlineThickness(2);
}

void Application::changeDataSet()
{
	// Clear word data before change data set
	if (currentDataSetID == 0)
	{
		displayBox.clearEngEngData();
	}
	else if (currentDataSetID == 1)
	{
		displayBox.clearEngVieData();
	}
	else if (currentDataSetID == 2)
	{
		displayBox.clearVieEngData();
	}
	else if(currentDataSetID == 3)
	{
		displayBox.clearEmoji();
	}
	// Start changing data set
	if (currentDataSetID != 3)
		++currentDataSetID;
	else
		currentDataSetID = 0;
	if (currentDataSetID == 0)
		dataSetButton.setString("      EN - EN");
	else if (currentDataSetID == 1)
		dataSetButton.setString("      EN - VI");
	else if (currentDataSetID == 2)
		dataSetButton.setString("      VI - EN");
	else
		dataSetButton.setString("      Emoji");
	displayBox.setCurrentDataSet(currentDataSetID);
	proposedWord->setDataSetID(currentDataSetID);
}

void Application::run()
{
	// Load dictionaries
	newWord = new NewWord(font, font2, window);
	removeWord = new RemoveWord(font, font2, window);
	favourite = new Favourite(window);
	editDefScreen = new EditDefinitionScreen(font, font2, screenWithOptions);
	searchDefScreen = new SearchDefinitionScreen(font, font2, window);
	proposedWord = new ProposeWord();
	loadEngEngDict();
	loadEngVieDict();
	loadVieEngDict();
	loadEmojiDict();
	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			searchBar.setSelected(true);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			searchBar.setSelected(false);

		handleEvent();
		update();
		render();
	}
}

void Application::handleEvent()
{
	//Event Loop:
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			newWord->saveAddedEEWord();
			window.close();
		}	
		if (currentScreen == ScreenState::MainScreen || currentScreen == ScreenState::OptionsScreen)
		{
			if (event.type == sf::Event::TextEntered)
			{
				searchBar.typedOn(event);
				proposedWord->isTyping = true;
				std::string word = searchBar.getText();
				proposedWord->initWordList(word, engEngRoot);
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (searchBar.isMouseOver(window))
					searchBar.setSelected(true);
				else
					searchBar.setSelected(false);
				// Start searching when search button is pressed
				if (searchButton.isMouseOver(window))
				{
					std::string inputWord = searchBar.getText();
					proposedWord->isTyping = false;

					//if (inputWord!="")
					//    history.add(inputWord);
					//favouriteMain.add(inputWord);
					if (currentDataSetID == 0)
						searchInEngEngDict(inputWord);
					else if (currentDataSetID == 1)
						searchInEngVieDict(inputWord);
					else if (currentDataSetID == 2)
						searchInVieEngDict(inputWord);
					else 
						searchInEmojiDict(inputWord);
				}
				else if (menuButton.isMouseOver(window)) {
					if (currentScreen == ScreenState::MainScreen)
						currentScreen = ScreenState::OptionsScreen;
					else
						currentScreen = ScreenState::MainScreen;
				}
				else if (addButton.isMouseOver(window) && currentScreen == ScreenState::OptionsScreen)
				{
					currentScreen = ScreenState::AddScreen;
				}
				else if (deleteButton.isMouseOver(window) && currentScreen == ScreenState::OptionsScreen)
				{
					currentScreen = ScreenState::RemoveScreen;
				}
				else if (editDefButton.isMouseOver(window) && currentScreen == ScreenState::OptionsScreen)
				{
					editDefScreen->setCurrentDataSetID(currentDataSetID);
					editDefScreen->initTextToEdit(displayBox.getWord(), displayBox.getWordType()
					, displayBox.getWordDef(), displayBox.getWordExample());
					currentScreen = ScreenState::EditDefinitionScreen;
				}
				else if (favouritebutton.isMouseOver(window) && currentScreen == ScreenState::OptionsScreen)
				{
					if(currentDataSetID == 0)
						displayBox.clearEngEngData();
					else if(currentDataSetID == 1)
						displayBox.clearEngVieData();
					else if(currentDataSetID == 2)
						displayBox.clearVieEngData();
					searchBar.clear();
					favourite->setCurrentDataSet(currentDataSetID);
					favourite->addtoFile();
					favourite->loadWordsList();
					currentScreen = ScreenState::FavouriteScreen;
				}
				else if(searchDefButton.isMouseOver(window) && currentScreen == ScreenState::OptionsScreen)
				{
					if(currentDataSetID == 0)
						displayBox.clearEngEngData();
					else if(currentDataSetID == 1)
						displayBox.clearEngVieData();
					else if(currentDataSetID == 2)
						displayBox.clearVieEngData();
					searchBar.clear();
					searchDefScreen->setCurrentDataSetID(currentDataSetID);
					currentScreen = ScreenState::SearchDefinitionScreen;
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
				{
					changeDataSet();
				}
				else if (currentScreen == ScreenState::MainScreen)
				{
					favourite->likeOrNot(window);
				}
				
			}
			else if (proposedWord->setIsTyping() && proposedWord->getMousePosition(window))
			{
				proposedWord->handleEvent(event, window);
			}
		}
		else if (currentScreen == ScreenState::EditDefinitionScreen)
		{
			bool endScreen = false;
			editDefScreen->setEndScreen(endScreen);
			std::string editWordType = displayBox.getWordType();
			std::string editWordDef = displayBox.getWordDef();
			std::string editWordExample = displayBox.getWordExample();
			bool isSaved = false;
			editDefScreen->handleEvent(event, window, endScreen);
			if (endScreen)
			{
				// Display box receive the edited word type, definition and example
				editDefScreen->setEndScreen(endScreen);
				currentScreen = ScreenState::OptionsScreen;
			}
		}
		else if (currentScreen == ScreenState::AddScreen)
		{
			bool endScreen = false;
			newWord->setEndScreen(endScreen);
			newWord->handleEvent(event, window, endScreen, engEngRoot);
			if (endScreen)
			{
				newWord->setEndScreen(endScreen);
				currentScreen = ScreenState::OptionsScreen;
			}
		}
		else if (currentScreen == ScreenState::RemoveScreen)
		{
			bool endScreen = false;
			removeWord->setEndScreen(endScreen);
			removeWord->handleEvent(event, window, endScreen, engEngRoot);
			if (endScreen)
			{
				removeWord->setEndScreen(endScreen);
				currentScreen = ScreenState::OptionsScreen;
			}
		}
		else if (currentScreen == ScreenState::FavouriteScreen)
		{
			bool endScreen = false;
			favourite->setEndScreen(endScreen);
			favourite->handleEvent(event, window, endScreen);
			if (endScreen)
			{
				favourite->setEndScreen(endScreen);
				currentScreen = ScreenState::OptionsScreen;
				favourite->eraseWordList();
			}
		}
		else if(currentScreen == ScreenState::SearchDefinitionScreen)
		{
			bool endScreen = false;
			searchDefScreen->setEndScreen(endScreen);
			searchDefScreen->handleEvent(event, window, endScreen);
			if(endScreen)
			{
				searchDefScreen->setEndScreen(endScreen);
				currentScreen = ScreenState::OptionsScreen;
			}
		}
		else
		{

		}
	}
}



void Application::update()
{
	if (currentScreen == ScreenState::MainScreen)
	{
		searchButton.update(window);
		dataSetButton.update(window);
		menuButton.update(window);
		displayBox.update(window);
	}
	else if (currentScreen == ScreenState::OptionsScreen)
	{
		searchButton.update(window);
		dataSetButton.update(window);
		menuButton.update(window);
		addButton.update(window);
		deleteButton.update(window);
		editDefButton.update(window);
		favouritebutton.update(window);
		searchDefButton.update(window);
		displayBox.update(window);
	}
	else if (currentScreen == ScreenState::EditDefinitionScreen)
	{
		bool endScreen = false;
		bool isSaved = false;
		std::string editWordType;
		std::string editWordDef;
		std::string editWordExample;
		editDefScreen->update(window, endScreen, isSaved, editWordType, editWordDef, editWordExample);
		if(endScreen)
		{
			if(isSaved)
				displayBox.receiveEditText(editWordType, editWordDef, editWordExample);
			editDefScreen->setEndScreen(endScreen);
			currentScreen = ScreenState::OptionsScreen;
		}
	}
	else if (currentScreen == ScreenState::AddScreen) {
		newWord->update(window);
	}
	else if (currentScreen == ScreenState::RemoveScreen) {
		removeWord->update(window);
	}
	else if (currentScreen == ScreenState::FavouriteScreen)
	{
		favourite->update(window);
	}
	else if(currentScreen == ScreenState::SearchDefinitionScreen)
	{
		searchDefScreen->update(window);
	}
	else
	{

	}
}

void Application::drawHistory() {
	if (currentDataSetID == 0)
		history.drawTo(window);
	else if (currentDataSetID == 1)
		history1.drawTo(window);
	else if (currentDataSetID == 2)
		history2.drawTo(window);
	else
		history3.drawTo(window);
}

void Application::render()
{
    if (currentScreen == ScreenState::MainScreen) {
		window.clear(sf::Color::White);
        window.draw(mainScreen);
        searchBar.drawTo(window);
        searchButton.drawTo(window);
        dataSetButton.drawTo(window);

		drawHistory();
        //favouriteMain.drawTo(window);
        menuButton.drawTo(window);
		if (!proposedWord->setIsTyping())
		{
			displayBox.drawTo(window);
		}
        //dataSetBar.drawTo(window);
		else 
		{
			proposedWord->drawTo(window);
		}
    }
    else if(currentScreen == ScreenState::OptionsScreen) {
		window.clear(sf::Color::White);
        window.draw(screenWithOptions);
        searchBar.drawTo(window);
        searchButton.drawTo(window);
        dataSetButton.drawTo(window);

		menuButton.drawTo(window);
		addButton.drawTo(window);
		deleteButton.drawTo(window);
		editDefButton.drawTo(window);
		favouritebutton.drawTo(window);
		searchDefButton.drawTo(window);
		if (!proposedWord->setIsTyping())
		{
			displayBox.drawTo(window);
		}
		//dataSetBar.drawTo(window);
		else
		{
			proposedWord->drawTo(window);
		}
		//dataSetBar.drawTo(window);
	}
	else if (currentScreen == ScreenState::EditDefinitionScreen) {
		editDefScreen->render(window, screenWithOptions);
	}
	else if (currentScreen == ScreenState::AddScreen) {
		newWord->render(window);
	}
	else if (currentScreen == ScreenState::RemoveScreen) {
		removeWord->render(window);
	}
	else if (currentScreen == ScreenState::FavouriteScreen)
	{
		favourite->render(window);
	}
	else if(currentScreen == ScreenState::SearchDefinitionScreen)
	{
		searchDefScreen->render(window);
	}

	window.display();
}

void Application::searchInEngEngDict(std::string& inputWord)
{
    if (inputWord!="")
        history.add(inputWord, "data/historyEE.txt");
    std::string wordInfo = filterAndSearch(engEngRoot, inputWord, 0);
    if(!wordInfo.empty())
    {
        // Console
        separateEngEngExample(wordInfo);
		std::string newWordInfo = formatEngEngWordInfo(wordInfo);
        std::cout << newWordInfo << std::endl;
        // UI
        displayBox.getWordDataEngEng(inputWord, newWordInfo);
    }
    else
    {
        std::cout << "Cannot find the word" << "\n";
        displayBox.showNoEngEngDefinitions();
    }
}

void Application::searchInEngVieDict(std::string& inputWord)
{
    if (inputWord!="")
        history.add(inputWord, "data/historyEV.txt");
    std::string wordInfo = filterAndSearch(engEngRoot, inputWord, 1);
    if(!wordInfo.empty())
    {
        // Console
        std::cout << wordInfo << std::endl;
        // UI
        displayBox.getWordDataEngVie(inputWord, wordInfo);
    }
    else
    {
        std::cout << "Cannot find the word" << "\n";
        displayBox.showNoEngVieDefinitions();
    }
}

void Application::searchInVieEngDict(std::string& inputWord)
{
    if (inputWord!="")
        history.add(inputWord, "data/historyVE.txt");
    std::string wordInfo = filterAndSearch(engEngRoot, inputWord, 2);
    if(!wordInfo.empty())
    {
        // Console
        std::cout << wordInfo << std::endl;
        // UI
        displayBox.getWordDataVieEng(inputWord, wordInfo);
    }
    else
    {
        std::cout << "Cannot find the word" << "\n";
        displayBox.showNoVieEngDefinitions();
    }
}
void Application::searchInEmojiDict(std::string& inputWord)
{
	if (inputWord != "")
		history.add(inputWord, "data/historyEmoji.txt");
	std::string wordInfo = filterAndSearch(engEngRoot, inputWord, 3);
	if (!wordInfo.empty())
	{
		// Console
		std::cout << wordInfo << std::endl;
		// UI
		displayBox.setEmojiMode(true);
		displayBox.showEmojiDefinition(inputWord, wordInfo);
	}
	else
	{
		displayBox.showNoEmojiDefinition();
		std::cout << "Cannot find the word " << "\n";
	}
}

