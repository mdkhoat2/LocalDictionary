#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
	Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor);
	~Button();
	// Pass font by reference:
	void setFont(const sf::Font& font);

	void setBackColor(const sf::Color &color);

	void setTextColor(const sf::Color &color);

	void setPosition(const sf::Vector2f &point);

	void setPosition(float x, float y);

	void setOutlineThickness(float thickness);

	void drawTo(sf::RenderWindow& window);

	// Check if the mouse is within the bounds of the button:
	bool isMouseOver(sf::RenderWindow& window);

	void update(sf::RenderWindow& window);
private:
	sf::Text text;
	sf::RectangleShape button;
	
	// For buttons with texture
	sf::Texture* buttonTex;
	sf::Sprite* buttonSprite;

	int btnWidth;
	int btnHeight;
};

#endif