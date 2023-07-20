#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include"Favourite.h"

void saveWords(const std::vector<std::string>& words) {
	std::ofstream file("favorite_words.txt");
	if (file.is_open()) {
		for (const std::string& word : words) {
			file << word << std::endl;
		}
		file.close();
	}
}

std::vector<std::string> loadWords() {
	std::vector<std::string> words;
	std::ifstream file("favorite_words.txt");
	if (file.is_open()) {
		std::string word;
		while (std::getline(file, word)) {
			words.push_back(word);
		}
		file.close();
	}
	return words;
}

bool checkStringInFile(const std::string& file_path, const std::string& target_string) {
	std::ifstream file(file_path);
	std::string line;
	while (std::getline(file, line)) {
		if (line == target_string) {
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}

void appendStringToFile(const std::string& file_path, const std::string& target_string) {
	std::ofstream file(file_path, std::ios::app);
	if (file.is_open()) {
		file << target_string << std::endl;
		file.close();
		// std::cout << "String has been appended to the file." << std::endl;
	}
	else {
		std::cout << "Unable to open the file." << std::endl;
	}
}


void favourite(sf::RenderWindow& window)
{
	window.setKeyRepeatEnabled(true);

	sf::Font font;
	if (!font.loadFromFile("font/SF-Pro-Rounded-Regular.otf"))
	{
		std::cout << "Failed to load font!" << std::endl;
		return;
	}
	std::string filePath = "favorite_words.txt";
	std::vector<std::string> favoriteWords = loadWords();
	std::vector<WordItem> wordItems;

	sf::RectangleShape addButton(sf::Vector2f(35, 35));
	addButton.setFillColor(sf::Color::Transparent);
	addButton.setPosition(882, 175);

	sf::RectangleShape backButton(sf::Vector2f(153, 62));
	backButton.setFillColor(sf::Color::Transparent);
	backButton.setPosition(972, 163);

	sf::RectangleShape addButtonfake(sf::Vector2f(40, 40));
	sf::Texture deletebuttonTexture;
	sf::Sprite deleteButtonImage;
	if (!deletebuttonTexture.loadFromFile("background/buttondelete.jpg"))
	{
		std::cout << "Falied to load image";
		return;
	}
	deleteButtonImage.setTexture(deletebuttonTexture);
	deleteButtonImage.setScale(static_cast<float>(addButtonfake.getSize().x / deletebuttonTexture.getSize().x), static_cast<float>(addButtonfake.getSize().y / deletebuttonTexture.getSize().y));
	for (const std::string& word : favoriteWords) {
		WordItem wordItem;
		wordItem.word = word;
		wordItem.deleteButton.setSize(sf::Vector2f(40, 40));
		wordItem.deleteButton.setFillColor(sf::Color(28, 199, 54));
		wordItems.push_back(wordItem);
	}

	float posY = 260;
	for (WordItem& wordItem : wordItems)
	{
		if (posY == 610)
		{
			posY = 260;
		}
		wordItem.deleteButton.setPosition(window.getSize().x - wordItem.deleteButton.getSize().x - 280, posY);
		posY += 50;
	}
	//handle if user adds the word already in existence.
	sf::Time t1 = sf::seconds(1.5f);
	sf::Clock clock;
	sf::Time elapse;
	sf::Text existed;
	existed.setFont(font);
	existed.setString("This word has been added before !");
	existed.setFillColor(sf::Color::Black);
	existed.setCharacterSize(33);
	existed.setPosition(270, 630);
	bool exist = false;
	// 
	sf::Texture backgroundTexture;
	sf::Sprite backgroundImage;
	if (!backgroundTexture.loadFromFile("background/favourite.jpg"))
	{
		std::cout << "Failed to load image!" << std::endl;
		return;
	}
	backgroundTexture.setSmooth(true);
	backgroundImage.setTexture(backgroundTexture);
	backgroundImage.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x, static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

	bool isAddingWord = false;
	std::string newWord;
	bool isTyping = false;
	bool isHoveringButton = false;
	//
	sf::RectangleShape hoverButton(sf::Vector2f(35, 35));
	hoverButton.setFillColor(sf::Color::Transparent);
	hoverButton.setOutlineThickness(2);
	hoverButton.setOutlineColor(sf::Color(0, 0, 0, 120));
	//
	bool isHoveringDeleteButton = false;
	sf::RectangleShape hoverdeleteButton(sf::Vector2f(40, 40));
	hoverdeleteButton.setFillColor(sf::Color::Transparent);
	hoverdeleteButton.setOutlineThickness(2);
	hoverdeleteButton.setOutlineColor(sf::Color(0, 0, 0, 120));
	//
	bool isHoveringBackButton = false;
	sf::RectangleShape hoverBackButton(sf::Vector2f(153, 62));
	hoverBackButton.setFillColor(sf::Color::Transparent);
	hoverBackButton.setOutlineThickness(2);
	hoverBackButton.setOutlineColor(sf::Color(0, 0, 0, 120));

	sf::RectangleShape typeBar(sf::Vector2f(800, 68));
	typeBar.setFillColor(sf::Color::Transparent);
	typeBar.setPosition(74, 158);
	//Next button
	sf::RectangleShape nextButton(sf::Vector2f(80, 80));
	nextButton.setFillColor(sf::Color::Transparent);
	nextButton.setPosition(800, 700);
	//Prev button
	sf::RectangleShape prevButton(sf::Vector2f(80, 80));
	prevButton.setFillColor(sf::Color::Transparent);
	prevButton.setPosition(150, 700);
	//
	sf::Texture prevButtonTexture, nextButtonTexture;
	sf::Sprite prevButtonImage, nextButtonImage;
	//
	if (!prevButtonTexture.loadFromFile("background/prev-button.png"))
	{
		std::cout << "Falied to load from file" << std::endl;
	}
	prevButtonTexture.setSmooth(true);
	prevButtonImage.setTexture(prevButtonTexture);
	prevButtonImage.setScale(sf::Vector2f(80.f / prevButtonTexture.getSize().x, 80.f / prevButtonTexture.getSize().y));
	if (!nextButtonTexture.loadFromFile("background/next-button.png"))
	{
		std::cout << "Falied to load from file" << std::endl;
	}
	nextButtonTexture.setSmooth(true);
	nextButtonImage.setTexture(nextButtonTexture);
	nextButtonImage.setScale(sf::Vector2f(80.f / nextButtonTexture.getSize().x, 80.f / nextButtonTexture.getSize().y));
	//Xu ly neu danh sach qua nhieu tu;
	int currentPage = 1;
	int numberPage;
	if (wordItems.size() % 7 == 0)
	{
		numberPage = wordItems.size() / 7;
	}
	else
	{
		numberPage = (wordItems.size() / 7) + 1;
	}


	//
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					if (addButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						if (checkStringInFile(filePath, newWord) && newWord != "")
						{
							exist = true;
						}
						if (newWord != "" && !checkStringInFile(filePath, newWord))
						{
							favoriteWords.push_back(newWord);
							if (posY == 610)
							{
								posY = 260;
							}
							WordItem wordItem;
							wordItem.word = newWord;
							wordItem.deleteButton.setSize(sf::Vector2f(40, 40));
							wordItem.deleteButton.setFillColor(sf::Color(28, 199, 54));
							wordItem.deleteButton.setPosition(window.getSize().x - wordItem.deleteButton.getSize().x - 280, posY);
							wordItems.push_back(wordItem);
							posY += 50;
							saveWords(favoriteWords);
							if (wordItems.size() % 7 == 1)
							{
								numberPage += 1;
							}

						}
						clock.restart();
						isAddingWord = false;
						newWord = "";
						isTyping = false;

					}
					else if (nextButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && currentPage < numberPage)
					{
						currentPage += 1;
					}
					else if (prevButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && currentPage != 1)
					{
						currentPage -= 1;
					}
					else if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						return;
					}
					else if (typeBar.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						isAddingWord = true;
						isTyping = true;
					}
					else {
						int p = 0;
						int first3 = (currentPage - 1) * 7;
						int last3 = currentPage * 7;
						for (auto it = wordItems.begin(); it != wordItems.end(); ++it) {
							p++;
							if (it->deleteButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && first3 < p && p <= last3) {
								favoriteWords.erase(std::remove(favoriteWords.begin(), favoriteWords.end(), it->word), favoriteWords.end());
								wordItems.erase(it);
								saveWords(favoriteWords);
								posY = 260;
								for (WordItem& wordItem : wordItems)
								{
									if (posY == 610)
									{
										posY = 260;
									}
									wordItem.deleteButton.setPosition(window.getSize().x - wordItem.deleteButton.getSize().x - 280, posY);
									posY += 50;
								}
								if (wordItems.size() != 0)
								{
									if (wordItems.size() % 7 == 0)
									{
										if (currentPage == numberPage)
										{
											currentPage -= 1;
										}
										numberPage -= 1;
									}
								}
								break;
							}
						}
					}
				}
			}
			else if (event.type == sf::Event::TextEntered && isTyping)
			{
				if (event.text.unicode == 8)
				{
					if (!newWord.empty()) {
						newWord.pop_back();
					}
				}
				else {
					newWord += event.text.unicode;
				}
			}
		}
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		std::string word1 = "";
		int m = 0;
		int first1 = (currentPage - 1) * 7;
		int last1 = currentPage * 7;
		for (const WordItem& meo : wordItems)
		{
			m++;
			if (meo.deleteButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && first1 < m && m <= last1)
			{
				isHoveringDeleteButton = true;
				word1 = meo.word;
			}
		}
		if (word1 == "")
		{
			isHoveringDeleteButton = false;
		}
		if (addButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			isHoveringButton = true;
		}
		else
		{
			isHoveringButton = false;
		}

		if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			isHoveringBackButton = true;
		}
		else
		{
			isHoveringBackButton = false;
		}
		if (exist == true)
		{
			if (clock.getElapsedTime() >= t1 && exist)
			{
				exist = false;
			}
		}
		window.clear();
		window.draw(backgroundImage);
		window.draw(addButton);
		window.draw(backButton);
		window.draw(typeBar);
		if (currentPage == 1 && numberPage > 1)
		{
			window.draw(nextButton);
			nextButtonImage.setPosition(nextButton.getPosition().x, nextButton.getPosition().y);
			window.draw(nextButtonImage);
		}
		if (currentPage > 1 && currentPage < numberPage)
		{
			window.draw(nextButton);
			nextButtonImage.setPosition(nextButton.getPosition().x, nextButton.getPosition().y);
			window.draw(nextButtonImage);
			window.draw(prevButton);
			prevButtonImage.setPosition(prevButton.getPosition().x, prevButton.getPosition().y);
			window.draw(prevButtonImage);
		}
		if (currentPage == numberPage && currentPage != 1)
		{
			window.draw(prevButton);
			prevButtonImage.setPosition(prevButton.getPosition().x, prevButton.getPosition().y);
			window.draw(prevButtonImage);
		}
		m = 0;
		for (WordItem& wordItem : wordItems)
		{
			m++;
			if (first1 < m && m <= last1 && m <= wordItems.size())
			{
				window.draw(wordItem.deleteButton);
				deleteButtonImage.setPosition(wordItem.deleteButton.getPosition().x, wordItem.deleteButton.getPosition().y);
				window.draw(deleteButtonImage);
				sf::Text wordText(wordItem.word, font, 20);
				wordText.setFillColor(sf::Color::Black);
				wordText.setPosition(140, wordItem.deleteButton.getPosition().y + 10);
				window.draw(wordText);
			}
		}
		//
		if (exist == true)
		{
			window.draw(existed);
		}
		//
		if (isHoveringDeleteButton)
		{
			int h = 0;
			for (const WordItem meo : wordItems)
			{
				h++;
				if (meo.word == word1 && first1 < h && h <= last1)
				{
					word1 = "";
					hoverdeleteButton.setPosition(meo.deleteButton.getPosition());
					window.draw(hoverdeleteButton);
				}
			}
		}
		if (isHoveringButton)
		{
			hoverButton.setPosition(addButton.getPosition());
			window.draw(hoverButton);
		}
		if (isHoveringBackButton)
		{
			hoverBackButton.setPosition(backButton.getPosition());
			window.draw(hoverBackButton);
		}
		if (isAddingWord) {
			sf::Text newText(newWord, font, 20);
			newText.setFillColor(sf::Color::Black);
			newText.setPosition(125, 180);
			window.draw(newText);
		}

		if (isTyping) {
			sf::Text underlineText(newWord + "_", font, 20);
			underlineText.setFillColor(sf::Color::Black);
			underlineText.setPosition(125, 180);
			window.draw(underlineText);
		}

		window.display();
	}

	return;
}

Favourite::Favourite()
{
	font.loadFromFile("font/SF-Pro-Rounded-Regular.otf");

	//chua thich
	if (!favouriteTexture1.loadFromFile("background/favourite2Button.png"))
	{
		std::cout << "Falied to load image ";
	}
	favouriteTexture1.setSmooth(true);
	favouriteImage1.setTexture(favouriteTexture1);
	favouriteImage1.setScale(sf::Vector2f(30.f / favouriteTexture1.getSize().x, 30.f / favouriteTexture1.getSize().y));
	if (!favouriteTexture2.loadFromFile("background/favouriteButton.png"))
	{
		std::cout << "Falied to load image ";
	}
	favouriteTexture2.setSmooth(true);
	favouriteImage2.setTexture(favouriteTexture2);
	favouriteImage2.setScale(sf::Vector2f(30.f / favouriteTexture2.getSize().x, 30.f / favouriteTexture2.getSize().y));
	posX = 1052;
	posY = 320;
}

void Favourite::add(std::string word)
{
	WordFavouriteButton newWord;
	newWord.word = word;
	newWord.favouriteButton.setSize(sf::Vector2f(30, 30));
	newWord.favouriteButton.setFillColor(sf::Color::Red);
	newWord.favouriteButton.setPosition(posX, posY);
	posY += 30;
	favourite.push_back(newWord);
}

void Favourite::drawTo(sf::RenderWindow& window)
{
	for (const WordFavouriteButton& cur : favourite)
	{
		window.draw(cur.favouriteButton);
		if (cur.liked == true)
		{
			favouriteImage2.setPosition(cur.favouriteButton.getPosition().x, cur.favouriteButton.getPosition().y);
			window.draw(favouriteImage2);
		}
		else
		{
			favouriteImage1.setPosition(cur.favouriteButton.getPosition().x, cur.favouriteButton.getPosition().y);
			window.draw(favouriteImage1);
		}
	}
}

void Favourite::addtoFile()
{
	std::ofstream fo;
	std::ifstream fi;
	std::string filePath = "favorite_words.txt";
	for (auto it = favourite.begin(); it != favourite.end(); it++)
	{
		if (!checkStringInFile(filePath, it->word) && it->liked == true)
		{
			appendStringToFile(filePath, it->word);
		}
	}

}

void Favourite::likeOrNot(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	for (auto it = favourite.begin(); it != favourite.end(); it++)
	{
		if (it->favouriteButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			if (it->liked == false)
			{
				it->liked = true;
			}
			else
			{
				it->liked = false;
			}
		}
	}
}



