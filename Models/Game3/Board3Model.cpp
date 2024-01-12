#include "Board3Model.h"

Board3Model::Board3Model() {
	// A 15x15 board for "BullTricker"
	initializeSquares(225, sf::Vector2f(0.f, 0.f)); // Size is irrelevant here, as it's overridden
}

sf::Vector2f Board3Model::determineSquareSize(int position) const {
	int mod30 = position % 30;
	if (mod30 == 0) mod30 = 30;  // Adjust for positions that are multiples of 30

	bool isFirstHalf = mod30 <= 15;
	bool isEven = mod30 % 2 == 0;

	if (isFirstHalf) {
		return isEven ? sf::Vector2f(60.f, 20.f) : sf::Vector2f(20.f, 20.f);
	}
	else {
		return isEven ? sf::Vector2f(20.f, 60.f) : sf::Vector2f(60.f, 60.f);
	}
}

void Board3Model::initializeSquares(int boardSize, const sf::Vector2f & uniformSize) {
	squareSizes.clear();
	squarePositions.clear();
	squareSizes.reserve(boardSize);
	squarePositions.reserve(boardSize);

	float xOffset = 0.0f, yOffset = 0.0f;

	for (int position = 0; position < boardSize; ++position) {
		sf::Vector2f size = determineSquareSize(position + 1);
		squareSizes.push_back(size);
		squarePositions.emplace_back(xOffset, yOffset);

		xOffset += size.x;
		if ((position + 1) % 15 == 0) {
			xOffset = 0.0f;
			yOffset += size.y;
		}
	}
}