#ifndef PIECE1MODEL_H
#define PIECE1MODEL_H

#include <vector>

class Piece1Model {
private:
	std::vector<int> possibleMoves;

	char m_color; //'J' = Jaune , 'N' = Noire, 'R' = Rouge
	int m_position; // 0-63 board, -1 dead
	int m_value; //N = 3 points, R = 2 points, J = 1 point
public:
	Piece1Model();
	~Piece1Model();

	void setPiece(char color, int pos);
	void setPosition(int pos);
	void setColor(char cl);
	void setValue(int vl);

	char getColor() const;
	int getPosition() const;
	int getValue() const;

};

#endif