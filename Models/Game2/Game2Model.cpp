#include "Game2Model.h"

Game2Model::Game2Model() : board(), player1(1, "Player One", true), player2(2, "Player Two", false) {
	restart();
}

void Game2Model::restart() {
	player1.initializePieces(true); // true so that player1 get white colored pieces
	player2.initializePieces(false);  // false so that player2 get black colored pieces
}

std::vector<const Piece2Model*> Game2Model::allPieces() const {
	std::vector<const Piece2Model*> combinedPieces;

	// Add pieces from player1
	for (const Piece2Model& piece : player1.getPieces()) {
		if (piece.getPosition() != -1) combinedPieces.push_back(&piece);
	}

	// Add pieces from player2
	for (const Piece2Model& piece : player2.getPieces()) {
		if (piece.getPosition() != -1) combinedPieces.push_back(&piece);
	}

	return combinedPieces;
}

const Board2Model & Game2Model::getBoardModel() const { return board; }