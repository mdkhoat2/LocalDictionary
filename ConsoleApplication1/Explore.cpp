#include "Explore.h"

Explore::Explore(sf::Font& font, sf::Font& font2, sf::Window& window) :
	displayBox({ 72, 250 }, { 850, 600 }, sf::Color::Transparent, sf::Color::Black),
	currentDataSet(0)
{
	initBackground(window);
	initFont();
	initDisplayBox();
}

void Explore::initBackground(sf::Window& window)
{
	if (!backgroundTex.loadFromFile("background/explore.jpg"))
		std::cout << "Loading screen not found!\n";
	backgroundTex.setSmooth(true);
	background.setTexture(backgroundTex);

	// Scale the background to fit window
	float scaleX = static_cast<float>(window.getSize().x) / backgroundTex.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / backgroundTex.getSize().y;
	background.setScale(scaleX, scaleY);
}

void Explore::initFont()
{
	font = font;
	font2 = font2;
}

void Explore::initDisplayBox() {
	
}


void Explore::searchInEngEngDict(std::string& inputWord, std::vector<WordDataEngVie>& engEngVector, EngTrieNode*& engEngRoot)
{
    int wordIndex = filterAndSearch(engEngRoot, inputWord, 0);
    if (wordIndex != -1)
    {
        // Console
        std::cout << wordIndex << std::endl;
        // UI
        displayBox.getWordDataEngEng(inputWord, wordIndex, engEngVector);
    }
    else
    {
        std::cout << "Cannot find the word" << "\n";
        displayBox.showNoEngEngDefinitions();
    }
}
