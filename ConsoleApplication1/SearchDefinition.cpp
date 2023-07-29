
#include "SearchDefinition.h"

SearchDefinitionScreen::SearchDefinitionScreen(sf::Font &font1, sf::Font &font2, sf::RenderWindow& window) :
    searchScreenTex(),
    searchScreen(),
    searchBar(20, sf::Color::Black, sf::Color::Transparent, true),
    backButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    dataSetButton("      EN - EN", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Black),
    searchButton("", { 35, 35 }, 20, sf::Color::Transparent, sf::Color::Transparent),
    isEndScreen(false),
    currentDataSetID(0)
{
    initBackground(window);
    initSearchBar(font1);
    initBackButton(font1);
    initSearchButton(font1);
    initDataSetButton(font1);
}

void SearchDefinitionScreen::handleEvent(sf::Event event, sf::RenderWindow &window, bool &endScreen)
{
    if (event.type == sf::Event::TextEntered) {
        searchBar.typedOn(event);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (searchBar.isMouseOver(window))
            searchBar.setSelected(true);
        else
            searchBar.setSelected(false);

        if (backButton.isMouseOver(window)) {
            endScreen = true;
            isEndScreen = endScreen;
        }
        else if (dataSetButton.isMouseOver(window))
            changeDataSet();
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
}

void SearchDefinitionScreen::setEndScreen(bool val)
{
    isEndScreen = val;
}

void SearchDefinitionScreen::initBackground(sf::RenderWindow &window)
{
    // Load background from file
    if (!searchScreenTex.loadFromFile("background/add.jpg"))
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

void SearchDefinitionScreen::changeDataSet()
{
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
