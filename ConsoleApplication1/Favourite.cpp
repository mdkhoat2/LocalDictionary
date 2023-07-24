#include"Favourite.h"
#include<string>
void saveWords(const std::vector<WordItem>& words,std::string filePath) {
	std::ofstream file(filePath);
	if (file.is_open()) {
		for (const WordItem& word : words) {
			file << word.word << std::endl;
		}
		file.close();
	}
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


Favourite::Favourite(sf::RenderWindow&window):
	addBar(20, sf::Color::Black, sf::Color::Transparent, true),
	backButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	addButton("", { 35, 35 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	prevButton("", { 80, 80 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	nextButton("", { 80, 80 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	isEndScreen(false),
	isExist(false),
	currentDataSetID(0)
{
	font.loadFromFile("font/SF-Pro-Rounded-Regular.otf");
	initAddButton(font);
	initBackButton(font);
	initBackground(window);
	initnextButton(font);
	initprevButton(font);
	initAddBar(font);
	initExistedText();
	posY = 320;
	posY1 = 260;
	t1 = sf::seconds(1.5f);
	filePath = "favorite_words" + std::to_string(currentDataSetID) + ".txt";
}

void Favourite::initExistedText()
{
	existed.setFont(font);
	existed.setString("This word has been added before !");
	existed.setFillColor(sf::Color::Black);
	existed.setCharacterSize(33);
	existed.setPosition(270, 630);
}

void Favourite::initAddBar(sf::Font& font)
{
	addBar.setPosition({ 125, 180 });
	addBar.setBoxPosition({ 74, 158 });
	addBar.setBoxSize({ 800, 68 });
	addBar.setLimit(true, 65); //set limit to 65 characters
	addBar.setFont(font);

}

void Favourite::initAddButton(sf::Font& font)
{
	addButton.setFont(font);
	addButton.setPosition({ 882, 175 });
	addButton.setOutlineThickness(2);
}

void Favourite::initBackButton(sf::Font& font)
{
	backButton.setFont(font);
	backButton.setPosition({ 972, 163 });
	backButton.setOutlineThickness(2);
}

void Favourite::initprevButton(sf::Font& font)
{
	prevButton.setFont(font);
	prevButton.setPosition(150, 700);
	prevButton.setOutlineThickness(2);
}

void Favourite::initnextButton(sf::Font& font)
{
	nextButton.setFont(font);
	nextButton.setPosition(800, 700);
	nextButton.setOutlineThickness(2);
}

void Favourite::initBackground(sf::RenderWindow&window)
{
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

	if (!deleteButtonTexture.loadFromFile("background/buttondelete.jpg"))
	{
		std::cout << "Falied to load image";
		return;
	}
	deleteButtonTexture.setSmooth(true);
	deleteButtonImage.setTexture(deleteButtonTexture);
	deleteButtonImage.setScale(sf::Vector2f(40.f / deleteButtonTexture.getSize().x, 40.f / deleteButtonTexture.getSize().y));

	if (!backgroundTexture.loadFromFile("background/favourite.jpg"))
	{
		std::cout << "Failed to load image!" << std::endl;
		return;
	}
	backgroundTexture.setSmooth(true);
	backgroundImage.setTexture(backgroundTexture);
	backgroundImage.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x, static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

	if (!prevButtonTexture.loadFromFile("background/prev-button.png"))
	{
		std::cout << "Falied to load from file" << std::endl;
	}
	prevButtonTexture.setSmooth(true);
	prevButtonImage.setTexture(prevButtonTexture);
	prevButtonImage.setScale(sf::Vector2f(80.f / prevButtonTexture.getSize().x, 80.f / prevButtonTexture.getSize().y));
	prevButtonImage.setPosition(150, 700);
	if (!nextButtonTexture.loadFromFile("background/next-button.png"))
	{
		std::cout << "Falied to load from file" << std::endl;
	}
	nextButtonTexture.setSmooth(true);
	nextButtonImage.setTexture(nextButtonTexture);
	nextButtonImage.setScale(sf::Vector2f(80.f / nextButtonTexture.getSize().x, 80.f / nextButtonTexture.getSize().y));
	nextButtonImage.setPosition(800, 700);
}
void Favourite::add(std::string word)
{
	WordFavouriteButton newWord;
	newWord.word = word;
	newWord.favouriteButton.setSize(sf::Vector2f(30, 30));
	newWord.favouriteButton.setFillColor(sf::Color::Red);
	newWord.favouriteButton.setPosition(1052, posY);
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
	for (auto it = favourite.begin(); it != favourite.end(); it++)
	{
		if (!filterAndCheck(it->word) && it->liked == true)
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

void Favourite::loadWordsList()
{
	std::ifstream fi;
	fi.open(filePath);
	currentPage = 1;
	if (fi.is_open())
	{
		std::string word;
		while (std::getline(fi, word))
		{
			if (posY1 == 610)
			{
				posY1 = 260;
			}
			WordItem newItem;
			newItem.word = word;
			newItem.deleteButton.setPosition(880, posY1);
			newItem.deleteButton.setOutlineThickness(2);
			wordItems.push_back(newItem);
			posY1 += 50;
		}
	}
	else
	{
		std::cout << "Meo";
	}
	if (wordItems.size() % 7 == 0)
	{
		numberPage = wordItems.size() / 7;
	}
	else
	{
		numberPage = (wordItems.size() / 7) + 1;
	}
	fi.close();
	//std::cout << wordItems.size();
	//std::cout << numberPage;
}
void Favourite::resavePositionDeleteButton()
{
	posY1 = 260;
	for (WordItem& wordItem : wordItems)
	{
		if (posY1 == 610)
		{
			posY1 = 260;
		}
		wordItem.deleteButton.setPosition(880, posY1);
		posY1 += 50;
	}
}

void Favourite::addWord(std::string inputword)
{
	if (filterAndCheck(inputword) && inputword != "")
	{
		isExist = true;
	}
	if (inputword != "" && !filterAndCheck(inputword))
	{
		if (posY1 == 610)
		{
			posY1 = 260;
		}
		WordItem wordItem;
		wordItem.word = inputword;
		wordItem.deleteButton.setPosition(880, posY1);
		wordItem.deleteButton.setOutlineThickness(2);
		wordItems.push_back(wordItem);
		posY1 += 50;
		saveWords(wordItems,filePath);
		if (wordItems.size() % 7 == 1)
		{
			numberPage += 1;
		}

	}
	clock.restart();
}

void Favourite::removeWord(sf::RenderWindow& window)
{
	int p = 0;
	int first3 = (currentPage - 1) * 7;
	int last3 = currentPage * 7;
	for (auto it = wordItems.begin(); it != wordItems.end(); ++it) {
		p++;
		if (it->deleteButton.isMouseOver(window) && first3 < p && p <= last3) {
			wordItems.erase(it);
			saveWords(wordItems,filePath);
			resavePositionDeleteButton();
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

////////////////////
void Favourite::handleEvent(sf::Event& event, sf::RenderWindow& window,bool &endScreen)
{
	if (event.type == sf::Event::TextEntered) {
		addBar.typedOn(event);
	}
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (addBar.isMouseOver(window))
		{
			addBar.setSelected(true);
		}
		else
		{
			addBar.setSelected(false);
		}
		if (addButton.isMouseOver(window))
		{
			std::string word = addBar.getText();
			addWord(word);
		}
		else if (backButton.isMouseOver(window))
		{
			endScreen = true;
			isEndScreen = endScreen;
		}
		else if (nextButton.isMouseOver(window)&& currentPage < numberPage)
		{
			currentPage += 1;
		}
		else if (prevButton.isMouseOver(window) && currentPage != 1)
		{
			currentPage -= 1;
		}
		else
		{
			removeWord(window);
		}
	}
}
void Favourite::update(sf::RenderWindow& window)
{
	if (!isEndScreen)
	{
		addButton.update(window);
		backButton.update(window);
		int m = 0;
		for (WordItem& wordItem : wordItems)
		{
			m++;
			if (((currentPage-1)*7) < m && m <= (currentPage*7) && m <= wordItems.size())
			{
				wordItem.deleteButton.update(window);
			}
		}
	}
}

void Favourite::render(sf::RenderWindow& window)
{
	if (!isEndScreen)
	{
		window.clear(sf::Color::White);
		window.draw(backgroundImage);
		addButton.drawTo(window);
		backButton.drawTo(window);
		addBar.drawTo(window);
		if (currentPage == 1 && numberPage > 1)
		{
			nextButton.drawTo(window);
			window.draw(nextButtonImage);
		}
		if (currentPage > 1 && currentPage < numberPage)
		{
			nextButton.drawTo(window);
			window.draw(nextButtonImage);
			prevButton.drawTo(window);
			window.draw(prevButtonImage);
		}
		if (currentPage == numberPage && currentPage != 1)
		{
			prevButton.drawTo(window);
			window.draw(prevButtonImage);
		}
		int m = 0;
		int y = 260;
		for (WordItem& wordItem : wordItems)
		{
			m++;
			if (((currentPage - 1) * 7) < m && m <= (currentPage * 7) && m <= wordItems.size())
			{
				wordItem.deleteButton.drawTo(window);
				deleteButtonImage.setPosition(880, y);
				window.draw(deleteButtonImage);
				sf::Text wordText(wordItem.word, font, 20);
				wordText.setFillColor(sf::Color::Black);
				wordText.setPosition(140, y + 10);
				window.draw(wordText);
				y += 50;
			}
		}
		if (isExist == true)
		{
			if (clock.getElapsedTime() >= t1 && isExist)
			{
				isExist = false;
			}
			window.draw(existed);
		}
	}
}
void Favourite::setEndScreen(bool value) {
	isEndScreen = value;
}

void Favourite::setCurrentDataSet(int theID)
{
	currentDataSetID = theID;
	filePath = "favorite_words" + std::to_string(currentDataSetID) + ".txt";
}

bool Favourite::filterAndCheck(std::string wordCheck)
{
	std::string word = wordCheck;
	if (checkStringInFile(filePath, word) == true)
	{
		return true;
	}
	for (int i = 0; i < word.length(); ++i)
	{
		if (word[i] >= 'a' && word[i] <= 'z')
			word[i] = toupper(word[i]);
	}
	if (checkStringInFile(filePath, word) == true)
	{
		return true;
	}
	for (int i = 0; i < word.length(); ++i)
	{
		word[i] = tolower(word[i]);
	}
	if (checkStringInFile(filePath, word) == true)
	{
		return true;
	}
	word[0] = toupper(word[0]);
	if (checkStringInFile(filePath, word) == true)
	{
		return true;
	}
	word[0] = tolower(word[0]);
	int i = 0;
	while (word[i] != ' ' && i < word.length())
		++i;
	if (i < word.length() && word[i] == ' ')
	{
		if (word[i + 1] >= 'a' && word[i + 1] <= 'z')
			word[i + 1] = toupper(word[i + 1]);
	}
	if (checkStringInFile(filePath, word) == true)
	{
		return true;
	}
	for (int i = 0; i < word.length(); ++i)
	{
		if (i == 0)
			word[0] = toupper(word[0]);
		if (word[i - 1] == ' ')
			word[i] = toupper(word[i]);
	}
	if (checkStringInFile(filePath, word) == true)
	{
		return true;
	}
	return false;
}

void Favourite::eraseWordList()
{
	while(wordItems.size()!=0)
	{
		wordItems.pop_back();
	}
}
