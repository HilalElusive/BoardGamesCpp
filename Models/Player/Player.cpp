#include "Player.h"

Player::Player(int id, const std::string& name, bool trn) : playerId(id), playerName(name), score(0), turn(trn) {}

int Player::getId() const {
	return playerId;
}

std::string Player::getName() const {
	return playerName;
}

bool Player::hasTurn() const {
	return turn;
}

const std::array<Piece3Model, 24>& Player::getPieces() const{
	return pieces;
}

Piece3Model * Player::findPieceAtPosition(int position) {
	for (Piece3Model& piece : pieces) {
		if (piece.getPosition() == position) return &piece;
	}
	return nullptr;
}

void Player::initializePieces(bool player) {
	pieces[0].setPiece('K', player, player ? 202 : 22);

	for (int i = 1; i < 9; i++)
		pieces[i].setPiece('Q', player, 2 * (i - 1) + (player ? 195 : 15) );

	for (int i = 9; i < 24; i++)
		pieces[i].setPiece('P', player, 2 * (i - 9) + (player ? 165 : 31) );
}
