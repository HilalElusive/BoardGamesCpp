#ifndef PLAYER2_H
#define PLAYER2_H

#include "../Player/Player.h"
#include "Piece2Model.h"

class Game2Player : public Player {
private:
	std::array<Piece2Model, 20> pieces;

public:
	Game2Player(int id, const std::string& name);

	const std::array<Piece2Model, 20>& getPieces() const;
	Piece2Model* findPieceAtPosition(int position);
	void initializePieces(bool player) override;
};

#endif