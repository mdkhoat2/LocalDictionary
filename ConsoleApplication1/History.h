#ifndef HISTORY_H
#define HISTORY_H

#include <queue>
#include <SFML/Graphics.hpp>

class History
{
public:
	History();

	void add(std::string word);
	void drawTo(sf::RenderWindow& window);

private:
	//create a queue of 20 strings
	std::queue<std::string> history;
	int size = 0;
	sf::Font font;
};


#endif