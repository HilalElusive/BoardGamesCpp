#include "Board1View.h"

Board1View::Board1View(const Board1Model& model) : BoardView(model) {
	// Defining colors for the board
	std::vector<sf::Color> squareColors = {
		sf::Color(255, 255, 255), // Color 1
	};

	load(squareColors, 2.f);
}