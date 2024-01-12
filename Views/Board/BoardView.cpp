#include "BoardView.h"

BoardView::BoardView(const BoardModel & model) : model(model) {}

void BoardView::load(const std::vector<sf::Color>& colors, float outlineWeight, sf::Color outline) {
	const auto& sizes = model.getSquareSizes();
	const auto& positions = model.getSquarePositions();

	boardSquares.resize(sizes.size());
	for (int i = 0; i < boardSquares.size(); ++i) {
		//finding the row and column
		int numRows = static_cast<int>(std::sqrt(boardSquares.size()));
		int row = i / numRows;
		int col = i % numRows;

		sf::Vector2f pos; 
		pos.x = positions[i].x + outlineWeight; pos.y = positions[i].y + outlineWeight; //Adding an offset because of the outline

		boardSquares[i].setPosition(pos);
		boardSquares[i].setSize(sizes[i]);
		boardSquares[i].setFillColor(colors[(row + col) % colors.size()]);
		boardSquares[i].setOutlineThickness(outlineWeight);
		boardSquares[i].setOutlineColor(outline); // Default outline color is black
	}
}

void BoardView::draw(sf::RenderWindow& window) const {
	for (const auto& square : boardSquares) {
		window.draw(square);
	}
}