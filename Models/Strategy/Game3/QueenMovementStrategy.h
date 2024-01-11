#ifndef QUEEN_MOVEMENT_STRATEGY_H
#define QUEEN_MOVEMENT_STRATEGY_H

#include "../MovementStrategy.h"

class QueenMovementStrategy : public MovementStrategy {
public:
	void generatePossibleMoves(PieceModel& piece, std::vector<int>& move) override;
};

#endif