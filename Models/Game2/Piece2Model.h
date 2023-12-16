#ifndef PIECE2MODEL_H
#define PIECE2MODEL_H

#include <vector>

class Piece2Model {
private:
	std::vector<int> possibleMoves;

	char m_type; //'Q' = Queen , 'P' = Pawn
	bool m_player; // true == White , false == Black
	int m_position; // 0-99 board, -1 dead

public:
	Piece2Model();
	~Piece2Model();

	void setPiece(char type, bool player, int pos);
	void setPosition(int pos);
	void setType(char ty);
	void setPlayer(bool bl);

	char getType() const;
	bool getPlayer() const;
	int getPosition() const;

	std::vector<int>& getPossibleMoves();
};

#endif