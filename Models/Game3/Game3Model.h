#ifndef GAME3MODEL_H
#define GAME3MODEL_H

#include "../BoardModel.h"
#include "../Player/Player.h"
#include "Piece3Model.h"

class Game3Model {
private:
	BoardModel board;
	Piece3Model* selectedPiece;

	Player player1;
	Player player2;

	std::vector<int> validPotentialMove;
	std::vector<Piece3Model*> capturablePieces;
	std::vector<const Piece3Model*> capturingPieces;

	std::vector<int> validPossibleMoves();

	bool playerTurn; // true = White turn, false = Black Turn
	bool selected;
	void capturing(int endPosition);

	//Helper functions
	std::vector<int> getIntermediatePositions(int from, int to, int step = 1);
	bool isPositionOccupied(int position, const std::vector<const Piece3Model*>& allPieces) const;
	bool hasIntermediateObstacles(std::vector<int>& intermediatePositions, const std::vector<const Piece3Model*>& allPieces) const;
	Piece3Model* findPieceAtPosition(int position);

	std::vector<int> validQueenCaptures(const Piece3Model* piece, const std::vector<const Piece3Model*>& allPieces);
	std::vector<int> validPawnCaptures(const Piece3Model* piece, const std::vector<const Piece3Model*>& allPieces);

	void validRectangularPieceMoves(std::vector<int>& moves, const std::vector<const Piece3Model*>& allPieces);
	void validKingMoves(std::vector<int>& moves, const std::vector<const Piece3Model*>& allPieces);

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
	bool turnInitialized;

	bool isSelected() const;
	const BoardModel& getBoardModel() const;
};

#endif