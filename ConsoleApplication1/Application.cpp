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
    editDefButton("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    favouritebutton("",{153,42},20,sf::Color::Transparent,sf::Color::Transparent),
    engEngRoot(nullptr),
    history(),
    currentScreen(ScreenState::MainScreen),
    editDefScreen(nullptr),
    newWord(nullptr),
    displayBox({72, 240}, {880, 610}, sf::Color::Transparent, sf::Color::Black),
    dataSetBar()
{
    initWindow();
    initBackground();
    initFont();
    initSearchBar();
    initSearchButton();
    initMenuButton();
    initAddButton();
    initEditDefButton();
    initDisplayBox();
    initFavouriteButton();
}

Application::~Application()
{
    trieDeleteAll(engEngRoot);
    delete editDefScreen;
    delete newWord;
}

void Application::loadEngEngDict()
{
    std::ifstream fin("data/EE.txt");
    // Skip the first 59 lines (unnecessary lines)
    std::string line, word, wordInfo;
    int count = 0;
    while(count < 59)
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
                trieInsert(engEngRoot, word, wordInfo);
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
    trieInsert(engEngRoot, word, wordInfo); // Insert last word
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
    searchBar.setPosition({125, 180});
    searchBar.setBoxPosition({74, 158});
    searchBar.setBoxSize({800, 68});
	searchBar.setLimit(true, 65); //set limit to 65 characters
	searchBar.setFont(font);
    
}

void Application::initSearchButton()
{
    searchButton.setFont(font);
	searchButton.setPosition({ 882, 175 });
    searchButton.setOutlineThickness(2);
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

void Application::initEditDefButton()
{
    editDefButton.setFont(font);
    editDefButton.setPosition({972, 365});
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

void Application::run()
{
    // Load dictionaries
    loadEngEngDict();
    // loadEngVieDict();
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
                if(searchButton.isMouseOver(window))
                {
                    std::string inputWord = searchBar.getText();
                    if (inputWord!="")
                        history.add(inputWord);
                    std::string wordInfo = filterAndSearch(engEngRoot, inputWord);
                    if(!wordInfo.empty())
                    {
                        // Console
                        WordData theWordData;
                        extractWordData(theWordData, inputWord, wordInfo);
                        theWordData.consolePrint();
                        // UI
                        displayBox.getWordData(inputWord, wordInfo);

                    }
                    else
                    {
                        std::cout << "Cannot find the word" << "\n";
                        displayBox.showNoDefinitions();
                    }
                        
                }
                else if (menuButton.isMouseOver(window)) {
                    if (currentScreen == ScreenState::MainScreen)
                        currentScreen = ScreenState::OptionsScreen;
                    else
                        currentScreen = ScreenState::MainScreen;
                }
                else if (addButton.isMouseOver(window))
                {
                    if (newWord == nullptr)
                    {
                        newWord = new NewWord(font, window);
                    }
                    currentScreen = ScreenState::AddScreen;
                }
                else if(editDefButton.isMouseOver(window))
                {
                    if(editDefScreen == nullptr)
                    {
                        editDefScreen = new EditDefinitionScreen();
                    }
                    currentScreen = ScreenState::EditDefinitionScreen;
                }
                else if (favouritebutton.isMouseOver(window))
                {
                    Favourite(window);
                }
                else if(displayBox.nextButtonDrawn() && displayBox.isMouseOverNextButton(window))
                {
                    displayBox.showNextDef();
                }
                else if(displayBox.prevButtonDrawn() && displayBox.isMouseOverPrevButton(window))
                {
                    displayBox.showPrevDef();
                }
                else if(dataSetBar.isMouseOverSwitchButton(window))
                {
                    dataSetBar.changeCurDataSet();
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
    if(currentScreen == ScreenState::MainScreen)
    {
        searchButton.update(window);
        menuButton.update(window);
        displayBox.update(window);
    }
    else if(currentScreen == ScreenState::OptionsScreen)
    {
        searchButton.update(window);
        menuButton.update(window);
        addButton.update(window);
        editDefButton.update(window);
        favouritebutton.update(window);
        displayBox.update(window);
    }
    else if(currentScreen == ScreenState::EditDefinitionScreen)
    {
        editDefScreen->update(window);
    }
    else if(currentScreen == ScreenState::AddScreen) {
        newWord->update(window);
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
        history.drawTo(window);
        menuButton.drawTo(window);
        displayBox.drawTo(window);
        dataSetBar.drawTo(window);
    }
    else if(currentScreen == ScreenState::OptionsScreen) {
        window.draw(screenWithOptions);
        searchBar.drawTo(window);
        searchButton.drawTo(window);
        menuButton.drawTo(window);
        addButton.drawTo(window);
        editDefButton.drawTo(window);
        favouritebutton.drawTo(window);
        displayBox.drawTo(window);
        dataSetBar.drawTo(window);
    }
    else if(currentScreen == ScreenState::EditDefinitionScreen) {
        editDefScreen->render(window);
    }
    else if(currentScreen == ScreenState::AddScreen) {
        newWord->render(window);
    }
    else
    {
        
    }
    
    window.display();
}
