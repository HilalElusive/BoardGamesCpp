#include "QueenMovementStrategy.h"
#include "../../Piece.h"

void QueenMovementStrategy::generatePossibleMoves(Piece & piece, std::vector<int>& moves) {
	moves.clear();

	bool player = piece.getPlayer();
	int position = piece.getPosition();

	int forwardRight = player ? position - 14 : position + 14;
	int forwardLeft = player ? position - 16 : position + 16;
	int BackwardLeft = player ? position + 14 : position - 14;
	int BackwardRight = player ? position + 16 : position - 16;

	int AheadOrBellow = player ? -30 : 30;
	int LeftorRight = player ? -2 : 2;

	if (position % 30 != 15) { // Not left edge for white or black
		if (player) {
			if (forwardLeft >= 0 && forwardLeft < 225) moves.push_back(forwardLeft);
			if (BackwardLeft >= 0 && BackwardLeft < 225) moves.push_back(BackwardLeft);
		}
		else {
			if (forwardRight >= 0 && forwardRight < 225) moves.push_back(forwardRight);
			if (BackwardRight >= 0 && BackwardRight < 225) moves.push_back(BackwardRight);
		}
	}
	if (position % 30 != 29) { // Not left edge for white or black
		if (player) {
			if (forwardRight >= 0 && forwardRight < 225) moves.push_back(forwardRight);
			if (BackwardRight >= 0 && BackwardRight < 225) moves.push_back(BackwardRight);
		}
		else {
			if (forwardLeft >= 0 && forwardLeft < 225) moves.push_back(forwardLeft);
			if (BackwardLeft >= 0 && BackwardLeft < 225) moves.push_back(BackwardLeft);
		}
	}

	while (position + AheadOrBellow >= 0 && position + AheadOrBellow < 225) { //Responsible for continuous foward movement for black and white
		moves.push_back(position + AheadOrBellow);
		player ? AheadOrBellow -= 30 : AheadOrBellow += 30;
	}
	AheadOrBellow = player ? -30 : 30; //resetting the forward movement counter
	while (position - AheadOrBellow >= 0 && position - AheadOrBellow < 225) { //Responsible for continuous backward movement for black and white
		moves.push_back(position - AheadOrBellow);
		player ? AheadOrBellow -= 30 : AheadOrBellow += 30;
	}
	while ((position % 30 > 14 && position % 30 + LeftorRight >= 15 && position % 30 + LeftorRight <= 29) || //Responsible for continuous left movement for black and white
		(position % 30 <= 14 && position % 30 + LeftorRight >= 0 && position % 30 + LeftorRight <= 14)) {
		moves.push_back(position + LeftorRight);
		player ? LeftorRight -= 2 : LeftorRight += 2;
	}
	LeftorRight = player ? -2 : 2; //resetting the side movement (left/right) counter 
	while ((position % 30 > 14 && position % 30 - LeftorRight >= 15 && position % 30 - LeftorRight <= 29) || //Responsible for continuous right movement for black and white
		(position % 30 <= 14 && position % 30 - LeftorRight >= 0 && position % 30 - LeftorRight <= 14)) {
		moves.push_back(position - LeftorRight);
		player ? LeftorRight -= 2 : LeftorRight += 2;
	}
}
