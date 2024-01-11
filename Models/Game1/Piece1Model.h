#ifndef PIECE1MODEL_H
#define PIECE1MODEL_H

#include "../Piece/PieceModel.h"

class Piece1Model : public PieceModel {
private:
	char m_color; //'J' = Jaune , 'N' = Noire, 'R' = Rouge
	int m_value; //N = 3 points, R = 2 points, J = 1 point

public:
	Piece1Model();
	~Piece1Model();

	void setPiece(char color, int pos);
	void setColor(char cl);
	void setValue(int vl);

	char getColor() const;
	int getValue() const;

	std::vector<int>& getPossibleMoves() override;
};

#endif