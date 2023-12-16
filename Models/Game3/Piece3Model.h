#ifndef PIECE3MODEL_H
#define PIECE3MODEL_H

#include <vector>
#include "../Strategy/MovementStrategy.h"

class Piece3Model {
private:
	std::vector<int> possibleMoves;
	MovementStrategy* movementStrategy;

	char m_type; //'K'=King , 'Q' = Queen , 'P' = Pawn
	bool m_player; // true == White , false == Black
	int m_position; // 0-224 board, -1 dead
	bool m_moved;

public:
	Piece3Model();
	~Piece3Model();

	void setPiece(char type, bool player, int pos);
	void setPosition(int pos);
	void setType(char ty);
	void setPlayer(bool bl);
	void setMoved(bool moved);
	void setStrategy(MovementStrategy* strategy);

	char getType() const;
	bool getPlayer() const;
	int getPosition() const;
	bool hasMoved() const;

	std::vector<int>& getPossibleMoves();
};

#endif