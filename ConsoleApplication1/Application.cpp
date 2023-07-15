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
    editDefButton("", {153, 42}, 20, sf::Color::Transparent, sf::Color::Transparent),
    engEngRoot(nullptr),
    vieEngRoot(nullptr),
    history(),
    currentScreen(ScreenState::MainScreen),
    editDefScreen(nullptr),
    displayBox({72, 240}, {880, 610}, sf::Color::Transparent, sf::Color::Black)
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
}

Application::~Application()
{
    trieDeleteAll(engEngRoot);
    trieDeleteAll(vieEngRoot);
    delete editDefScreen;
    editDefScreen = nullptr;
}

void Application::loadEngEngDict()
{
    std::ifstream fin("data/EE.txt");
    // Skip the first 59 lines (unnecessary lines)
    std::string line, word, wordInfo;
    bool moreThan1Def = false;
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
                moreThan1Def = false;
            }
        }
        else
        {
            // Skip leading spaces
            int i = 0;
            while(line[i] == ' ')
                ++i;
            // Read the word's information
            // The first line will definitely contain the word type
            if(wordInfo.empty()) 
            {
                std::string wordType;
                while(line[i] != ' ')
                    wordType += line[i++];
                if(isdigit(line[i+1]))
                    moreThan1Def = true;
                wordInfo += wordType + "\n" + line.substr(i+1);
            }
            else
            {
                // Check for "X:" which indicates another meaning of the same word type
                int j  = i;
                std::string numStr;
                while(line[j] != ':' && j < line.length())
                    numStr += line[j++];
                if(isNumber(numStr) && moreThan1Def)
                    wordInfo += "\n" + line.substr(i);
                else
                {
                    // Check for any other word type
                    std::string wordType;
                    while(line[i] != ' ' && i < line.length())
                        wordType += line[i++];
                    // If the word has another word type
                    if(isValidWordType(wordType))
                    {
                        wordInfo += "\n" + wordType + "\n" + line.substr(i+1);
                    }
                    // If it is a normal line
                    else if(line[i] == ' ')
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
    trieInsert(engEngRoot, word, wordInfo); // Insert last word
    fin.close();
}

void Application::loadEngVieDict()
{
    std::wifstream fin("data/EV.txt");
    if(!fin.is_open())
        std::cout << "Cannot open EV.txt" << std::endl;
    std::wstring word, line, wordInfo;
    int count = 0;
    while(std::getline(fin, line))
    {
        if(count < 15)
            ++count;
        else
        {
            if(line.empty()) // skip empty line 
                continue;
            else if(line[0] == L'@') // this line contains the word
            {
                if(count == 15) // read the first word
                    ++count;
                else
                {
                    // insert previous word
                    trieInsertVieInfo(engEngRoot, word, wordInfo);
                    word.clear();
                    wordInfo.clear();
                }
                int i = 1;
                while(line[i] != L'/' && i < line.length())
                {
                    if(isValidEngChar(line[i]))
                        word += line[i];
                    ++i;
                }
                if(word[word.length()-1] == ' ')
                    word.pop_back();
            }
            else // this line contains word information
            {   
                wordInfo += line + L"\n";
            }
        } 
    }
    trieInsertVieInfo(engEngRoot, word, wordInfo);
    
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
                        WordData theWordData;
                        extractWordData(theWordData, inputWord, wordInfo);
                        theWordData.consolePrint();
                        displayBox.setText(wordInfo);
                    }
                    else
                        std::cout << "Cannot find the word" << "\n";
                }
                else if (menuButton.isMouseOver(window)) {
                    if (currentScreen == ScreenState::MainScreen)
                        currentScreen = ScreenState::OptionsScreen;
                    else
                        currentScreen = ScreenState::MainScreen;
                }
                else if (addButton.isMouseOver(window))
                {
                }
                else if(editDefButton.isMouseOver(window))
                {
                    if(editDefScreen == nullptr)
                    {
                        editDefScreen = new EditDefinitionScreen();
                    }
                    currentScreen = ScreenState::EditDefinitionScreen;
                }
                else
                {

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
                currentScreen = ScreenState::MainScreen;
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
        displayBox.update(window);
    }
    else if(currentScreen == ScreenState::EditDefinitionScreen)
    {
        editDefScreen->update(window);
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
    }
    else if(currentScreen == ScreenState::OptionsScreen) {
        window.draw(screenWithOptions);
        searchBar.drawTo(window);
        searchButton.drawTo(window);
        menuButton.drawTo(window);
        addButton.drawTo(window);
        editDefButton.drawTo(window);
        displayBox.drawTo(window);
    }
    else if(currentScreen == ScreenState::EditDefinitionScreen) {
        editDefScreen->render(window);
    }
    else {

    }
    
    window.display();
}
