#include "History.h"

History::History()
{
	font.loadFromFile("font/SF-Pro-Display-Medium.otf");
}

void History::add(std::string word, std::string filename)
{
	history.push_back(word);
	std::ofstream fout(filename, std::ios_base::app);
	fout << std::endl << word;
	fout.close();
}

void History::drawTo(sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	sf::Color grey(0,0,0,160);
	sf::Color myBlue(0, 32, 96);
	text.setFillColor(grey);
	text.setPosition(985, 280); //972 to 1125 (163 width)
	int size = history.size();
	

	for (int i = 0; i < 14; i++) {
		if (size - 1 - i < 0)
			break;
		
		std::string temp = history[size - 1 - i];
		if (temp.size() >= 14)
			temp = temp.substr(0, 11) + "...";
		text.setString(temp);
		float centerX = (972 + 1125 - text.getLocalBounds().width) / 2;
		text.setPosition(centerX, text.getPosition().y);
		window.draw(text);
		text.move(0, 40);
	}
	/*while (!temp.empty())
	{
		text.setString(temp.front());
		if (temp.front().size() >= 15)
			text.setCharacterSize(15);
		else
			text.setCharacterSize(20);
		window.draw(text);
		text.move(0, 30);
		temp.pop();
	}*/
}

void History::loadHistory(std::string filename)
{
	std::ifstream fin(filename);
	if (!fin.is_open()) {
		throw std::runtime_error("Failed to open file: " + filename);
	}
	std::string temp;
	while (std::getline(fin,temp)) {
		history.push_back(temp);
	}
	fin.close();
}

void History::resetHistory()
{
	history.clear();
}
