#include "Game3Player.h"

Game3Player::Game3Player(int id, const std::string& name, bool turn) 
    : Player(id, name, turn) {}

const std::array<Piece3Model, 24>& Game3Player::getPieces() const {
	return pieces;
}

Piece3Model * Game3Player::findPieceAtPosition(int position) {
	for (Piece3Model& piece : pieces) {
		if (piece.getPosition() == position) return &piece;
	}
	return nullptr;
}

void Game3Player::initializePieces(bool player) {
	pieces[0].setPiece('K', player, player ? 202 : 22);

	for (int i = 1; i < 9; i++)
		pieces[i].setPiece('Q', player, 2 * (i - 1) + (player ? 195 : 15));

	for (int i = 9; i < 24; i++)
		pieces[i].setPiece('P', player, 2 * (i - 9) + (player ? 165 : 31));
}