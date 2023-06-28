
#include "Application.h"

Application::Application() : videoMode(1200, 900), window(videoMode, "Dictionary"), searchBar(20, sf::Color::Black, true), searchButton("", { 50, 50 }, 20, sf::Color::Transparent, sf::Color::Transparent)
{
    initWindow();
    initBackground();
    initFont();
    initSearchBar();
    initSearchButton();
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
	searchBar.setLimit(true, 100); //set limit to 100 characters
	searchBar.setFont(font);
}

void Application::initSearchButton()
{
    searchButton.setFont(font);
	searchButton.setPosition({ 875, 170 });
}

void Application::run()
{
    while(window.isOpen())
    {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) 
        {
			searchBar.setSelected(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
        {
			searchBar.setSelected(false);
		}

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
        if(event.type == sf::Event::MouseMoved)
        {
            if(searchButton.isMouseOver(window))
            {
                searchButton.setBackColor(sf::Color::Transparent);
            }
            else
            {
                searchButton.setBackColor(sf::Color::Transparent);
            }
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            if(searchButton.isMouseOver(window))
            {
                std::cout << searchBar.getText() << "\n";
            }
        }
    }
}

void Application::update()
{

}

void Application::render()
{
    window.clear(sf::Color::White);
    window.draw(mainScreen);
    searchBar.drawTo(window);
    searchButton.drawTo(window);
    window.display();
}
