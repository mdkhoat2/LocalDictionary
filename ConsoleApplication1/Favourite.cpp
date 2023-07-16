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

    sf::RectangleShape addButton(sf::Vector2f(116, 52));
    addButton.setFillColor(sf::Color::Transparent);
    addButton.setPosition(112, 146);

    sf::RectangleShape backButton(sf::Vector2f(141, 53));
    backButton.setFillColor(sf::Color::Transparent);
    backButton.setPosition(55, 32);

    sf::RectangleShape addButtonfake(sf::Vector2f(40, 40));
    sf::Texture deletebuttonTexture;
    sf::Sprite deleteButtonImage;
    if (!deletebuttonTexture.loadFromFile("background/buttondelete.jpg"))
    {
        std::cout << "Falied to load image";
        return ;
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

    float posY = 220;
    for (WordItem& wordItem : wordItems) {
        wordItem.deleteButton.setPosition(window.getSize().x - wordItem.deleteButton.getSize().x - 150, posY);
        posY += 50;
    }

    sf::Texture backgroundTexture;
    sf::Sprite backgroundImage;
    if (!backgroundTexture.loadFromFile("background/backgroundfavourite.jpg"))
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
    sf::RectangleShape hoverButton(sf::Vector2f(116, 52));
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
    bool isHoveringBackButton = false;
    sf::RectangleShape hoverBackButton(sf::Vector2f(141, 53));
    hoverBackButton.setFillColor(sf::Color::Transparent);
    hoverBackButton.setOutlineThickness(2);
    hoverBackButton.setOutlineColor(sf::Color::Black);

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
                    else if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        return;
                    }
                    else {
                        for (auto it = wordItems.begin(); it != wordItems.end(); ++it) {
                            if (it->deleteButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                favoriteWords.erase(std::remove(favoriteWords.begin(), favoriteWords.end(), it->word), favoriteWords.end());
                                wordItems.erase(it);
                                saveWords(favoriteWords);
                                posY = 220;
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
                    wordItem.deleteButton.setPosition(window.getSize().x - wordItem.deleteButton.getSize().x - 150, posY);
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

        if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            isHoveringBackButton = true;
        }
        else
        {
            isHoveringBackButton = false;
        }
        window.clear();
        window.draw(backgroundImage);
        window.draw(addButton);
        window.draw(backButton);
        for (const WordItem& wordItem : wordItems) {
            window.draw(wordItem.deleteButton);
            deleteButtonImage.setPosition(wordItem.deleteButton.getPosition().x, wordItem.deleteButton.getPosition().y);
            window.draw(deleteButtonImage);
            sf::Text wordText(wordItem.word, font, 20);
            wordText.setFillColor(sf::Color::Black);
            wordText.setPosition(150, wordItem.deleteButton.getPosition().y + 10);
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
        if (isHoveringBackButton)
        {
            hoverBackButton.setPosition(backButton.getPosition());
            window.draw(hoverBackButton);
        }
        if (isAddingWord) {
            sf::Text newText(newWord, font, 20);
            newText.setFillColor(sf::Color::Black);
            newText.setPosition(addButton.getPosition().x + addButton.getSize().x + 40, addButton.getPosition().y + 20);
            window.draw(newText);
        }

        if (isTyping) {
            sf::Text underlineText(newWord + "_", font, 20);
            underlineText.setFillColor(sf::Color::Black);
            underlineText.setPosition(addButton.getPosition().x + addButton.getSize().x + 40, addButton.getPosition().y + 20);
            window.draw(underlineText);
        }

        window.display();
    }

    return;
}

