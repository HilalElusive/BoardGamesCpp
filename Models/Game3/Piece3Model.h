#ifndef PIECE3MODEL_H
#define PIECE3MODEL_H

#include "../Strategy/MovementStrategy.h"

class Piece3Model : public PieceModel {
private:
	MovementStrategy* movementStrategy;

	char m_type; //'K'=King , 'Q' = Queen , 'P' = Pawn
	bool m_player; // true == White , false == Black

public:
	Piece3Model();
	~Piece3Model();

	void setType(char ty);
	void setPlayer(bool bl);

	char getType() const;
	bool getPlayer() const;

	void setPiece(char type, bool player, int pos);
	void setStrategy(MovementStrategy* strategy);

	std::vector<int>& getPossibleMoves() override;
};

#endif