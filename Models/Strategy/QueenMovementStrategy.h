#ifndef QUEEN_MOVEMENT_STRATEGY_H
#define QUEEN_MOVEMENT_STRATEGY_H

#include "MovementStrategy.h"

class QueenMovementStrategy : public MovementStrategy {
public:
	//QueenMovementStrategy(Piece& p) { generatePossibleMoves(p); }
	void generatePossibleMoves(Piece3Model& piece, std::vector<int>& move) override;
};

#endif