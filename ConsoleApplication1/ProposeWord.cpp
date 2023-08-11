#include"ProposeWord.h"
char getCharFromIndex(int index);
void findWordsWithPrefix(EngTrieNode* prefixRoot, const std::string& prefix, std::vector<ProposeWords>& proposeWordList, int theID)
{
	if (!prefixRoot || proposeWordList.size() == 15)
	{
		return;
	}
	if (prefixRoot->flag)
	{
		if (theID == 0)
		{
			if (prefixRoot->engEngIndex != -1)
			{
				ProposeWords meo;
				meo.word = prefix;
				proposeWordList.push_back(meo);
			}
		}
		else if (theID == 1)
		{
			if (prefixRoot->engVieIndex != -1)
			{
				ProposeWords meo;
				meo.word = prefix;
				proposeWordList.push_back(meo);
			}
		}
		else if (theID == 2)
		{
			if (prefixRoot->vieEngIndex != -1)
			{
				ProposeWords meo;
				meo.word = prefix;
				proposeWordList.push_back(meo);
			}
		}
		else
		{
			if (prefixRoot->emojiIndex != -1)
			{
				ProposeWords meo;
				meo.word = prefix;
				proposeWordList.push_back(meo);
			}
		}
	}

	for (int i = 0; i < 72; ++i) {
		if (prefixRoot->links[i] != nullptr)
		{
			char ch = getCharFromIndex(i);
			findWordsWithPrefix(prefixRoot->links[i], prefix + ch, proposeWordList, theID);
		}
	}
}
char getCharFromIndex(int index) {
	if (index >= 0 && index <= 25) {
		return 'a' + index;
	}
	else if (index >= 26 && index <= 51) {
		return 'A' + (index - 26);
	}
	else if (index >= 52 && index <= 61) {
		return '0' + (index - 52);
	}
	else if (index == 62) {
		return '\'';
	}
	else if (index == 63) {
		return '.';
	}
	else if (index == 64) {
		return '-';
	}
	else if (index == 65) {
		return ' ';
	}
	else if (index == 66) {
		return '/';
	}
	else if (index == 67) {
		return ',';
	}
	else if (index == 68) {
		return '&';
	}
	else if (index == 69) {
		return '!';
	}
	else if (index == 70) {
		return ':';
	}
	else if (index == 71) {
		return '?';
	}
	else {
		return '\0';
	}
}
ProposeWord::ProposeWord() :
	datasetID(0),
	prefixRoot(nullptr),
	isTyping(true)
{
	font.loadFromFile("font/SF-Pro-Rounded-Regular.otf");
	initScrollBar();
	firstVisibleIndex = 0;
	viewableItems = 9;
	prevPrefix = "";
}
bool ProposeWord::setIsTyping()
{
	return isTyping;
}
void ProposeWord::LoadWordList()
{
	eraseWordList();
	findWordsWithPrefix(prefixRoot, prevPrefix, proposeWordList, datasetID);
}
EngTrieNode* ProposeWord::search(EngTrieNode* root, std::string word)
{
	if (word.empty())return nullptr;
	EngTrieNode* node = root;
	for (int i = 0; i < word.length(); ++i)
	{
		if (!node->containsKey(word[i]))
			return nullptr;
		node = node->get(word[i]);
	}
	return node;
}
void ProposeWord::eraseWordList()
{
	while (proposeWordList.size() != 0)
	{
		proposeWordList.pop_back();
	}
}
void ProposeWord::initScrollBar()
{
	if (!scrollbar1Texture.loadFromFile("background/Scroll-bar.png"))
	{
		std::cout << "Falied to load image ";
	}
	scrollbar1Texture.setSmooth(true);
	scrollbar1Image.setTexture(scrollbar1Texture);
	scrollbar1Image.setScale(sf::Vector2f(15.f / scrollbar1Texture.getSize().x, 607.f / scrollbar1Texture.getSize().y));
	scrollbar1Image.setPosition(926, 253);
	if (!scrollbar2Texture.loadFromFile("background/scroll-bar1.png"))
	{
		std::cout << "Falied to load image ";
	}
	scrollbar2Texture.setSmooth(true);
	scrollbar2Image.setTexture(scrollbar2Texture);
	scrollbar2Image.setScale(sf::Vector2f(15.f / scrollbar2Texture.getSize().x, 50.f / scrollbar2Texture.getSize().y));
}
void ProposeWord::setDataSetID(int theID)
{
	datasetID = theID;
	firstVisibleIndex = 0;
	eraseWordList();
	return;
}
bool ProposeWord::getMousePosition(sf::RenderWindow& window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f checkAreaPosition(71, 253);
	sf::Vector2f checkAreaSize(870, 607);
	if (mousePosition.x >= checkAreaPosition.x &&
		mousePosition.x <= checkAreaPosition.x + checkAreaSize.x &&
		mousePosition.y >= checkAreaPosition.y &&
		mousePosition.y <= checkAreaPosition.y + checkAreaSize.y)
	{
		return true;
	}
	else return false;
}
void ProposeWord::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
		{
			int delta = event.mouseWheelScroll.delta;
			if (delta > 0 && firstVisibleIndex > 0)
			{
				firstVisibleIndex--;
			}
			else if (delta < 0 && firstVisibleIndex < proposeWordList.size() - viewableItems)
			{
				firstVisibleIndex++;
			}
		}
	}
}
void ProposeWord::drawTo(sf::RenderWindow& window)
{
	int m = 0;
	int y = 300;
	for (ProposeWords& word : proposeWordList)
	{
		if (firstVisibleIndex <= m && m <= (firstVisibleIndex + 8))
		{
			sf::Text wordText(word.word, font, 20);
			wordText.setFillColor(sf::Color::Black);
			wordText.setPosition(140, y);
			word.grayButton.drawTo(window);
			word.grayButton.setPosition(71, y - 15);
			window.draw(wordText);
			y += 50;
		}
		m++;
	}
	if (proposeWordList.size() > 7)
	{
		float posY = 300 + firstVisibleIndex * (520 / (proposeWordList.size() - 7));
		scrollbar2Image.setPosition(926, posY);
		window.draw(scrollbar2Image);
	}
}
void ProposeWord::initWordList(std::string word, EngTrieNode* root)
{
	if (word == "")
	{
		prevPrefix = "";
	}
	if (checkPrefix(word, root))
	{
		LoadWordList();
	}
	if (prevPrefix.empty())
	{
		eraseWordList();
	}
}
bool ProposeWord::checkPrefix(std::string word, EngTrieNode* root)
{
	std::string word1 = word;
	if (word1 != prevPrefix)
	{
		prevPrefix = word1;
		prefixRoot = search(root, word1);
		if (prefixRoot != nullptr)
		{
			return true;
		}
	}
	for (int i = 0; i < word1.length(); ++i)
	{
		if (word1[i] >= 'a' && word1[i] <= 'z')
			word1[i] = toupper(word1[i]);
	}
	if (word1 != prevPrefix)
	{
		prevPrefix = word1;
		prefixRoot = search(root, word1);
		if (prefixRoot != nullptr)
		{
			return true;
		}
	}
	for (int i = 0; i < word1.length(); ++i)
	{
		word1[i] = tolower(word1[i]);
	}
	if (word1 != prevPrefix)
	{
		prevPrefix = word1;
		prefixRoot = search(root, word1);
		if (prefixRoot != nullptr)
		{
			return true;
		}
	}
	word1[0] = toupper(word1[0]);
	if (word1 != prevPrefix)
	{
		prevPrefix = word1;
		prefixRoot = search(root, word1);
		if (prefixRoot != nullptr)
		{
			return true;
		}
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
	if (word1 != prevPrefix)
	{
		prevPrefix = word1;
		prefixRoot = search(root, word1);
		if (prefixRoot != nullptr)
		{
			return true;
		}
	}
	for (int i = 0; i < word1.length(); ++i)
	{
		if (i == 0)
		{
			word1[0] = toupper(word1[0]);
		}
		else if (word[i - 1] == ' ' && i > 1)
		{
			word1[i] = toupper(word1[i]);
		}
	}
	if (word1 != prevPrefix)
	{
		prevPrefix = word1;
		prefixRoot = search(root, word1);
		if (prefixRoot != nullptr)
		{
			return true;
		}
	}
	return false;
}
void ProposeWord::update(sf::RenderWindow& window)
{
	int m = 0;
	for (ProposeWords& word : proposeWordList)
	{
		if (firstVisibleIndex <= m && m <= (firstVisibleIndex + 8))
		{
			if (word.grayButton.isMouseOver(window))
			{
				word.grayButton.setBackColor(sf::Color(201, 209, 202));
			}
			else
			{
				word.grayButton.setBackColor(sf::Color::Transparent);
			}
		}
		m++;
	}
}
void ProposeWord::handleEvent2(sf::Event& event, sf::RenderWindow& window, Textbox& searchBar)
{

	int m = 0;
	for (ProposeWords& word : proposeWordList)
	{
		if (firstVisibleIndex <= m && m <= (firstVisibleIndex + 8) && word.grayButton.isMouseOver(window))
		{
			searchBar.setText(word.word);
		}
		m++;
	}

}