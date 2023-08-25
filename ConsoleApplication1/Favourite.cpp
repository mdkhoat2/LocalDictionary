#include"Favourite.h"
#include<string>
void saveWords(const std::vector<WordItem>& words, std::string filePath) {
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
void removeStringFromFile(const std::string& filePath, const std::string& stringToRemove) {
	std::ifstream inputFile(filePath);
	if (!inputFile.is_open()) {
		return;
	}

	std::vector<std::string> lines;
	std::string line;

	while (std::getline(inputFile, line)) {
		if (line.find(stringToRemove) == std::string::npos) {
			lines.push_back(line);
		}
	}

	inputFile.close();

	std::ofstream outputFile(filePath);
	if (!outputFile.is_open()) {
		return;
	}

	for (const auto& line : lines) {
		outputFile << line << "\n";
	}

	outputFile.close();

}

Favourite::Favourite(sf::RenderWindow& window) :
	addBar(20, sf::Color::Black, sf::Color::Transparent, true),
	backButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	addButton("", { 35, 35 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	prevButton("", { 80, 80 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	nextButton("", { 80, 80 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	dataSetButton("      EN - EN", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Black),
	isEndScreen(false),
	isExist(false),
	notFound(false),
	currentDataSetID(0)
{
	font.loadFromFile("font/SF-Pro-Rounded-Regular.otf");
	initAddButton(font);
	initBackButton(font);
	initBackground(window);
	initnextButton(font);
	initprevButton(font);
	initAddBar(font);
	initDataSetButton(font);
	initExistedText();
	initNotFoundText();
	posY1 = 260;
	t1 = sf::seconds(1.5f);
	filePath = "data/favourite/favorite_words" + std::to_string(currentDataSetID) + ".txt";
}

void Favourite::initExistedText()
{
	existed.setFont(font);
	existed.setString("This word has been added before !");
	existed.setFillColor(sf::Color::Black);
	existed.setCharacterSize(33);
	existed.setPosition(270, 630);
}

void Favourite::initNotFoundText()
{
	notFoundText.setFont(font);
	notFoundText.setString("This word does not exist in the dictionary with this dataset.");
	notFoundText.setFillColor(sf::Color::Black);
	notFoundText.setCharacterSize(33);
	notFoundText.setPosition(110, 630);
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

void Favourite::initBackground(sf::RenderWindow& window)
{

	if (!deleteButtonTexture.loadFromFile("background/removeButton.png"))
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
		std::cout << "Meo" << std::endl;
		std::cout << filePath;
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

void Favourite::addWord(std::string inputword, EngTrieNode* root)
{
	if (inputword.empty() == true)return;
	if (!filterAndCheckinDictionary(root, inputword))
	{
		notFound = true;
	}
	else if (filterAndCheck(inputword))
	{
		isExist = true;
	}
	else
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
		saveWords(wordItems, filePath);
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
			saveWords(wordItems, filePath);
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
void Favourite::handleEvent(sf::Event& event, sf::RenderWindow& window, bool& endScreen, EngTrieNode* root)
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
			addWord(word, root);
		}
		else if (backButton.isMouseOver(window))
		{
			endScreen = true;
			isEndScreen = endScreen;
		}
		else if (nextButton.isMouseOver(window) && currentPage < numberPage)
		{
			currentPage += 1;
		}
		else if (prevButton.isMouseOver(window) && currentPage != 1)
		{
			currentPage -= 1;
		}
		else if (dataSetButton.isMouseOver(window))
		{
			changeDataSet();
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
		dataSetButton.update(window);
		int m = 0;
		for (WordItem& wordItem : wordItems)
		{
			m++;
			if (((currentPage - 1) * 7) < m && m <= (currentPage * 7) && m <= wordItems.size())
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
		dataSetButton.drawTo(window);
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
				wordText.setPosition(125, y + 10);
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
		if (notFound == true)
		{
			if (clock.getElapsedTime() >= t1 && notFound)
			{
				notFound = false;
			}
			window.draw(notFoundText);
		}
	}
}
void Favourite::setEndScreen(bool value) {
	isEndScreen = value;
}

void Favourite::setCurrentDataSet()
{
	posY1 = 260;
	filePath = "data/favourite/favorite_words" + std::to_string(currentDataSetID) + ".txt";
}
void Favourite::setDataSet(int theID)
{
	currentDataSetID = theID;
	posY1 = 260;
	filePath = "data/favourite/favorite_words" + std::to_string(currentDataSetID) + ".txt";
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
		{
			word[0] = toupper(word[0]);
		}
		else if (word[i - 1] == ' ' && i > 1)
		{
			word[i] = toupper(word[i]);
		}
	}
	if (checkStringInFile(filePath, word) == true)
	{
		return true;
	}
	return false;
}

void Favourite::eraseWordList()
{
	while (wordItems.size() != 0)
	{
		wordItems.pop_back();
	}
}

void Favourite::initDataSetButton(sf::Font& font)
{
	dataSetButton.setFont(font);
	dataSetButton.setPosition({ 972, 72 });
	dataSetButton.setOutlineThickness(2);
	dataSetButton.setStyle(sf::Text::Style::Bold);
}
void Favourite::changeDataSet()
{
	if (currentDataSetID != 3)
		currentDataSetID += 1;
	else
		currentDataSetID = 0;
	if (currentDataSetID == 0)
		dataSetButton.setString("      EN - EN");
	else if (currentDataSetID == 1)
		dataSetButton.setString("      EN - VI");
	else if (currentDataSetID == 2)
		dataSetButton.setString("      VI - EN");
	else
		dataSetButton.setString("      Emoji");
	eraseWordList();
	setCurrentDataSet();
	loadWordsList();
}
bool Favourite::filterAndCheckinDictionary(EngTrieNode* root, std::string word)
{
	int result = trieSearch(root, word, currentDataSetID);
	if (result !=-1)
		return true;
	for (int i = 0; i < word.length(); ++i)
	{
		if (word[i] >= 'a' && word[i] <= 'z')
			word[i] = toupper(word[i]);
	}
	result = trieSearch(root, word, currentDataSetID);
	if (result != -1)
		return true;
	for (int i = 0; i < word.length(); ++i)
	{
		word[i] = tolower(word[i]);
	}
	result = trieSearch(root, word, currentDataSetID);
	if (result != -1)
		return true;
	word[0] = toupper(word[0]);
	result = trieSearch(root, word, currentDataSetID);
	if (result != -1)
		return true;
	word[0] = tolower(word[0]);
	int i = 0;
	while (word[i] != ' ' && i < word.length())
		++i;
	if (i < word.length() && word[i] == ' ')
	{
		if (word[i + 1] >= 'a' && word[i + 1] <= 'z')
			word[i + 1] = toupper(word[i + 1]);
	}
	result = trieSearch(root, word, currentDataSetID);
	if (result != -1)return true;
	return false;
}

//=======================================================================================

FavouriteOnMainAndOptionScreen::FavouriteOnMainAndOptionScreen()
{
	font.loadFromFile("font/SF-Pro-Rounded-Regular.otf");
	t1 = sf::seconds(1.5f);
	initFavouriteFlagImage();
	initAddedText();
	initRemovedText();
	CoutText = false;
	showFlag = true;
}


void FavouriteOnMainAndOptionScreen::initFavouriteFlagImage()
{
	if (!favouriteFlag1Texture.loadFromFile("background/flag1.png"))
	{
		std::cout << "Falied to load image ";
	}
	favouriteFlag1Texture.setSmooth(true);
	favouriteFlag1Image.setTexture(favouriteFlag1Texture);
	favouriteFlag1Image.setScale(sf::Vector2f(60.f / favouriteFlag1Texture.getSize().x, 60.f / favouriteFlag1Texture.getSize().y));
	favouriteFlag1Image.setPosition(9, 162);
	if (!favouriteFlag2Texture.loadFromFile("background/flag2.png"))
	{
		std::cout << "Falied to load image ";
	}
	favouriteFlag2Texture.setSmooth(true);
	favouriteFlag2Image.setTexture(favouriteFlag2Texture);
	favouriteFlag2Image.setScale(sf::Vector2f(60.f / favouriteFlag2Texture.getSize().x, 60.f / favouriteFlag2Texture.getSize().y));
	favouriteFlag2Image.setPosition(9, 162);
}

void FavouriteOnMainAndOptionScreen::initAddedText()
{
	Added.setFont(font);
	Added.setString("You have added this word to favorites");
	Added.setFillColor(sf::Color::Black);
	Added.setCharacterSize(33);
	Added.setPosition(150, 700);
}
void FavouriteOnMainAndOptionScreen::initRemovedText()
{
	Removed.setFont(font);
	Removed.setString("You have removed this word from favorites");
	Removed.setFillColor(sf::Color::Black);
	Removed.setCharacterSize(33);
	Removed.setPosition(150, 700);
}
void FavouriteOnMainAndOptionScreen::checkWordAddedOrNot(std::string word, int currentDataSetID)
{
	std::string filePath = "data/favourite/favorite_words" + std::to_string(currentDataSetID) + ".txt";
	if (filterAndCheck(word, filePath))
	{
		isAdded = true;
	}
	else
	{
		isAdded = false;
	}

}
void FavouriteOnMainAndOptionScreen::eraseOrAdd(Textbox& searchBar, int currentDataSetID)
{
	std::string filePath = "data/favourite/favorite_words" + std::to_string(currentDataSetID) + ".txt";
	std::string word = searchBar.getText();
	CoutText = true;
	if (isAdded == true)
	{
		isAdded = false;
		filterAndCheck(word, filePath);
		removeStringFromFile(filePath, word);
	}
	else
	{
		isAdded = true;
		appendStringToFile(filePath, word);
	}
	clock.restart();
}

void FavouriteOnMainAndOptionScreen::drawTo(sf::RenderWindow& window, Textbox& searchBar)
{
	std::string word = searchBar.getText();
	if (!word.empty())
	{
		if (isAdded == true)
		{
			window.draw(favouriteFlag2Image);
		}
		else
		{
			window.draw(favouriteFlag1Image);
		}
		if (CoutText == true)
		{
			if (clock.getElapsedTime() >= t1 && CoutText)
			{
				CoutText = false;
			}
			if (isAdded == true)
			{
				window.draw(Added);
			}
			else
			{
				window.draw(Removed);
			}
		}
	}
}
bool FavouriteOnMainAndOptionScreen::filterAndCheck(std::string& word, std::string filePath)
{
	std::string wordCheck = word;
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
		{
			word[0] = toupper(word[0]);
		}
		else if (word[i - 1] == ' ' && i > 1)
		{
			word[i] = toupper(word[i]);
		}
	}
	if (checkStringInFile(filePath, word) == true)
	{
		return true;
	}
	word = wordCheck;
	return false;

}
