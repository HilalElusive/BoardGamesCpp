#include "KingMovementStrategy.h"
#include "../../Piece.h"

void KingMovementStrategy::generatePossibleMoves(Piece& piece, std::vector<int>& moves) {
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
