#include "Board2View.h"

Board2View::Board2View(const Board2Model& model) : BoardView(model) {
	// Defining colors for the board
	std::vector<sf::Color> squareColors = {
		sf::Color(255, 206, 158), // Color 1
		sf::Color(209, 139, 71)  // Color 2
	};

	load(squareColors);
}