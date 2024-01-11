#ifndef PIECE2MODEL_H
#define PIECE2MODEL_H

#include "../Strategy/MovementStrategy.h"

class Piece2Model : public PieceModel {
private:
	MovementStrategy* movementStrategy;

	char m_type; //'Q' = Queen , 'P' = Pawn
	bool m_player; // true == White , false == Black

public:
	Piece2Model();
	~Piece2Model();

	void setType(char ty);
	void setPlayer(bool bl);

	char getType() const;
	bool getPlayer() const;

	void setPiece(char type, bool player, int pos);
	void setStrategy(MovementStrategy* strategy);

	std::vector<int>& getPossibleMoves();
};

#endif