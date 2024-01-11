#include "Game2PawnMovementStrategy.h"
#include "../../Game2/Piece2Model.h"
#include <iostream>

void Game2PawnMovementStrategy::generatePossibleMoves(PieceModel & p, std::vector<int>& moves) {
	// Downcast to Piece2Model
	Piece2Model* piece = dynamic_cast<Piece2Model*>(&p);
	bool player = piece->getPlayer();
	int position = piece->getPosition();
	moves.clear();

	int forwardRight = player ? position - 9 : position + 9;
	int forwardLeft = player ? position - 11 : position + 11;

	if (position % 10 != 0) { // Not left edge for white or black
		if (player) {
			if (forwardLeft >= 0 && forwardLeft < 100) moves.push_back(forwardLeft);
		}
		else if (forwardRight >= 0 && forwardRight < 100) moves.push_back(forwardRight);
	}
	if (position % 10 != 9) { // Not right edge for white or black
		if (player) {
			if (forwardRight >= 0 && forwardRight < 100) moves.push_back(forwardRight);
		}
		else if (forwardLeft >= 0 && forwardLeft < 100) moves.push_back(forwardLeft);
	}
}