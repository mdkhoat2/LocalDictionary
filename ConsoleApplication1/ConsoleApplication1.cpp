#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Application.h"

int main() {

	Application app;

	app.run();

	// VieTrieNode* root = nullptr;
	// trieInsert(root, L"nữ", "");
	// trieInsert(root, L"hoảng", "");
	// trieInsert(root, L"hoàng", "");
	// trieRemove(root, L"nữ");

	// std::cout << std::boolalpha;
	// if(!trieSearch(root, L"nữ").empty())
	// 	std::cout << "YES" << std::endl;
	// else
	// 	std::cout << "NO" << std::endl;
	
	// if(!trieSearch(root, L"hoảng").empty())
	// 	std::cout << "YES" << std::endl;
	// else
	// 	std::cout << "NO" << std::endl;
	
	// if(!trieSearch(root, L"hoàng").empty())
	// 	std::cout << "YES" << std::endl;
	// else
	// 	std::cout << "NO" << std::endl;

	// trieDeleteAll(root);
	// if(root != nullptr)
	// 	std::cout << "ERROR" << std::endl;

	return 0;
}
