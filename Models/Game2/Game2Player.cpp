#include "Game2Player.h"

Game2Player::Game2Player(int id, const std::string& name, bool turn)
	: Player(id, name, turn) {}

const std::array<Piece2Model, 20>& Game2Player::getPieces() const {
	return pieces;
}

Piece2Model * Game2Player::findPieceAtPosition(int position) {
	for (Piece2Model& piece : pieces) {
		if (piece.getPosition() == position) return &piece;
	}
	return nullptr;
}

void Game2Player::initializePieces(bool player) {
	int pieceCount = 0;
	for (int i = 0; i < 10 && pieceCount < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if ((i + j) % 2 != 0) { // Check for dark square
				int position = i * 10 + j + (player ? 60 : 0);
				pieces[pieceCount++].setPiece('P', player, position);
			}
			//pieces[pieceCount++].setPiece('P', player, 1);
		}
	}
	/*for (auto& piece : pieces) {
		piece.setPosition(-1);
	}
	
	if (player) {
		pieces[0].setPosition(34);
		pieces[1].setPosition(47);
		pieces[2].setPosition(56);
		pieces[3].setPosition(76);
		pieces[4].setPosition(83);
	}
	else {
		pieces[5].setPosition(45); pieces[5].setType('Q');
		pieces[6].setPosition(16); pieces[6].setType('Q');
	}*/
}