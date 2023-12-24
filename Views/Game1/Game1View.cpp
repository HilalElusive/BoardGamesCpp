#include "Game1View.h"

Game1View::Game1View(const Game1Model & model) : model(model), boardView(model.getBoardModel()) {
	// Initialize pieceViews
	for (const Piece1Model& piece : model.allPieces()) {
		pieceViews.emplace_back(piece, model.getBoardModel());
	}
}

void Game1View::draw(sf::RenderWindow & window) {
	// Draw the board
	boardView.draw(window);

	// Draw the pieces
	for (Piece1View& pieceView : pieceViews) {
		pieceView.draw(window);
	}
}

void Game1View::createMovesSquares(std::vector<sf::RectangleShape>& squares)
{
}
