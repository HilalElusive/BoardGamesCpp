#include "Game3View.h"

Game3View::Game3View(const Game3Model& model) : model(model), boardView(model.getBoardModel()) {
	// Initialize pieceViews
	for (const Piece3Model* piece : model.allPieces()) {
		pieceViews.emplace_back(*piece, model.getBoardModel());
	}
}

void Game3View::draw(sf::RenderWindow &window) {
	// Draw the board
	boardView.draw(window);

	// Draw the pieces
	for (Piece3View& pieceView : pieceViews) {
		pieceView.draw(window);
	}

	// Draw possible moves
	if (model.isSelected()) {
		std::vector<sf::RectangleShape> possibleMovesSquares;
		createMovesSquares(possibleMovesSquares);
		for (const sf::RectangleShape& square : possibleMovesSquares) {
			window.draw(square);
		}
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