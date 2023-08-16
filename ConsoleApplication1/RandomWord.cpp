#include "RandomWord.h"

RandomWord::RandomWord(sf::Font& first, sf::Font& second, sf::RenderWindow& window):
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
	currentChoice(0)
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

void RandomWord::handleEvent(sf::Event& event, sf::RenderWindow& window, int& id, std::vector<WordDataEngVie>& engEngVector, std::vector<WordDataEngVie>& engVieVector, std::vector<WordDataEngVie>& vieEngVector)
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
				keyword = "this mode does not support emojis, please choose another mode";
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

void RandomWord::update(sf::RenderWindow& window)
{
	backButton.update(window);
	randomButton.update(window);
	button1.update(window);
	button2.update(window);
	button3.update(window);
	button4.update(window);
	submitButton.update(window);
}

void RandomWord::render(sf::RenderWindow& window)
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
		displayDefinition(window, word1);
	else if (currentChoice == 2)
		displayDefinition(window, word2);
	else if (currentChoice == 3)
		displayDefinition(window, word3);
	else if (currentChoice == 4)
		displayDefinition(window, word4);
	else
	{
		//std::cout << "1 " << keyword << std::endl << word1.def << std::endl << word2.def << std::endl;
	}
	displayKeyword(window);
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

void RandomWord::displayDefinition(sf::RenderWindow& window, word toDraw)
{
	sf::Text text;
	text.setFont(font);
	text.setString(toDraw.type);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Black);
	text.setPosition(100, 270);
	window.draw(text);
	//std::vector<std::string> line;
	//while (toDraw.def.size() > 0) {
	//	std::string temp = toDraw.def.substr(0, 63);
	//	toDraw.def.erase(0, 63);
	//	line.push_back(temp);
	//}
	//for (int i = 0; i < line.size(); i++) {
	//	sf::Text text;
	//	text.setFont(font);
	//	text.setString(line[i]);
	//	text.setCharacterSize(30);
	//	text.setFillColor(sf::Color::Black);
	//	text.setPosition(100, 320 + i * 40);
	//	window.draw(text);
	//}
	sf::Text text2;
	text2.setFont(font);
	text2.setString(toDraw.def);
	text2.setCharacterSize(30);
	text2.setFillColor(sf::Color::Black);
	text2.setPosition(100, 320);
	wrapText(text2);
	window.draw(text2);
}

void RandomWord::displayKeyword(sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(font2);
	text.setString(keyword);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setPosition(125, 180);
	window.draw(text);
}

void RandomWord::getRandom(std::vector<WordDataEngVie>& root)
{
	int n1 = ranNum(root.size() - 5752) + 5752;
	int n2 = ranNum(root.size() - 5752) + 5752;
	int n3 = ranNum(root.size() - 5752) + 5752;
	int n4 = ranNum(root.size() - 5752) + 5752;

	word1.def = root[n1].defList[0].defAndExample.first;
	word1.type = root[n1].defList[0].wordType;

	word2.def = root[n2].defList[0].defAndExample.first;
	word2.type = root[n2].defList[0].wordType;

	word3.def = root[n3].defList[0].defAndExample.first;
	word3.type = root[n3].defList[0].wordType;

	word4.def = root[n4].defList[0].defAndExample.first;
	word4.type = root[n4].defList[0].wordType;

	answer = ranNum(4);
	if (answer == 1)
		keyword = root[n1].word;
	else if (answer == 2)
		keyword = root[n2].word;
	else if (answer == 3)
		keyword = root[n3].word;
	else if (answer == 4)
		keyword = root[n4].word;
}

void RandomWord::wrapText(sf::Text& theText)
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

void RandomWord::initBackground(sf::RenderWindow& window)
{
	if (!backgroundTexture.loadFromFile("background/randomWord.jpg"))
		std::cout << "randomWord not found!\n";
	backgroundTexture.setSmooth(true);
	background.setTexture(backgroundTexture);
	float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
	background.setScale(scaleX, scaleY);
}

void RandomWord::initSprite()
{
	if (!rightTexture.loadFromFile("background/congratulation.png"))
		std::cout << "randomWord not found!\n";
	rightTexture.setSmooth(true);
	right.setTexture(rightTexture);
	right.setScale(0.3, 0.3);
	right.setPosition(300, 300);

	if (!wrongTexture.loadFromFile("background/oops.png"))
		std::cout << "randomWord not found!\n";
	wrongTexture.setSmooth(true);
	wrong.setTexture(wrongTexture);
	wrong.setScale(0.3, 0.3);
	wrong.setPosition(300, 300);
}

void RandomWord::initBackButton()
{
	backButton.setFont(font);
	backButton.setPosition({ 972, 163 });
	backButton.setOutlineThickness(2);
}

void RandomWord::initRandomButton()
{
	randomButton.setFont(font);
	randomButton.setPosition({ 882, 175 });
	randomButton.setOutlineThickness(2);
}

void RandomWord::initButton1()
{
	button1.setFont(font);
	button1.setPosition({ 972, 253 });
	button1.setOutlineThickness(2);
}

void RandomWord::initButton2()
{
	button2.setFont(font);
	button2.setPosition({ 972, 310 });
	button2.setOutlineThickness(2);
}

void RandomWord::initButton3()
{
	button3.setFont(font);
	button3.setPosition({ 972, 365 });
	button3.setOutlineThickness(2);
}

void RandomWord::initButton4()
{
	button4.setFont(font);
	button4.setPosition({ 972, 420 });
	button4.setOutlineThickness(2);
}

void RandomWord::initSubmitButton()
{
	submitButton.setFont(font);
	submitButton.setPosition({ 972, 531 });
	submitButton.setOutlineThickness(2);
}

void RandomWord::initWord()
{
	word1.def = "	";
	word1.type = "	";
	word2.def = "	";
	word2.type = "	";
	word3.def = "	";
	word3.type = "	";
	word4.def = "	";
	word4.type = "	";
	keyword = "please click the shuffle icon to start...";
}
