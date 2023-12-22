#ifndef GAME2MODEL_H
#define GAME2MODEL_H

#include "Board2Model.h"
#include "Game2Player.h"
#include <set>

class Game2Model {
private:
	Board2Model board;
	Piece2Model* selectedPiece;

	Game2Player player1;
	Game2Player player2;

	bool playerTurn;
	bool turnInitialized;
	bool selected;

	std::vector<int> validPotentialMove;
	std::vector<const Piece2Model*> capturingPieces;

	std::vector<int> validPossibleMoves();
	void validPieceMoves(std::vector<int>& moves);
	std::pair<std::vector<std::vector<int>>, int> validPawnCaptures(const Piece2Model* piece);
	std::pair<std::vector<std::vector<int>>, int> validQueenCaptures(const Piece2Model* piece);

	void explorePawnCaptures(const Piece2Model* piece, int currpos, std::vector<int>& currentSequence, std::vector<std::vector<int>>& allLongestSequences);
	void exploreQueenCaptures(const Piece2Model* piece, int currpos, std::vector<int>& currentSequence, std::vector<std::vector<int>>& allLongestSequences, std::set<int>& capturedPositions);

	Piece2Model* findPieceAtPosition(int position);
	bool isPositionInSequence(int position, const std::vector<int>& sequence);
	bool isValidDiagonalMove(int fromPos, int toPos);
	void updateLongestSequences(const std::vector<int>& currentSequence, std::vector<std::vector<int>>& allLongestSequences);

	void capturing(int endPosition);
	void pawnPromotion(Piece2Model * pawn);

public:
	Game2Model();

	void selectPiece(int pos);
	void moveSelected(int pos);
	void findCapturingScenarios();

	void restart();
	void setTurnInit(bool turn);

	const std::vector<int>& getValidMoves() const;
	std::vector<const Piece2Model*> allPieces() const;

	const Board2Model& getBoardModel() const;
	bool isTurnInitialized() const;
	bool isSelected() const;
};

#endif