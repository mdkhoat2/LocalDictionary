#ifndef HISTORY_H
#define HISTORY_H

#include <queue>
#include <stack>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

class History
{
public:
	History();

	void add(std::string word, std::string filename);
	void drawTo(sf::RenderWindow& window);
	void loadHistory(std::string filename);
	void resetHistory();
private:
	std::vector<std::string> history;
	int size = 0;
	sf::Font font;
};


#endif