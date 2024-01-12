#include "Board3View.h"

Board3View::Board3View(const Board3Model& model) : BoardView(model) {
	// Defining colors for the board
	std::vector<sf::Color> squareColors = {
		sf::Color(239, 156, 115), // Color 1
		sf::Color(255, 206, 140)  // Color 2
	};
	sf::Color outline = sf::Color(134, 68, 2);

	load(squareColors, 2.f, outline);
}