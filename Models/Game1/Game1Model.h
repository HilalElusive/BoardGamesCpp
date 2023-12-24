#ifndef GAME1MODEL_H
#define GAME1MODEL_H

#include "Board1Model.h"
#include "Piece1Model.h"
#include "Game1Player.h"

class Game1Model {
private:
	Board1Model board;
	Piece1Model* selectedPiece;

	std::array<Piece1Model, 64> pieces;
	std::vector<Game1Player> players; // Vector of players

	bool turnInitialized;
	bool selected;
	bool removalPhase;
	int currentPlayerIndex; // Index of the current player

	void nextTurn();
	Piece1Model* findPieceAtPosition(int position);

public:
	Game1Model();

	Game1Player& getCurrentPlayer(); // Get the current player
	void restart();
	void setTurnInit(bool turn);

	void selectPiece(int pos);
	void moveSelected(int pos);

	bool isTurnInitialized() const;
	bool isRemovalPhase() const;
	bool isSelected() const;

	const Board1Model& getBoardModel() const;
	const std::array<Piece1Model, 64>& allPieces() const;
};

#endif