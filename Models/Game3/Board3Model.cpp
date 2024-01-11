#include "Board3Model.h"

Board3Model::Board3Model() {
	// Initialize square sizes and positions
	float xOffset = 0.0f, yOffset = 0.0f;

	for (int position = 0; position < 225; position++) {
		sf::Vector2f size = determineSquareSize(position + 1);
		squareSizes[position] = size;

		// Calculate and store the position
		squarePositions[position] = sf::Vector2f(xOffset, yOffset);

		// Update offsets for the next square
		xOffset += size.x;
		if ((position + 1) % 15 == 0) {
			xOffset = 0.0f;
			yOffset += size.y;
		}
	}
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

int Board3Model::getClickedSquareIndex(const sf::Event::MouseButtonEvent& clickPosition) const {
	for (int i = 0; i < 225; ++i) {
		const sf::Vector2f& size = squareSizes[i];
		const sf::Vector2f& position = squarePositions[i];

		// Check if the click is within the square's bounds
		if (clickPosition.x >= position.x && clickPosition.x < position.x + size.x &&
			clickPosition.y >= position.y && clickPosition.y < position.y + size.y) {
			return i; // Index of the square that was clicked
		}
	}
	return -1;
}

const std::array<sf::Vector2f, 225>& Board3Model::getSquareSizes() const {
	return squareSizes;
}

const std::array<sf::Vector2f, 225>& Board3Model::getSquarePositions() const {
	return squarePositions;
}