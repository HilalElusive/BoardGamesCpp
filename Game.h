#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <array>
#include "Board.h"
#include "Piece.h"

class Game : public sf::Drawable {
private:
	Board board;
	Piece* selectedPiece;

	std::array<Piece, 24> whitePieces;
	std::array<Piece, 24> blackPieces;

	std::vector<sf::RectangleShape> possibleMovesSquares;
	std::vector<int> validPotentialMove;
	std::vector<Piece*> capturablePieces;
	std::vector<Piece*> capturingPieces;

	bool playerTurn; // true = White turn, false = Black Turn
	bool selected;
	void createMovesSquares();
	void capturing(int endPosition);

	//Helper functions
	std::vector<int> getIntermediatePositions(int from, int to, int step = 1);
	bool isPositionOccupied(int position, const std::vector<Piece>& allPieces);
	bool hasIntermediateObstacles(std::vector<int>& intermediatePositions, std::vector<Piece>& allPieces);
	Piece* findPieceAtPosition(int position);

	std::vector<int> validQueenCaptures(Piece* piece, std::vector<Piece>& allPieces);
	std::vector<int> validPawnCaptures(Piece* piece, std::vector<Piece>& allPieces);

	std::vector<int> validPossibleMoves();
	void validRectangularPieceMoves(std::vector<int>& moves);
	void validKingMoves(std::vector<int>& moves);

	void pawnPromotion(Piece* pawn);
	bool checkmate();
	bool isKingCheckmated(const Piece& king);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Game(sf::Color bordCol1 = sf::Color::White, sf::Color bordCol2 = sf::Color::Black);

	void selectPiece(int pos);
	void moveSelected(int pos);
	void findCapturingScenarios();

	void restart();
	bool turnInitialized;

	bool isSelected();
	Board& getBoard();
};


#endif