#ifndef PAWN_MOVEMENT_STRATEGY_H
#define PAWN_MOVEMENT_STRATEGY_H

#include "MovementStrategy.h"

class PawnMovementStrategy : public MovementStrategy
{
public:
	//PawnMovementStrategy(Piece& p) { generatePossibleMoves(p); }
	void generatePossibleMoves(Piece3Model& piece, std::vector<int>& move) override;
};

#endif