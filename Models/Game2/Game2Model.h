#ifndef GAME2MODEL_H
#define GAME2MODEL_H

#include "Board2Model.h"
#include "Game2Player.h"

class Game2Model {
private:
	Board2Model board;
	Piece2Model* selectedPiece;

	Game2Player player1;
	Game2Player player2;

public:
	Game2Model();

	void restart();
	bool turnInitialized;

	std::vector<const Piece2Model*> allPieces() const;
	const Board2Model& getBoardModel() const;
};

#endif