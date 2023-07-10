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

void Favourite(sf::RenderWindow &window)
{
    window.setKeyRepeatEnabled(false);

    sf::Font font;
    if (!font.loadFromFile("font/SF-Pro-Rounded-Regular.otf"))
    {
        std::cout << "Failed to load font!" << std::endl;
        return ;
    }

    std::vector<std::string> favoriteWords = loadWords();
    std::vector<WordItem> wordItems;

    sf::RectangleShape addButton(sf::Vector2f(60, 40));
    addButton.setFillColor(sf::Color(101, 199, 181));
    addButton.setPosition(90, 50);

    sf::Text addButtonText("ADD", font, 20);
    addButtonText.setFillColor(sf::Color::Black);
    addButtonText.setPosition(addButton.getPosition().x + 10, addButton.getPosition().y + 10);

    for (const std::string& word : favoriteWords) {
        WordItem wordItem;
        wordItem.word = word;
        wordItem.deleteButton.setSize(sf::Vector2f(40, 40));
        wordItem.deleteButton.setFillColor(sf::Color(28, 199, 54));
        wordItems.push_back(wordItem);
    }

    float posY = 100;
    for (WordItem& wordItem : wordItems) {
        wordItem.deleteButton.setPosition(window.getSize().x - wordItem.deleteButton.getSize().x - 50, posY);
        posY += 50;
    }

    sf::Texture backgroundTexture;
    sf::Sprite backgroundImage;
    if (!backgroundTexture.loadFromFile("background/Trang.jpg"))
    {
        std::cout << "Failed to load image!" << std::endl;
        return;
    }
    backgroundImage.setTexture(backgroundTexture);
    backgroundImage.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x, static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    bool isAddingWord = false;
    std::string newWord;
    bool isTyping = false;
    bool isHoveringButton = false;
    sf::RectangleShape hoverButton(sf::Vector2f(60, 40));
    hoverButton.setFillColor(sf::Color::Transparent);
    hoverButton.setOutlineThickness(2);
    hoverButton.setOutlineColor(sf::Color::Black);
    //
    bool isHoveringDeleteButton = false;
    sf::RectangleShape hoverdeleteButton(sf::Vector2f(40, 40));
    hoverdeleteButton.setFillColor(sf::Color::Transparent);
    hoverdeleteButton.setOutlineThickness(2);
    hoverdeleteButton.setOutlineColor(sf::Color::Black);


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
                        isAddingWord = true;
                        isTyping = true;
                    }
                    else {
                        for (auto it = wordItems.begin(); it != wordItems.end(); ++it) {
                            if (it->deleteButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                favoriteWords.erase(std::remove(favoriteWords.begin(), favoriteWords.end(), it->word), favoriteWords.end());
                                wordItems.erase(it);
                                saveWords(favoriteWords);
                                posY = 100;
                                for (WordItem& wordItem : wordItems) {
                                    wordItem.deleteButton.setPosition(window.getSize().x - wordItem.deleteButton.getSize().x - 50, posY);
                                    posY += 50;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            else if (event.type == sf::Event::TextEntered && isTyping)
            {
                if (event.text.unicode == 13)
                {
                    favoriteWords.push_back(newWord);
                    WordItem wordItem;
                    wordItem.word = newWord;
                    wordItem.deleteButton.setSize(sf::Vector2f(40, 40));
                    wordItem.deleteButton.setFillColor(sf::Color(28, 199, 54));
                    wordItem.deleteButton.setPosition(window.getSize().x - wordItem.deleteButton.getSize().x - 50, posY);
                    wordItems.push_back(wordItem);
                    posY += 50;
                    saveWords(favoriteWords);
                    isAddingWord = false;
                    newWord = "";
                    isTyping = false;
                }
                else if (event.text.unicode == 8)
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
        for (const WordItem& meo : wordItems)
        {
            if (meo.deleteButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
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
        window.clear();
        window.draw(backgroundImage);
        window.draw(addButton);
        window.draw(addButtonText);
        for (const WordItem& wordItem : wordItems) {
            window.draw(wordItem.deleteButton);
            sf::Text wordText(wordItem.word, font, 20);
            wordText.setFillColor(sf::Color::Black);
            wordText.setPosition(200, wordItem.deleteButton.getPosition().y + 10);
            window.draw(wordText);
        }
        //
        if (isHoveringDeleteButton)
        {
            for (const WordItem meo : wordItems)
            {
                if (meo.word == word1)
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
        if (isAddingWord) {
            sf::Text newText(newWord, font, 20);
            newText.setFillColor(sf::Color::Black);
            newText.setPosition(addButton.getPosition().x + addButton.getSize().x + 10, addButton.getPosition().y + 10);
            window.draw(newText);
        }

        if (isTyping) {
            sf::Text underlineText(newWord + "_", font, 20);
            underlineText.setFillColor(sf::Color::Black);
            underlineText.setPosition(addButton.getPosition().x + addButton.getSize().x + 10, addButton.getPosition().y + 10);
            window.draw(underlineText);
        }

        window.display();
    }

    return;
}

