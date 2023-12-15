#include "PawnMovementStrategy.h"
#include "../../Piece.h"

void PawnMovementStrategy::generatePossibleMoves(Piece & piece, std::vector<int>& moves) {
	moves.clear();

	int forwardRight = piece.getPlayer() ? piece.getPosition() - 14 : piece.getPosition() + 14;
	int forwardLeft = piece.getPlayer() ? piece.getPosition() - 16 : piece.getPosition() + 16;
	int forwardAhead = piece.getPlayer() ? -30 : 30;

	if (piece.getPosition() % 30 != 15) { // Not left edge for white or black
		if (piece.getPlayer()) {
			if (forwardLeft >= 0 && forwardLeft < 225) moves.push_back(forwardLeft);
		}
		else if (forwardRight >= 0 && forwardRight < 225) moves.push_back(forwardRight);
	}
	if (piece.getPosition() % 30 != 29) { // Not right edge for white or black
		if (piece.getPlayer()) {
			if (forwardRight >= 0 && forwardRight < 225) moves.push_back(forwardRight);
		}
		else if (forwardLeft >= 0 && forwardLeft < 225) moves.push_back(forwardLeft);
	}
	// Long forward move (30), always an option
	if (piece.getPosition() + forwardAhead >= 0 && piece.getPosition() + forwardAhead < 225) moves.push_back(piece.getPosition() + forwardAhead);
	//Pawn special move
	if (!piece.hasMoved() && piece.getPosition() % 30 < 15) moves.push_back(piece.getPosition() + 2 * forwardAhead);
}
