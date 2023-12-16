#ifndef PLAYER3_H
#define PLAYER3_H

#include "../Player/Player.h"
#include "Piece3Model.h"

class Game3Player : public Player {
private:
	std::array<Piece3Model, 24> pieces;

public:
	Game3Player(int id, const std::string& name, bool turn);

	const std::array<Piece3Model, 24>& getPieces() const;
	Piece3Model* findPieceAtPosition(int position);
	void initializePieces(bool player) override;
};
#endif