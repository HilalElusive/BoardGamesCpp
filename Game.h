#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <array>
#include "Board.h"
#include "Piece.h"
#include "./Models/Player/Player.h"

class Game : public sf::Drawable {
private:
	Board board;
	Piece* selectedPiece;

	Player player1;
	Player player2;

	std::vector<sf::RectangleShape> possibleMovesSquares;
	std::vector<int> validPotentialMove;
	std::vector<Piece*> capturablePieces;
	std::vector<const Piece*> capturingPieces;

	bool playerTurn; // true = White turn, false = Black Turn
	bool selected;
	void createMovesSquares();
	void capturing(int endPosition);

	//Helper functions
	std::vector<int> getIntermediatePositions(int from, int to, int step = 1);
	bool isPositionOccupied(int position, const std::vector<const Piece*>& allPieces) const;
	bool hasIntermediateObstacles(std::vector<int>& intermediatePositions, const std::vector<const Piece*>& allPieces) const;
	Piece* findPieceAtPosition(int position);
	std::vector<const Piece*> allPieces() const;

	std::vector<int> validQueenCaptures(const Piece* piece, const std::vector<const Piece*>& allPieces);
	std::vector<int> validPawnCaptures(const Piece* piece, const std::vector<const Piece*>& allPieces);

	std::vector<int> validPossibleMoves();
	void validRectangularPieceMoves(std::vector<int>& moves, const std::vector<const Piece*>& allPieces);
	void validKingMoves(std::vector<int>& moves, const std::vector<const Piece*>& allPieces);

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