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

	std::vector<int> validPotentialMove;
	std::vector<std::vector<int>> validCaptures(const Piece1Model* piece);
	void exploreCaptures(const Piece1Model* piece, int currentPosition, std::vector<int>& currentSequence, std::vector<std::vector<int>>& allSequences);
	std::vector<const Piece1Model*> capturablePieces;

	bool turnInitialized;
	bool selected;
	bool removalPhase;
	int currentPlayerIndex; // Index of the current player

	void nextTurn();
	void capturing(int endPosition);

	Piece1Model* findPieceAtPosition(int position);
	bool isValidMove(int fromPos, int toPos);

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

	const std::vector<int>& getValidMoves() const;
	const Board1Model& getBoardModel() const;
	const std::array<Piece1Model, 64>& allPieces() const;
};

#endif