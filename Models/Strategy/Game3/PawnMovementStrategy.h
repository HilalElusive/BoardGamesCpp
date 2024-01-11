#ifndef PAWN_MOVEMENT_STRATEGY_H
#define PAWN_MOVEMENT_STRATEGY_H

#include "../MovementStrategy.h"

class PawnMovementStrategy : public MovementStrategy
{
public:
	void generatePossibleMoves(PieceModel& piece, std::vector<int>& move) override;
};

#endif