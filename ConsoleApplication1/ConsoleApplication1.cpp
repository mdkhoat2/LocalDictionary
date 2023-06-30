#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Application.h"

int main() {

	Application app;

	app.loadEngEngDict();

	app.run();

	return 0;
}
