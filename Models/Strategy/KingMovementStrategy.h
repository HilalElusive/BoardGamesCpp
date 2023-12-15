#ifndef KING_MOVEMENT_STRATEGY_H
#define KING_MOVEMENT_STRATEGY_H

#include "MovementStrategy.h"

class KingMovementStrategy : public MovementStrategy {
public:
	void generatePossibleMoves(Piece& piece, std::vector<int>& move) override;
};
#endif
