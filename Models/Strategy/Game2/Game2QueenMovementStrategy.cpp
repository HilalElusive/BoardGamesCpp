#include "Game2QueenMovementStrategy.h"
#include "../../Game2/Piece2Model.h"

void Game2QueenMovementStrategy::generatePossibleMoves(PieceModel& p, std::vector<int>& moves) {
	// Downcast to Piece2Model
	Piece2Model* piece = dynamic_cast<Piece2Model*>(&p);
	moves.clear();
	// Directions: up-right, up-left, down-right, down-left
	int directions[] = { -9, -11, 11, 9 };

	// Check each direction
	for (int dir : directions) {
		int currentPos = piece->getPosition();
		// Move in the current direction until the edge of the board is reached
		while (true) {
			int nextPos = currentPos + dir;
			// Check if the next position is still on the board
			if (nextPos < 0 || nextPos >= 100) break;
			// Check for edge wrapping
			int currentColumn = currentPos % 10;
			int nextColumn = nextPos % 10;
			if (abs(currentColumn - nextColumn) > 1) break; // Prevent wrapping
			// Update position and add the move to the list of possible moves
			currentPos = nextPos;
			moves.push_back(currentPos);
		}
	}
}