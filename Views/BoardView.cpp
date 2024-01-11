#include "BoardView.h"

BoardView::BoardView(const Board3Model& model) : model(model) {
	// You may initialize default colors here, or use a separate load function
	sf::Color col1 = sf::Color(239, 156, 115);
	sf::Color col2 = sf::Color(255, 206, 140);

	load(col1, col2);
}

void BoardView::load(sf::Color col1, sf::Color col2) {
	float xOffset, yOffset = 2.0f;
	sf::Vector2f size;
	for (int i = 0; i < 15; i++) {
		xOffset = 2.0f; // Reset the xOffset for each new row

		for (int j = 0; j < 15; j++) {
			int position = i * 15 + j + 1;
			size = model.determineSquareSize(position);

			m_boardSquares[j + (i * 15)].setPosition(sf::Vector2f(xOffset, yOffset));
			m_boardSquares[j + (i * 15)].setSize(size);
			m_boardSquares[j + (i * 15)].setFillColor((i + j) % 2 == 0 ? col1 : col2);
			m_boardSquares[j + (i * 15)].setOutlineThickness(2.f);
			m_boardSquares[j + (i * 15)].setOutlineColor(sf::Color(134, 68, 2));

			xOffset += size.x; // Update the xOffset for the next square in the row
		}
		yOffset += model.determineSquareSize(i * 15 + 1).y; // Update the yOffset for the next row
	}
}

void BoardView::draw(sf::RenderWindow& window) const{
	for (const auto& square : m_boardSquares) {
		window.draw(square);
	}
}
