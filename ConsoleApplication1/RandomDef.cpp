#include "RandomDef.h"

RandomDef::RandomDef(sf::Font& first, sf::Font& second, sf::RenderWindow& window) :
	backButton("", { 153, 60 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	randomButton("", { 35, 35 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	button1("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	button2("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	button3("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	button4("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	submitButton("", { 153, 42 }, 20, sf::Color::Transparent, sf::Color::Transparent),
	isBackButtonPressed(false),
	isSubmitted(false),
	isCorrect(false),
	currentChoice(1)
{
	font = first;
	font2 = second;
	theBox.setPosition(72, 250);
	theBox.setSize({ 850, 600 });
	initBackground(window);
	initSprite();
	initBackButton();
	initRandomButton();
	initButton1();
	initButton2();
	initButton3();
	initButton4();
	initSubmitButton();
	initWord();
}

void RandomDef::handleEvent(sf::Event& event, sf::RenderWindow& window, int& id, std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector, std::vector<WordDataEngVie>& vieEngVector)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		isSubmitted = false;
		if (backButton.isMouseOver(window))
			isBackButtonPressed = true;
		else if (randomButton.isMouseOver(window)) {
			if (id == 0) {
				getRandom(engEngVector);
				isSubmitted = false;
			}
			else if (id == 1) {
				getRandom(engVieVector);
				isSubmitted = false;
			}
			else if (id == 2) {
				getRandom(vieEngVector);
				isSubmitted = false;
			}
			else {
				definition = "this mode does not support emojis, please choose en or vi";
			}
		}
		else if (button1.isMouseOver(window)) {
			currentChoice = 1;
		}
		else if (button2.isMouseOver(window)) {
			currentChoice = 2;
		}
		else if (button3.isMouseOver(window)) {
			currentChoice = 3;
		}
		else if (button4.isMouseOver(window)) {
			currentChoice = 4;
		}
		else if (submitButton.isMouseOver(window)) {
			if (currentChoice == answer) {
				isSubmitted = true;
				isCorrect = true;
				std::cout << "Correct\n";
			}
			else {
				isSubmitted = true;
				isCorrect = false;
				std::cout << "Incorrect\n";
			}
		}
	}
}

void RandomDef::update(sf::RenderWindow& window)
{
	backButton.update(window);
	randomButton.update(window);
	button1.update(window);
	button2.update(window);
	button3.update(window);
	button4.update(window);
	submitButton.update(window);
}

void RandomDef::render(sf::RenderWindow& window)
{
	window.draw(background);
	backButton.drawTo(window);
	randomButton.drawTo(window);
	button1.drawTo(window);
	button2.drawTo(window);
	button3.drawTo(window);
	button4.drawTo(window);
	submitButton.drawTo(window);
	if (currentChoice == 1)
		displayKeyword(window, word1);
	else if (currentChoice == 2)
		displayKeyword(window, word2);
	else if (currentChoice == 3)
		displayKeyword(window, word3);
	else if (currentChoice == 4)
		displayKeyword(window, word4);

	displayDefinition(window);
	//window.draw(right);
	//window.draw(wrong);
	if (isSubmitted)
		if (isCorrect) {
			//for (int i = 0; i < 5000; i++)
			window.draw(right);
			//isSubmitted = false;
		}
		else {
			//for (int i = 0; i < 5000; i++)
			window.draw(wrong);
			//isSubmitted = false;
		}
}

void RandomDef::displayDefinition(sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(font);
	text.setString(type);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Black);
	text.setPosition(100, 270);
	window.draw(text);

	sf::Text text2;
	text2.setFont(font);
	text2.setString(definition);
	text2.setCharacterSize(30);
	text2.setFillColor(sf::Color::Black);
	text2.setPosition(100, 320);
	wrapText(text2);
	window.draw(text2);
}

void RandomDef::displayKeyword(sf::RenderWindow& window, std::string& keyword)
{
	sf::Text text;
	text.setFont(font2);
	text.setString(keyword);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setPosition(125, 180);
	window.draw(text);
}

void RandomDef::getRandom(std::vector<WordDataEngVie>& root)
{
	int n1 = ranNum(root.size() - 5752) + 5752;
	int n2 = ranNum(root.size() - 5752) + 5752;
	int n3 = ranNum(root.size() - 5752) + 5752;
	int n4 = ranNum(root.size() - 5752) + 5752;

	word1 = root[n1].word;
	word2 = root[n2].word;
	word3 = root[n3].word;
	word4 = root[n4].word;

	answer = ranNum(4);
	if (answer == 1)
	{
		definition = root[n1].defList[0].defAndExample.first;
		type = root[n1].defList[0].wordType;
	}
	else if (answer == 2) {
		definition = root[n2].defList[0].defAndExample.first;
		type = root[n2].defList[0].wordType;
	}
	else if (answer == 3) {
		definition = root[n3].defList[0].defAndExample.first;
		type = root[n3].defList[0].wordType;
	}
	else if (answer == 4) {
		definition = root[n4].defList[0].defAndExample.first;
		type = root[n4].defList[0].wordType;
	}
}

void RandomDef::wrapText(sf::Text& theText)
{
	std::string str = theText.getString();
	std::string wrappedStr;

	std::istringstream iss(str);
	std::string word;
	std::string line;

	// Clear theText before wrapping
	theText.setString("");

	while (std::getline(iss, word, '\n')) {
		// Process each line separately
		if (!line.empty()) {
			// Add the previous line to the wrapped text and start a new line
			wrappedStr += line + '\n';
			line.clear();
		}
		std::istringstream lineIss(word);
		while (lineIss >> word) {
			// Set theText with the current line + the next word
			theText.setString(line + (line.empty() ? "" : " ") + word);
			if (theText.getLocalBounds().width > theBox.getLocalBounds().width - 30.f) {
				// Add the current line to the wrapped text and start a new line
				wrappedStr += line + '\n';
				line = word;
			}
			else {
				// Continue adding words to the current line
				line += (line.empty() ? "" : " ") + word;
			}
		}
	}

	// Add the last line to the wrapped text
	wrappedStr += line;

	// Set theText with the wrapped text
	theText.setString(wrappedStr);
}

void RandomDef::initBackground(sf::RenderWindow& window)
{
	if (!backgroundTexture.loadFromFile("background/randomDef.jpg"))
		std::cout << "randomDef not found!\n";
	backgroundTexture.setSmooth(true);
	background.setTexture(backgroundTexture);
	float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
	background.setScale(scaleX, scaleY);
}

void RandomDef::initSprite()
{
	if (!rightTexture.loadFromFile("background/congratulation.png"))
		std::cout << "randomDef not found!\n";
	rightTexture.setSmooth(true);
	right.setTexture(rightTexture);
	right.setScale(0.3, 0.3);
	right.setPosition(300, 300);

	if (!wrongTexture.loadFromFile("background/oops.png"))
		std::cout << "randomDef not found!\n";
	wrongTexture.setSmooth(true);
	wrong.setTexture(wrongTexture);
	wrong.setScale(0.3, 0.3);
	wrong.setPosition(300, 300);
}

void RandomDef::initBackButton()
{
	backButton.setFont(font);
	backButton.setPosition({ 972, 163 });
	backButton.setOutlineThickness(2);
}

void RandomDef::initRandomButton()
{
	randomButton.setFont(font);
	randomButton.setPosition({ 882, 175 });
	randomButton.setOutlineThickness(2);
}

void RandomDef::initButton1()
{
	button1.setFont(font);
	button1.setPosition({ 972, 253 });
	button1.setOutlineThickness(2);
}

void RandomDef::initButton2()
{
	button2.setFont(font);
	button2.setPosition({ 972, 310 });
	button2.setOutlineThickness(2);
}

void RandomDef::initButton3()
{
	button3.setFont(font);
	button3.setPosition({ 972, 365 });
	button3.setOutlineThickness(2);
}

void RandomDef::initButton4()
{
	button4.setFont(font);
	button4.setPosition({ 972, 420 });
	button4.setOutlineThickness(2);
}

void RandomDef::initSubmitButton()
{
	submitButton.setFont(font);
	submitButton.setPosition({ 972, 531 });
	submitButton.setOutlineThickness(2);
}

void RandomDef::initWord()
{
	word1 = "please click the shuffle icon to start...";
	word2 = "please click the shuffle icon to start...";
	word3 = "please click the shuffle icon to start...";
	word4 = "please click the shuffle icon to start...";
}
