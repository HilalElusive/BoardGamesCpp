#ifndef GAME3MODEL_H
#define GAME3MODEL_H

#include "../BoardModel.h"
#include "../Player/Player.h"
#include "../../Piece.h"

class Game3Model {
private:
	BoardModel board;
	Piece* selectedPiece;

	Player player1;
	Player player2;

	std::vector<int> validPotentialMove;
	std::vector<Piece*> capturablePieces;
	std::vector<const Piece*> capturingPieces;

	std::vector<int> validPossibleMoves();

	bool playerTurn; // true = White turn, false = Black Turn
	bool selected;
	void capturing(int endPosition);

	//Helper functions
	std::vector<int> getIntermediatePositions(int from, int to, int step = 1);
	bool isPositionOccupied(int position, const std::vector<const Piece*>& allPieces) const;
	bool hasIntermediateObstacles(std::vector<int>& intermediatePositions, const std::vector<const Piece*>& allPieces) const;
	Piece* findPieceAtPosition(int position);

	std::vector<int> validQueenCaptures(const Piece* piece, const std::vector<const Piece*>& allPieces);
	std::vector<int> validPawnCaptures(const Piece* piece, const std::vector<const Piece*>& allPieces);

	void validRectangularPieceMoves(std::vector<int>& moves, const std::vector<const Piece*>& allPieces);
	void validKingMoves(std::vector<int>& moves, const std::vector<const Piece*>& allPieces);

	void pawnPromotion(Piece* pawn);
	bool checkmate();
	bool isKingCheckmated(const Piece& king);

public:
	Game3Model();

	void selectPiece(int pos);
	void moveSelected(int pos);
	void findCapturingScenarios();

	const std::vector<int>& getValidMoves() const;
	std::vector<const Piece*> allPieces() const;

	void restart();
	bool turnInitialized;

	bool isSelected();
	const BoardModel& getBoardModel() const;
};

#endif