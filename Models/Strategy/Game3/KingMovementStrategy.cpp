#include "KingMovementStrategy.h"
#include "../../Game3/Piece3Model.h"

void KingMovementStrategy::generatePossibleMoves(PieceModel& p, std::vector<int>& moves) {
	// Downcast to Piece3Model
	Piece3Model& piece = dynamic_cast<Piece3Model&>(p);
	moves.clear();
	int position = piece.getPosition();
	int AheadOrBellow = piece.getPlayer() ? -30 : 30;
	int LeftorRight = piece.getPlayer() ? -2 : 2;

	if (position + AheadOrBellow >= 0 && position + AheadOrBellow < 225) moves.push_back(position + AheadOrBellow);
	if (position - AheadOrBellow >= 0 && position - AheadOrBellow < 225) moves.push_back(position - AheadOrBellow);

	if (position % 30 != 16) { // Not left edge for white or black
		if (piece.getPlayer()) {
			if (position + LeftorRight >= 0 && position + LeftorRight < 225) moves.push_back(position + LeftorRight);
		}
		else if (position - LeftorRight >= 0 && position - LeftorRight < 225) moves.push_back(position - LeftorRight);
	}
	if (position % 30 != 28) { // Not right edge for white or black
		if (piece.getPlayer()) {
			if (position - LeftorRight >= 0 && position - LeftorRight < 225) moves.push_back(position - LeftorRight);
		}
		else if (position + LeftorRight >= 0 && position + LeftorRight < 225) moves.push_back(position + LeftorRight);
	}
}