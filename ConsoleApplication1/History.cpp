#include "History.h"

History::History()
{
	font.loadFromFile("font/SF-Pro-Rounded-Regular.otf");
}

void History::add(std::string word)
{
	if (size < 18)
	{
		history.push(word);
		size++;
	}
	else
	{
		history.pop();
		history.push(word);
	}
}

void History::drawTo(sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	sf::Color grey(0,0,0,160);
	text.setFillColor(grey);
	text.setPosition(980, 320);

	std::queue<std::string> temp = history;
	while (!temp.empty())
	{
		text.setString(temp.front());
		window.draw(text);
		text.move(0, 30);
		temp.pop();
	}
}
