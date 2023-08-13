#include "RandomWord.h"

RandomWord::RandomWord(sf::Font& font, sf::Font& font2, sf::RenderWindow& window):
	backButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	button1("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	button2("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	button3("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	button4("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	isBackButtonPressed(false)
{
	this->font = font;
	this->font2 = font2;
	initBackground(window);
	initBackButton();
	initButton1();
	initButton2();
	initButton3();
	initButton4();
}

void RandomWord::handleEvent(sf::Event& event, sf::RenderWindow& window, std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector, std::vector<WordDataEngVie>& vieEngVector)
{
	if (event.type == sf::Event::MouseButtonPressed)
		if (backButton.isMouseOver(window))
			isBackButtonPressed = true;
}

void RandomWord::update(sf::RenderWindow& window)
{
	backButton.update(window);
	button1.update(window);
	button2.update(window);
	button3.update(window);
	button4.update(window);
}

void RandomWord::render(sf::RenderWindow& window)
{
	window.draw(background);
	backButton.drawTo(window);
	button1.drawTo(window);
	button2.drawTo(window);
	button3.drawTo(window);
	button4.drawTo(window);
}

void RandomWord::initBackground(sf::RenderWindow& window)
{
	if (!backgroundTexture.loadFromFile("background/randomWord.jpg"))
		std::cout << "randomWord not found!\n";
	backgroundTexture.setSmooth(true);
	background.setTexture(backgroundTexture);
	float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
	background.setScale(scaleX, scaleY);
}

void RandomWord::initBackButton()
{
	backButton.setFont(font);
	backButton.setPosition({ 972, 163 });
	backButton.setOutlineThickness(2);
}

void RandomWord::initButton1()
{
	button1.setFont(font);
	button1.setPosition({ 972, 253 });
	button1.setOutlineThickness(2);
}

void RandomWord::initButton2()
{
	button2.setFont(font);
	button2.setPosition({ 972, 310 });
	button2.setOutlineThickness(2);
}

void RandomWord::initButton3()
{
	button3.setFont(font);
	button3.setPosition({ 972, 365 });
	button3.setOutlineThickness(2);
}

void RandomWord::initButton4()
{
	button4.setFont(font);
	button4.setPosition({ 972, 420 });
	button4.setOutlineThickness(2);
}