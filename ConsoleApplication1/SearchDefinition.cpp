#include <iostream>
#include <sstream>
#include <string>
#include "SearchDefinition.h"

SearchDefinitionScreen::SearchDefinitionScreen(sf::Font &font1, sf::Font &font2, sf::RenderWindow& window) :
    searchScreenTex(),
    searchScreen(),
    searchBar(20, sf::Color::Black, sf::Color::Transparent, true),
    backButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    dataSetButton("      EN - EN", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Black),
    searchButton("", { 35, 35 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    isEndScreen(false),
    currentDataSetID(0),
    displayBox({ 72, 250 }, { 850, 600 }, sf::Color::Transparent, sf::Color::Black)
{
    initBackground(window);
    initSearchBar(font1);
    initBackButton(font1);
    initSearchButton(font1);
    initDataSetButton(font1);
    initDisplayBox(font2);
}

void SearchDefinitionScreen::handleEvent(sf::Event event, sf::RenderWindow &window, bool &endScreen,
std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector,
std::vector<WordDataEngVie>& vieEngVector)
{
    if(event.type == sf::Event::TextEntered) {
        searchBar.typedOn(event);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if(searchBar.isMouseOver(window))
            searchBar.setSelected(true);
        else
            searchBar.setSelected(false);
        
        if(searchButton.isMouseOver(window))
        {
            std::string inputDef = searchBar.getText();
            if (currentDataSetID == 0)
                searchInEngEngItems(inputDef, engEngVector);
            else if (currentDataSetID == 1)
                searchInEngVieItems(inputDef, engVieVector);
            else if (currentDataSetID == 2)
                searchInVieEngItems(inputDef, vieEngVector);
        }

        else if(backButton.isMouseOver(window)) {
            endScreen = true;
            isEndScreen = endScreen;
            displayBox.clearData();
            displayBox.clearUIText();
            searchBar.clear();
        }
        else if(dataSetButton.isMouseOver(window))
            changeDataSet();
        else if(displayBox.nextButtonDrawn() && displayBox.isMouseOverNextButton(window))
        {
            displayBox.showNextWord();
        }
        else if(displayBox.prevButtonDrawn() && displayBox.isMouseOverPrevButton(window))
        {
            displayBox.showPrevWord();
        }
    }
}

void SearchDefinitionScreen::update(sf::RenderWindow &window)
{
    if (!isEndScreen) {
        searchButton.update(window);
        backButton.update(window);
        dataSetButton.update(window);
    }
}

void SearchDefinitionScreen::render(sf::RenderWindow &window)
{
    if (!isEndScreen) {
        window.clear(sf::Color::White);
        window.draw(searchScreen);
        window.draw(dataSet);
        searchBar.drawTo(window);
        backButton.drawTo(window);
        searchButton.drawTo(window);
        dataSetButton.drawTo(window);
        displayBox.drawTo(window);
    }
}

void SearchDefinitionScreen::setCurrentDataSetID(int theID)
{
    currentDataSetID = theID;
    if (currentDataSetID == 0)
		dataSetButton.setString("      EN - EN");
	else if (currentDataSetID == 1)
		dataSetButton.setString("      EN - VI");
	else if (currentDataSetID == 2)
		dataSetButton.setString("      VI - EN");
	else
		dataSetButton.setString("      Emoji");
    displayBox.setCurrentDataSet(theID);
}

void SearchDefinitionScreen::setEndScreen(bool val)
{
    isEndScreen = val;
}

void SearchDefinitionScreen::searchInEngEngItems(std::string& inputDef, std::vector<WordDataEngVie>& EEItems)
{
    if(!displayBox.isDataEmpty())
        displayBox.clearData();
    std::pair<std::string, EngVieDef> thePair;
    int count = 0;
    for(int i = 0; i < EEItems.size(); ++i)
    {
        for(int j = 0; j < EEItems[i].defList.size(); ++j)
        {
            size_t found = EEItems[i].defList[j].defAndExample.first.find(inputDef);
            if(found != std::string::npos)
            {
                std::cout << EEItems[i].word << std::endl; // test
                thePair.first = EEItems[i].word;
                thePair.second.wordType = EEItems[i].defList[j].wordType;
                thePair.second.defAndExample.first = EEItems[i].defList[j].defAndExample.first;
                thePair.second.defAndExample.second = EEItems[i].defList[j].defAndExample.second;
                displayBox.insertDataPair(thePair);
                ++count;
                break;
            }
        }
    }
    if(count == 0)
        displayBox.showNoWord();
    else
        displayBox.initFirstWord();
}

void SearchDefinitionScreen::searchInEngVieItems(std::string& inputDef, std::vector<WordDataEngVie>& EVItems)
{
    if(!displayBox.isDataEmpty())
        displayBox.clearData();
    std::pair<std::string, EngVieDef> thePair;
    int count = 0;
    for(int i = 0; i < EVItems.size(); ++i)
    {
        for(int j = 0; j < EVItems[i].defList.size(); ++j)
        {
            size_t found = EVItems[i].defList[j].defAndExample.first.find(inputDef);
            if(found != std::string::npos)
            {
                std::cout << EVItems[i].word << std::endl; // test
                thePair.first = EVItems[i].word;
                thePair.second.wordType = EVItems[i].defList[j].wordType;
                thePair.second.defAndExample.first = EVItems[i].defList[j].defAndExample.first;
                thePair.second.defAndExample.second = EVItems[i].defList[j].defAndExample.second;
                displayBox.insertDataPair(thePair);
                ++count;
                break;
            }
        }
    }
    if(count == 0)
        displayBox.showNoWord();
    else
        displayBox.initFirstWord();
}

void SearchDefinitionScreen::searchInVieEngItems(std::string &inputDef, std::vector<WordDataEngVie>& VEItems)
{
    if(!displayBox.isDataEmpty())
        displayBox.clearData();
    std::pair<std::string, EngVieDef> thePair;
    int count = 0;
    for(int i = 0; i < VEItems.size(); ++i)
    {
        for(int j = 0; j < VEItems[i].defList.size(); ++j)
        {
            size_t found = VEItems[i].defList[j].defAndExample.first.find(inputDef);
            if(found != std::string::npos)
            {
                std::cout << VEItems[i].word << std::endl; // test
                thePair.first = VEItems[i].word;
                thePair.second.wordType = VEItems[i].defList[j].wordType;
                thePair.second.defAndExample.first = VEItems[i].defList[j].defAndExample.first;
                thePair.second.defAndExample.second = VEItems[i].defList[j].defAndExample.second;
                displayBox.insertDataPair(thePair);
                ++count;
                break;
            }
        }
    }
    if(count == 0)
        displayBox.showNoWord();
    else
        displayBox.initFirstWord();
}

void SearchDefinitionScreen::initBackground(sf::RenderWindow &window)
{
    // Load background from file
    if (!searchScreenTex.loadFromFile("background/searchDef.jpg"))
        std::cout << "add not found!\n";
    searchScreenTex.setSmooth(true);
    searchScreen.setTexture(searchScreenTex);

    // Scale the background to fit window
    float scaleX = static_cast<float>(window.getSize().x) / searchScreenTex.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / searchScreenTex.getSize().y;
    searchScreen.setScale(scaleX, scaleY);

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

void SearchDefinitionScreen::initSearchBar(sf::Font &font)
{
    float scaleX = searchScreen.getScale().x;
	float scaleY = searchScreen.getScale().y;
	searchBar.setPosition({ 125, 180 });
	searchBar.setBoxPosition(sf::Vector2f(247 * scaleX, 536 * scaleY));
	searchBar.setBoxSize(sf::Vector2f(2608 * scaleX, 213 * scaleY));
	searchBar.setLimit(true, 200); 
	searchBar.setFont(font);
}

void SearchDefinitionScreen::initSearchButton(sf::Font &font)
{
    searchButton.setFont(font);
	searchButton.setPosition({ 882, 175 });
	searchButton.setOutlineThickness(2);
}

void SearchDefinitionScreen::initBackButton(sf::Font &font)
{
    backButton.setFont(font);
    backButton.setPosition({ 972, 163 });
    backButton.setOutlineThickness(2);
}

void SearchDefinitionScreen::initDataSetButton(sf::Font &font)
{
    dataSetButton.setFont(font);
    dataSetButton.setPosition({ 972, 72 });
    dataSetButton.setOutlineThickness(2);
    dataSetButton.setStyle(sf::Text::Style::Bold);
}

void SearchDefinitionScreen::initDisplayBox(sf::Font &font)
{
    float scaleX = searchScreen.getScale().x;
	float scaleY = searchScreen.getScale().y;
	displayBox.setPosition(247 * scaleX, 842 * scaleY);
	displayBox.setSize(sf::Vector2f(2887 * scaleX, 2019 * scaleY));
	displayBox.setFont(font);
	displayBox.setCharacterSize(25);
	displayBox.setCurrentDataSet(currentDataSetID);
}

void SearchDefinitionScreen::changeDataSet()
{
    // Start changing data set
    if (currentDataSetID == 2)
        currentDataSetID = 0;
    else
        ++currentDataSetID;

    if (currentDataSetID == 0)
        dataSetButton.setString("      EN - EN");
    else if (currentDataSetID == 1)
        dataSetButton.setString("      EN - VI");
    else if (currentDataSetID == 2)
        dataSetButton.setString("      VI - EN");
    displayBox.clearData();
    displayBox.clearUIText();
    displayBox.setCurrentDataSet(currentDataSetID);
}