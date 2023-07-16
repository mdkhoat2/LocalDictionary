#ifndef FAVOUTITE_H
#define FAVOURITE_H

#include <queue>
#include <SFML/Graphics.hpp>
struct WordItem {
    std::string word;
    sf::RectangleShape deleteButton;
};
void saveWords(const std::vector<std::string>& words);
std::vector<std::string> loadWords();
void Favourite(sf::RenderWindow&window);
#endif