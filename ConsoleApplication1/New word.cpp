#include "New word.h"

void NewWord::addNewWord(TrieNode*& root, std::string word, std::string wordInfo, std::queue<WordData> addedWord) {
	trieInsert(root, word, wordInfo);
	WordData tmp;
	extractWordData(tmp, word, wordInfo);
	addedWord.push(tmp);
}

void NewWord::saveAddedWord(std::queue<WordData> addedWord) {
	if (addedWord.empty()) return;

	std::ofstream fout("data/Added Words.txt");
	if (!fout.is_open()) {
		fout.close();
		return;
	}

	while (!addedWord.empty()) {
		WordData tmp = addedWord.front();
		fout << tmp.word << std::endl;
		for (int i = 0; i < 4; ++i) {
			if (tmp.defListHead[i]) {
				fout << "     ";
				switch (i) {
				case 0:
					fout << "n ";
					break;
				case 1:
					fout << "v ";
					break;
				case 2:
					fout << "adj ";
					break;
				case 3:
					fout << "adv ";
					break;
				}
				if (tmp.defListHead[i]->next) {
					WordDefNode* cur = tmp.defListHead[i];
					int count = 1;
					while (cur) {
						fout << count << ": " << cur->wordDef << std::endl; 
						++count;
						cur = cur->next;
					}
				}
				else fout << " : " << tmp.defListHead[i]->wordDef << std::endl;
			}
		}
		addedWord.pop();
	}

	fout.close();
}

void NewWord::loadAddedWord(TrieNode*& root) {
    std::ifstream fin("data/Added Words.txt");
    
    std::string line, word, wordInfo;
    bool moreThan1Def = false;
    int count = 0;

    while (std::getline(fin, line))
    {
        if (line[0] != ' ') // this is a word
        {
            if (count == 0) // Read first word
            {
                ++count;
                word = line;
            }
            else
            {
                // insert the previous word with its definition
                trieInsert(root, word, wordInfo);
                word = line;
                wordInfo.clear();
                moreThan1Def = false;
            }
        }
        else
        {
            // Skip leading spaces
            int i = 0;
            while (line[i] == ' ')
                ++i;
            // Read the word's information
            // The first line will definitely contain the word type
            if (wordInfo.empty())
            {
                std::string wordType;
                while (line[i] != ' ')
                    wordType += line[i++];
                if (isdigit(line[i + 1]))
                    moreThan1Def = true;
                wordInfo += wordType + "\n" + line.substr(i + 1);
            }
            else
            {
                // Check for "X:" which indicates another meaning of the same word type
                int j = i;
                std::string numStr;
                while (line[j] != ':' && j < line.length())
                    numStr += line[j++];
                if (isNumber(numStr) && moreThan1Def)
                    wordInfo += "\n" + line.substr(i);
                else
                {
                    // Check for any other word type
                    std::string wordType;
                    while (line[i] != ' ' && i < line.length())
                        wordType += line[i++];
                    // If the word has another word type
                    if (isValidWordType(wordType))
                    {
                        wordInfo += "\n" + wordType + "\n" + line.substr(i + 1);
                    }
                    // If it is a normal line
                    else if (line[i] == ' ')
                    {
                        wordInfo += " " + wordType + line.substr(i);
                    }
                    // If the line contains only 1 word that is not a word type
                    else
                    {
                        wordInfo += " " + wordType;
                    }
                }
            }
        }
    }
    trieInsert(root, word, wordInfo); // Insert last word
    fin.close();
}