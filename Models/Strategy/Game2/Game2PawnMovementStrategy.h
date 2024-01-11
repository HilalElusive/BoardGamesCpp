#ifndef GAME2_PAWN_MOVEMENT_STRATEGY_H
#define GAME2_PAWN_MOVEMENT_STRATEGY_H

#include "../MovementStrategy.h"

class Game2PawnMovementStrategy : public MovementStrategy
{
public:
	void generatePossibleMoves(PieceModel& piece, std::vector<int>& move) override;
};

#endif