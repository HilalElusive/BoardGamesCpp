#include "PawnMovementStrategy.h"
#include "../../Game3/Piece3Model.h"

void PawnMovementStrategy::generatePossibleMoves(PieceModel & p, std::vector<int>& moves) {
	// Downcast to Piece3Model
	Piece3Model* piece = dynamic_cast<Piece3Model*>(&p);
	bool player = piece->getPlayer();
	int position = piece->getPosition();
	moves.clear();
	
	int forwardRight = player ? position - 14 : position + 14;
	int forwardLeft = player ? position - 16 : position + 16;
	int forwardAhead = player ? -30 : 30;

	if (position % 30 != 15) { // Not left edge for white or black
		if (player) {
			if (forwardLeft >= 0 && forwardLeft < 225) moves.push_back(forwardLeft);
		}
		else if (forwardRight >= 0 && forwardRight < 225) moves.push_back(forwardRight);
	}
	if (position % 30 != 29) { // Not right edge for white or black
		if (player) {
			if (forwardRight >= 0 && forwardRight < 225) moves.push_back(forwardRight);
		}
		else if (forwardLeft >= 0 && forwardLeft < 225) moves.push_back(forwardLeft);
	}
	// Long forward move (30), always an option
	if (position + forwardAhead >= 0 && position + forwardAhead < 225) moves.push_back(position + forwardAhead);
	//Pawn special move
	if (!piece->hasMoved() && position % 30 < 15) moves.push_back(position + 2 * forwardAhead);
}
