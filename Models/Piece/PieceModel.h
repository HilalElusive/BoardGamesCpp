#ifndef PIECE_MODEL_H
#define PIECE_MODEL_H

#include <vector>

class PieceModel {
protected:
	int m_position; // Position on the board
	bool m_moved;
	std::vector<int> possibleMoves;

public:
	PieceModel();
	virtual ~PieceModel();

	void setPosition(int pos);
	void setMoved(bool moved);

	int getPosition() const;
	bool hasMoved() const;

	virtual std::vector<int>& getPossibleMoves() = 0;
};

#endif