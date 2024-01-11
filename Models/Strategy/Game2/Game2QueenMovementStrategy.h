#ifndef GAME2_QUEEN_MOVEMENT_STRATEGY_H
#define GAME2_QUEEN_MOVEMENT_STRATEGY_H

#include "../MovementStrategy.h"

class Game2QueenMovementStrategy : public MovementStrategy {
public:
	void generatePossibleMoves(PieceModel& piece, std::vector<int>& move) override;
};

#endif