#ifndef FAVOUTITE_H
#define FAVOURITE_H

#include <queue>
#include <SFML/Graphics.hpp>
struct WordItem {
	std::string word;
	sf::RectangleShape deleteButton;
};
struct WordFavouriteButton
{
	std::string word;
	sf::RectangleShape favouriteButton;
	bool liked = false;
};
void saveWords(const std::vector<std::string>& words);

std::vector<std::string> loadWords();

void favourite(sf::RenderWindow& window);

bool checkStringInFile(const std::string& file_path, const std::string& target_string);

void appendStringToFile(const std::string& file_path, const std::string& target_string);

class Favourite
{
public:
	Favourite();
	void add(std::string word);

	void drawTo(sf::RenderWindow& window);

	void addtoFile();

	void likeOrNot(sf::RenderWindow& window);

	int posX;
	int posY;

private:
	std::vector<WordFavouriteButton>favourite;
	sf::Texture favouriteTexture1, favouriteTexture2;
	sf::Sprite favouriteImage1, favouriteImage2;
	sf::Font font;
};
#endif