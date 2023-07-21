#pragma once
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
	engEngRoot(nullptr),
	history(),
	favourite(nullptr),
	currentScreen(ScreenState::MainScreen),
	editDefScreen(nullptr),
	newWord(nullptr),
	displayBox({ 72, 240 }, { 880, 610 }, sf::Color::Transparent, sf::Color::Black),
	dataSetButton("      EN - EN", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Black),
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
}

Application::~Application()
{
	trieDeleteAll(engEngRoot);
	delete editDefScreen;
	newWord->saveAddedWord();
	delete newWord;
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
                    // If that word type has more than 1 definition
                    if(line[j+1] == '1')
                        wordInfo += line.substr(i+4);
                    // If that word type has only 1 definition
                    else
                        wordInfo += line.substr(i+3);
                }
                    
                // If it is the word "See"
                else if(wordType == "See")
                    wordInfo += line.substr(i);
                // If it is a number (which means that the word has more than 1 definition for a word type)
                else
                {
                    wordInfo += "\n" + line.substr(i);
                }
                
            }
            // If there are more than 5 blanks then it is just a normal line of a definition
            else
            {
                wordInfo += " " + line.substr(i);
            }
        }
    }
    trieInsert(engEngRoot, word, wordInfo, 0); // Insert last word
    fin.close();
    newWord->loadAddedWord(engEngRoot);
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
        if(line.empty())
            continue;
        // this is the line containing the word
        if(line[0] == '@')
        {   
            // If it is the first word
            if(count == 15)
                ++count;
            else
            {   
                // insert previous word and its information
                if(isValidWord(word))
                    trieInsert(engEngRoot, word, wordInfo, 1);
                word.clear();
                wordInfo.clear();
            }
            int i = 1;
            while(line[i] != '/' && line[i] != '=' && line[i] != '(' && line[i] != ')'
            && line[i] != '[' && line[i] != ']' && line[i] != '&' && i < line.length())
            {
                word += line[i];
                ++i;
            }
            // Pop the space at the end of the current word
            if(word[word.length()-1] == ' ')
                word.pop_back();
            // If there is an open parenthesis at the middle of the word
            if(line[i] == '(')
            {
                while(line[i] != ')')
                    ++i;
                if(i < line.length()-2)
                {
                    ++i;
                    while(line[i] != '/' && line[i] != '(' && line[i] != '[' 
                    && line[i] != '=' && i < line.length())
                    {
                        word += line[i];
                        ++i;
                    }
                }
            }
            // If there is an open bracket at the middle of the word
            if(line[i] == '[')
            {
                while(line[i] != ']')
                    ++i;
                if(i < line.length()-2)
                {
                    ++i;
                    while(line[i] != '/' && line[i] != '(' && line[i] != '[' 
                    && line[i] != '=' && i < line.length())
                    {
                        word += line[i];
                        ++i;
                    }
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
                wordInfo += line;
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
        if(line.empty())
            continue;
        // this is the line containing the word
        if(line[0] == '@')
        {   
            // If it is the first word
            if(count == 12)
                ++count;
            else
            {   
                // insert previous word and its information
                if(isValidWord(word))
                    trieInsert(engEngRoot, word, wordInfo, 2);
                word.clear();
                wordInfo.clear();
            }
            word += line.substr(1);
        }
        // this is the line containing the word type, word definitions, ...
        else
        {
            if(wordInfo.empty())
                wordInfo += line;
            else
                wordInfo += "\n" + line;
        }
    }
    // Insert the last word
    trieInsert(engEngRoot, word, wordInfo, 2);
    fin.close();
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
}

void Application::initSearchBar()
{
	searchBar.setPosition({ 125, 180 });
	searchBar.setBoxPosition({ 74, 158 });
	searchBar.setBoxSize({ 800, 68 });
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

void Application::initEditDefButton()
{
	editDefButton.setFont(font);
	editDefButton.setPosition({ 972, 365 });
	editDefButton.setOutlineThickness(2);
}

void Application::initDisplayBox()
{
	displayBox.setFont(font);
	displayBox.setCharacterSize(30);
}

void Application::initFavouriteButton()
{
	favouritebutton.setFont(font);
	favouritebutton.setPosition({ 972, 420 });
	favouritebutton.setOutlineThickness(2);
}

void Application::changeDataSet()
{
    // Clear word data before change data set
    if(currentDataSetID == 0)
    {
        displayBox.clearEngEngData();
    }
    if(currentDataSetID == 1)
    {
        displayBox.clearEngVieData();
    }
    if(currentDataSetID == 2)
    {
        displayBox.clearVieEngData();
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
}

void Application::run()
{
    // Load dictionaries
    newWord = new NewWord(font, window);
    loadEngEngDict();
    loadEngVieDict();
    loadVieEngDict();
    while(window.isOpen())
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
        if(event.type == sf::Event::Closed)
            window.close();
        if(currentScreen == ScreenState::MainScreen || currentScreen == ScreenState::OptionsScreen)
        {
            if(event.type == sf::Event::TextEntered)
                searchBar.typedOn(event);
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(searchBar.isMouseOver(window))
                    searchBar.setSelected(true);
                else
                    searchBar.setSelected(false);
                // Start searching when search button is pressed
                if(searchButton.isMouseOver(window))
                {
                    std::string inputWord = searchBar.getText();
                    //if (inputWord!="")
                    //    history.add(inputWord);
                    //favouriteMain.add(inputWord);
                        
                    if(currentDataSetID == 0)
                        searchInEngEngDict(inputWord);
                    else if(currentDataSetID == 1)
                        searchInEngVieDict(inputWord);
                    else if(currentDataSetID == 2)
                        searchInVieEngDict(inputWord);
                    
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
                    
                }
                else if(editDefButton.isMouseOver(window) && currentScreen == ScreenState::OptionsScreen)
                {
                    if(editDefScreen == nullptr)
                    {
                        editDefScreen = new EditDefinitionScreen();
                    }
                    currentScreen = ScreenState::EditDefinitionScreen;
                }
                else if (favouritebutton.isMouseOver(window) && currentScreen == ScreenState::OptionsScreen)
                {
                    favouriteMain.addtoFile();
                    favourite(window);
                }
                else if(displayBox.nextButtonDrawn() && displayBox.isMouseOverNextButton(window))
                {
                    if(currentDataSetID == 0)
                        displayBox.showNextDef();
                    else if(currentDataSetID == 1)
                        displayBox.showNextEngVieDef();
                    else if(currentDataSetID == 2)
                        displayBox.showNextVieEngDef();
                }
                else if(displayBox.prevButtonDrawn() && displayBox.isMouseOverPrevButton(window))
                {
                    if(currentDataSetID == 0)
                        displayBox.showPrevDef();
                    else if(currentDataSetID == 1)
                        displayBox.showPrevEngVieDef();
                    else if(currentDataSetID == 2)
                        displayBox.showPrevVieEngDef();
                }
                else if(dataSetButton.isMouseOver(window))
                {
                    changeDataSet();
                }
                else if (currentScreen == ScreenState::MainScreen)
                {
                    favouriteMain.likeOrNot(window);
                }
               
            }
        }
        else if(currentScreen == ScreenState::EditDefinitionScreen)
        {
            bool endScreen = false;
            editDefScreen->setEndScreen(endScreen);
            editDefScreen->handleEvent(event, window, endScreen);
            if(endScreen)
            {
                editDefScreen->setEndScreen(endScreen);
                currentScreen = ScreenState::OptionsScreen;
            }
        }
        else if(currentScreen == ScreenState::AddScreen)
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
		displayBox.update(window);
	}
	else if (currentScreen == ScreenState::EditDefinitionScreen)
	{
		editDefScreen->update(window);
	}
	else if (currentScreen == ScreenState::AddScreen) {
		newWord->update(window);
	}
	else if (currentScreen == ScreenState::FavouriteScreen)
	{
		favourite->update(window);
	}
	else
	{

	}
}

void Application::render()
{
	window.clear(sf::Color::White);
	if (currentScreen == ScreenState::MainScreen) {
		window.draw(mainScreen);
		searchBar.drawTo(window);
		searchButton.drawTo(window);
		dataSetButton.drawTo(window);

		history.drawTo(window);
		//favouriteMain.drawTo(window);
		menuButton.drawTo(window);
		displayBox.drawTo(window);
		//dataSetBar.drawTo(window);
	}
	else if (currentScreen == ScreenState::OptionsScreen) {
		window.draw(screenWithOptions);
		searchBar.drawTo(window);
		searchButton.drawTo(window);
		dataSetButton.drawTo(window);

		menuButton.drawTo(window);
		addButton.drawTo(window);
		deleteButton.drawTo(window);
		editDefButton.drawTo(window);
		favouritebutton.drawTo(window);
		displayBox.drawTo(window);
		//dataSetBar.drawTo(window);
	}
	else if (currentScreen == ScreenState::EditDefinitionScreen) {
		editDefScreen->render(window);
	}
	else if (currentScreen == ScreenState::AddScreen) {
		newWord->render(window);
	}
	else if (currentScreen == ScreenState::FavouriteScreen)
	{
		favourite->render(window);
	}

	window.display();
}

void Application::searchInEngEngDict(std::string& inputWord)
{
	if (inputWord != "")
		history.add(inputWord);
	favourite->add(inputWord);
	std::string wordInfo = filterAndSearch(engEngRoot, inputWord, 0);
	if (!wordInfo.empty())
	{
		// Console
		WordData theWordData;
		extractWordData(theWordData, inputWord, wordInfo);
		theWordData.consolePrint();
		// UI
		displayBox.getWordDataEngEng(inputWord, wordInfo);

	}
	else
	{
		std::cout << "Cannot find the word" << "\n";
		displayBox.showNoDefinitions();
	}
}

void Application::searchInEngVieDict(std::string& inputWord)
{
    if (inputWord!="")
        history.add(inputWord);
    std::string wordInfo = filterAndSearch(engEngRoot, inputWord, 1);
    if(!wordInfo.empty())
    {
        // Console
        std::cout << wordInfo << std::endl;
        WordDataEngVie engVieData;
        extractEngVieData(engVieData, inputWord, wordInfo);
        engVieData.consolePrint();
        // UI
        displayBox.getWordDataEngVie(inputWord, wordInfo);
    }
    else
    {
        std::cout << "Cannot find the word" << "\n";
        displayBox.showNoEngVieDefinitions();
    }
}

void Application::searchInVieEngDict(std::string &inputWord)
{
    if (inputWord!="")
        history.add(inputWord);
    std::string wordInfo = filterAndSearch(engEngRoot, inputWord, 2);
    if(!wordInfo.empty())
    {
        // Console
        WordDataEngVie vieEngData;
        extractVieEngData(vieEngData, inputWord, wordInfo);
        vieEngData.consolePrint();
        // UI
        displayBox.getWordDataVieEng(inputWord, wordInfo);
    }
    else
    {
        std::cout << "Cannot find the word" << "\n";
        displayBox.showNoVieEngDefinitions();
    }
}
