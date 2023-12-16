#include "Game2View.h"

Game2View::Game2View(const Game2Model& model) : model(model), boardView(model.getBoardModel()) {
	// Initialize pieceViews
	for (const Piece2Model* piece : model.allPieces()) {
		pieceViews.emplace_back(*piece, model.getBoardModel());
	}
}

void Game2View::draw(sf::RenderWindow &window) {
	// Draw the board
	boardView.draw(window);

	// Draw the pieces
	for (Piece2View& pieceView : pieceViews) {
		pieceView.draw(window);
	}
}