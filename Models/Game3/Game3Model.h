#ifndef GAME3MODEL_H
#define GAME3MODEL_H

#include "Board3Model.h"
#include "Game3Player.h"
#include "Piece3Model.h"

class Game3Model {
private:
	Board3Model board;
	Piece3Model* selectedPiece;

	Game3Player player1;
	Game3Player player2;

	std::vector<int> validPotentialMove;
	std::vector<Piece3Model*> capturablePieces;
	std::vector<const Piece3Model*> capturingPieces;

	std::vector<int> validPossibleMoves();

	bool playerTurn; // true = White turn, false = Black Turn
	bool turnInitialized;
	bool selected;

	//Helper functions
	std::vector<int> getIntermediatePositions(int from, int to, int step = 1);
	bool isPositionOccupied(int position, const std::vector<const Piece3Model*>& allPieces) const;
	bool hasIntermediateObstacles(std::vector<int>& intermediatePositions, const std::vector<const Piece3Model*>& allPieces) const;
	Piece3Model* findPieceAtPosition(int position);

	std::vector<int> validQueenCaptures(const Piece3Model* piece, const std::vector<const Piece3Model*>& allPieces);
	std::vector<int> validPawnCaptures(const Piece3Model* piece, const std::vector<const Piece3Model*>& allPieces);

	void validRectangularPieceMoves(std::vector<int>& moves, const std::vector<const Piece3Model*>& allPieces);
	void validKingMoves(std::vector<int>& moves, const std::vector<const Piece3Model*>& allPieces);

	void capturing(int endPosition);
	void pawnPromotion(Piece3Model* pawn);
	bool checkmate();
	bool isKingCheckmated(const Piece3Model& king);

public:
	Game3Model();

	void selectPiece(int pos);
	void moveSelected(int pos);
	void findCapturingScenarios();

	const std::vector<int>& getValidMoves() const;
	std::vector<const Piece3Model*> allPieces() const;

	void restart();
	void setTurnInit(bool turn);

	bool isSelected() const;
	bool isTurnInitialized() const;
	const Board3Model& getBoardModel() const;
};

#endif