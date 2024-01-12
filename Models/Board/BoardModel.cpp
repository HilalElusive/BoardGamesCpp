#include "BoardModel.h"

const std::vector<sf::Vector2f>& BoardModel::getSquarePositions() const {
	return squarePositions;
}

const std::vector<sf::Vector2f>& BoardModel::getSquareSizes() const {
	return squareSizes;
}

int BoardModel::getClickedSquareIndex(const sf::Event::MouseButtonEvent & clickPosition) const {
	for (int i = 0; i < squarePositions.size(); ++i) {
		const sf::Vector2f& size = squareSizes[i];
		const sf::Vector2f& position = squarePositions[i];

		if (clickPosition.x >= position.x && clickPosition.x < position.x + size.x &&
			clickPosition.y >= position.y && clickPosition.y < position.y + size.y) {
			return i;
		}
	}
	return -1;
}

void BoardModel::initializeSquares(int boardSize, const sf::Vector2f & uniformSize){
	squarePositions.resize(boardSize);
	squareSizes.resize(boardSize, uniformSize);

	// Initialize square sizes and positions
	float xOffset = 0.0f, yOffset = 0.0f;
	int rowLength = static_cast<int>(std::sqrt(boardSize));

	for (int i = 0; i < boardSize; ++i) {
		// Calculate and store the position
		squarePositions[i] = sf::Vector2f(xOffset, yOffset);

		// Update offsets for the next square
		xOffset += uniformSize.x;
		if ((i + 1) % rowLength == 0) {
			xOffset = 0.0f;
			yOffset += uniformSize.y;
		}
	}
}