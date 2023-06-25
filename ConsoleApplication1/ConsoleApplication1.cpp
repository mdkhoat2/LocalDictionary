#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "textbox.h"
#include "button.h"

int main() {
	//create window
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 600, (sf::VideoMode::getDesktopMode().height / 2) - 450);
	window.create(sf::VideoMode(1200, 900), "Dictionary");
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);

	//load background
	sf::Texture texture1;
	if (!texture1.loadFromFile("background/background1.jpg"))
		std::cout << "Background1 not found!\n";
	texture1.setSmooth(true);
	sf::Texture texture2;
	if (!texture2.loadFromFile("background/background2.jpg"))
		std::cout << "Background2 not found!\n";
	texture2.setSmooth(true);
	sf::Sprite sprite1(texture1);
	sf::Sprite sprite2(texture2);

	//scale the background to fit window
	float scaleX = static_cast<float>(window.getSize().x) / texture1.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / texture1.getSize().y;
	sprite1.setScale(scaleX, scaleY);
	sprite2.setScale(scaleX, scaleY);

	//load font
	sf::Font font;
	//if (!font.loadFromFile("arial.ttf"))
	//	std::cout << "Font not found!\n";
	if (!font.loadFromFile("font/SF-Pro-Rounded-Regular.otf"))
		std::cout << "Font not found!\n";

	//create textbox
	Textbox text1(20, sf::Color::Black, true);
	text1.setPosition({ 125, 180 });
	text1.setLimit(true, 100); //set limit to 100 characters
	text1.setFont(font);

	//create button
	Button btn1("", { 50, 50 }, 20, sf::Color::Transparent, sf::Color::Transparent);
	btn1.setFont(font);
	btn1.setPosition({ 875, 170 });
	
	//Main Loop:
	while (window.isOpen()) {

		sf::Event Event;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			text1.setSelected(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			text1.setSelected(false);
		}

		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();
			case sf::Event::TextEntered:
				text1.typedOn(Event);
			case sf::Event::MouseMoved:
				if (btn1.isMouseOver(window)) {
					btn1.setBackColor(sf::Color::Magenta);
				}
				else {
					btn1.setBackColor(sf::Color::Green);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (btn1.isMouseOver(window)) {
					std::cout << text1.getText() << "\n";
				}
			}
		}
		
		//clear
		window.clear(sf::Color::White);

		window.draw(sprite1);
		text1.drawTo(window);
		btn1.drawTo(window);
		window.display();
	}
}