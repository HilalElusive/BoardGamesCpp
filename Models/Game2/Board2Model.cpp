#include "Board2Model.h"

Board2Model::Board2Model() {
	squareSize = sf::Vector2f(58.4f, 58.4f);
	float xOffset = 0.0f, yOffset = 0.0f;

	for (int i = 0; i < 100; i++) {
		squarePositions[i] = sf::Vector2f(xOffset, yOffset);

		xOffset += squareSize.x;
		if ((i + 1) % 10 == 0) {
			xOffset = 0.0f;
			yOffset += squareSize.y;
		}
	}
}

const sf::Vector2f Board2Model::getSquareSize() const {
	return squareSize;
}

const std::array<sf::Vector2f, 100>& Board2Model::getSquarePositions() const {
	return squarePositions;
}

int Board2Model::getClickedSquareIndex(const sf::Event::MouseButtonEvent& clickPosition) const {
	int col = static_cast<int>((clickPosition.x - 2) / squareSize.x);
	int row = static_cast<int>((clickPosition.y - 2) / squareSize.y);

	if (col >= 0 && col < 10 && row >= 0 && row < 10) {
		return row * 10 + col;
	}
	return -1;
}