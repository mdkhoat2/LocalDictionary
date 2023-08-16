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
	sf::Color grey(0, 0, 0, 160);
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

void History::drawToFull(sf::RenderWindow& window, int& page)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	for (int i = 0; i < 20; i++) {
		int index = 20 * (page - 1) + i;
		if (index >= history.size())
			break;
		text.setString(history[index]);
		text.setPosition(125, 180 + 30 * i);
		window.draw(text);
	}
}

void History::loadHistory(std::string filename)
{
	std::ifstream fin(filename);
	if (!fin.is_open()) {
		throw std::runtime_error("Failed to open file: " + filename);
	}
	std::string temp;
	while (std::getline(fin, temp)) {
		history.push_back(temp);
	}
	fin.close();
}

void History::resetHistory()
{
	history.clear();
}

int History::getSize()
{
	return history.size();
}

HistoryScreen::HistoryScreen(sf::Font& _font, sf::RenderWindow& window, History& history0, History& history1, History& history2, History& history3) :
	backButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent)
{
	font = _font;
	initBackground(window);
	initSprites();
	initBackButton();
	maxPage0 = history0.getSize() / 20 + 1;
	page0 = 1;
	maxPage1 = history1.getSize() / 20 + 1;
	page1 = 1;
	maxPage2 = history2.getSize() / 20 + 1;
	page2 = 1;
	maxPage3 = history3.getSize() / 20 + 1;
	page3 = 1;
	isBackButtonPressed = false;
}

bool HistoryScreen::isMouseOverNextButton(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	return nextButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool HistoryScreen::isMouseOverPrevButton(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	return prevButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void HistoryScreen::handleEvent(sf::Event& event, sf::RenderWindow& window, int& id, History& history0, History& history1, History& history2, History& history3)
{

	if (event.type == sf::Event::MouseButtonPressed) {
		if (backButton.isMouseOver(window)) {
			isBackButtonPressed = true;
		}
		else if (isMouseOverNextButton(window)) {
			if (id == 0) {
				if (page0 < maxPage0)
					page0++;
			}
			else if (id == 1) {
				if (page1 < maxPage1)
					page1++;
			}
			else if (id == 2) {
				if (page2 < maxPage2)
					page2++;
			}
			else if (id == 3) {
				if (page3 < maxPage3)
					page3++;
			}
		}
		else if (isMouseOverPrevButton(window)) {
			if (id == 0) {
				if (page0 > 1)
					page0--;
			}
			else if (id == 1) {
				if (page1 > 1)
					page1--;
			}
			else if (id == 2) {
				if (page2 > 1)
					page2--;
			}
			else if (id == 3) {
				if (page3 > 1)
					page3--;
			}
		}
	}
}

void HistoryScreen::update(sf::RenderWindow& window)
{
	backButton.update(window);
}


void HistoryScreen::render(sf::RenderWindow& window, int& id, History& history0, History& history1, History& history2, History& history3)
{
	window.draw(background);
	backButton.drawTo(window);
	if (id == 0) {
		if (page0 < maxPage0)
			window.draw(nextButtonSprite);
		if (page0 > 1)
			window.draw(prevButtonSprite);
		history0.drawToFull(window, page0);
	}
	else if (id == 1) {
		if (page1 < maxPage1)
			window.draw(nextButtonSprite);
		if (page1 > 1)
			window.draw(prevButtonSprite);
		history1.drawToFull(window, page1);
	}
	else if (id == 2) {
		if (page2 < maxPage2)
			window.draw(nextButtonSprite);
		if (page2 > 1)
			window.draw(prevButtonSprite);
		history2.drawToFull(window, page2);
	}
	else if (id == 3) {
		if (page3 < maxPage3)
			window.draw(nextButtonSprite);
		if (page3 > 1)
			window.draw(prevButtonSprite);
		history3.drawToFull(window, page3);
	}
}

void HistoryScreen::updatePage(History& history0, History& history1, History& history2, History& history3)
{
	maxPage0 = history0.getSize() / 20 + 1;

	maxPage1 = history1.getSize() / 20 + 1;

	maxPage2 = history2.getSize() / 20 + 1;

	maxPage3 = history3.getSize() / 20 + 1;

}

void HistoryScreen::initBackground(sf::RenderWindow& window)
{
	if (!backgroundTexture.loadFromFile("background/history.jpg"))
		std::cout << "randomWord not found!\n";
	backgroundTexture.setSmooth(true);
	background.setTexture(backgroundTexture);
	float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
	background.setScale(scaleX, scaleY);
}

void HistoryScreen::initSprites()
{
	if (!nextButtonTex.loadFromFile("background/next-button.png"))
		std::cout << "Cannot load next button texture" << std::endl;
	nextButtonTex.setSmooth(true);

	if (!prevButtonTex.loadFromFile("background/prev-button.png"))
		std::cout << "Cannot load prev button texture" << std::endl;
	prevButtonTex.setSmooth(true);

	nextButtonSprite.setTexture(nextButtonTex);
	nextButtonSprite.setTextureRect(sf::IntRect(65, 46, 86, 85));
	nextButtonSprite.setScale(0.5f, 0.5f);

	prevButtonSprite.setTexture(prevButtonTex);
	prevButtonSprite.setTextureRect(sf::IntRect(65, 46, 86, 85));
	prevButtonSprite.setScale(0.5f, 0.5f);

	nextButtonSprite.setPosition(870, 800);
	prevButtonSprite.setPosition(100, 800);
}

void HistoryScreen::initBackButton()
{
	backButton.setFont(font);
	backButton.setPosition({ 972, 163 });
	backButton.setOutlineThickness(2);
}
