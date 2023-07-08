#pragma once
#include <fstream>
#include "Application.h"


Application::Application() :
    videoMode(1200, 900),
    window(videoMode, "Dictionary"),
    searchBar(20, sf::Color::Black, true),
    searchButton("", { 35, 35 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    menuButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    engEngRoot(nullptr),
    vieEngRoot(nullptr),
    history()
{
    initWindow();
    initBackground();
    initFont();
    initSearchBar();
    initSearchButton();
    initMenuButton();
}

Application::~Application()
{
    trieDeleteAll(engEngRoot);
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
	searchBar.setLimit(true, 65); //set limit to 65 characters
	searchBar.setFont(font);
}

void Application::initSearchButton()
{
    searchButton.setFont(font);
	searchButton.setPosition({ 882, 175 });
    searchButton.button.setOutlineThickness(2);
}

void Application::initMenuButton()
{
	menuButton.setFont(font);
	menuButton.setPosition({ 972, 163 });
    menuButton.button.setOutlineThickness(2);
}

void Application::run()
{
    // Load dictionaries
    loadEngEngDict();
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
        if(event.type == sf::Event::TextEntered)
            searchBar.typedOn(event);
        if(event.type == sf::Event::MouseButtonPressed)
        {
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
                }
                else
                    std::cout << "Cannot find the word" << "\n";
            }
        }
    }
}

void Application::update()
{
    sf::Color grey(0, 0, 0, 120);
    if (searchButton.isMouseOver(window))
        searchButton.button.setOutlineColor(grey);
    else
        searchButton.button.setOutlineColor(sf::Color::Transparent);
    if (menuButton.isMouseOver(window))
        menuButton.button.setOutlineColor(grey);
    else
        menuButton.button.setOutlineColor(sf::Color::Transparent);
}

void Application::render()
{
    window.clear(sf::Color::White);
    window.draw(mainScreen);
    searchBar.drawTo(window);
    searchButton.drawTo(window);
    menuButton.drawTo(window);
    history.drawTo(window);
    window.display();
}
