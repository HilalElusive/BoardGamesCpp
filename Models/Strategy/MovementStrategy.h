#ifndef MOVEMENT_STRATEGY_H
#define MOVEMENT_STRATEGY_H

#include "../Piece/PieceModel.h"

class MovementStrategy {
public:
	virtual ~MovementStrategy() {}

	// Generates possible moves for a piece. The implementation varies for different types of pieces.
	virtual void generatePossibleMoves(PieceModel& piece, std::vector<int>& moves) = 0;
};

#endif