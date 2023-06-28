#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
	Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor);

	// Pass font by reference:
	void setFont(sf::Font& fonts);

	void setBackColor(sf::Color color);

	void setTextColor(sf::Color color);

	void setPosition(const sf::Vector2f &point);

	void setPosition(float x, float y);

	void drawTo(sf::RenderWindow& window);

	// Check if the mouse is within the bounds of the button:
	bool isMouseOver(sf::RenderWindow& window);
private:
	sf::RectangleShape button;
	sf::Text text;

	int btnWidth;
	int btnHeight;
};

#endif