#ifndef MOVEMENT_STRATEGY_H
#define MOVEMENT_STRATEGY_H

#include <vector>

// Forward declaration of Piece
class Piece;

class MovementStrategy {
public:
	virtual ~MovementStrategy() {}

	// Generates possible moves for a piece. The implementation varies for different types of pieces.
	virtual void generatePossibleMoves(Piece& piece, std::vector<int>& moves) = 0;
};

#endif