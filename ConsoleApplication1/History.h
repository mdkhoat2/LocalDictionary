#ifndef HISTORY_H
#define HISTORY_H

#include <queue>
#include <stack>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Button.h"

class History
{
public:
	History();

	void add(std::string word, std::string filename);
	void drawTo(sf::RenderWindow& window);
	void drawToFull(sf::RenderWindow& window, int& page);
	void loadHistory(std::string filename);
	void resetHistory();
	int getSize();
private:
	std::vector<std::string> history;
	int size = 0;
	sf::Font font;
};

class HistoryScreen {
public:
	HistoryScreen(sf::Font& font, sf::RenderWindow& window, History& history0, History& history1, History& history2, History& history3);
	void handleEvent(sf::Event& event, sf::RenderWindow& window, int& id, History& history0, History& history1, History& history2, History& history3);
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window, int& id, History& history0, History& history1, History& history2, History& history3);
	void updatePage(History& history0, History& history1, History& history2, History& history3);
	bool isBackButtonPressed;
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Texture prevButtonTex;
	sf::Sprite prevButtonSprite;

	sf::Texture nextButtonTex;
	sf::Sprite nextButtonSprite;

	sf::Font font;

	Button backButton;
	int maxPage0;
	int page0;
	int maxPage1;
	int page1;
	int maxPage2;
	int page2;
	int maxPage3;
	int page3;
private:
	bool isMouseOverNextButton(sf::RenderWindow& window);
	bool isMouseOverPrevButton(sf::RenderWindow& window);
	void initBackground(sf::RenderWindow& window);
	void initSprites();
	void initBackButton();
};


#endif