#include "Board1Model.h"

Board1Model::Board1Model() {
	squareSize = sf::Vector2f(72.5f, 72.5f);
	float xOffset = 0.0f, yOffset = 0.0f;

	for (int i = 0; i < 64; i++) {
		squarePositions[i] = sf::Vector2f(xOffset, yOffset);

		xOffset += squareSize.x;
		if ((i + 1) % 8 == 0) {
			xOffset = 0.0f;
			yOffset += squareSize.y;
		}
	}
}

const sf::Vector2f Board1Model::getSquareSize() const {
	return squareSize;
}

const std::array<sf::Vector2f, 64>& Board1Model::getSquarePositions() const {
	return squarePositions;
}

int Board1Model::getClickedSquareIndex(const sf::Event::MouseButtonEvent& clickPosition) const {
	int col = static_cast<int>((clickPosition.x - 2) / squareSize.x);
	int row = static_cast<int>((clickPosition.y - 2) / squareSize.y);

	if (col >= 0 && col < 8 && row >= 0 && row < 8) {
		return row * 8 + col;
	}
	return -1;
}
