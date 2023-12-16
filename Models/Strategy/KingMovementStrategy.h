#ifndef KING_MOVEMENT_STRATEGY_H
#define KING_MOVEMENT_STRATEGY_H

#include "MovementStrategy.h"

class KingMovementStrategy : public MovementStrategy {
public:
	void generatePossibleMoves(Piece3Model& piece, std::vector<int>& move) override;
};
#endif
