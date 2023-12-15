#include "Game3View.h"

Game3View::Game3View(const Game3Model& model) : model(model), boardView(model.getBoardModel()) {
	// Initialize your view here if needed
}

void Game3View::draw(sf::RenderWindow &window) {
	// Draw the board
	boardView.draw(window);

	// Draw the pieces
	for (const Piece* piece : model.allPieces()) {
		if (piece->getPosition() != -1) {
			window.draw(*piece);
		}
	}

	// Draw possible moves
	std::vector<sf::RectangleShape> possibleMovesSquares;
	createMovesSquares(possibleMovesSquares);
	for (const auto& square : possibleMovesSquares) {
		window.draw(square);
	}
}

void Game3View::createMovesSquares(std::vector<sf::RectangleShape>& squares) {
	for (int i : model.getValidMoves()) {
		sf::RectangleShape tmp;
		tmp.setPosition(model.getBoardModel().getSquarePositions()[i]);
		tmp.setSize(model.getBoardModel().getSquareSizes()[i]);
		tmp.setFillColor(sf::Color(0x66b4cc50));
		squares.push_back(tmp);
	}
}