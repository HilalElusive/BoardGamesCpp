#include "Board2View.h"
#include <iostream>

Board2View::Board2View(const Board2Model& model) : model(model) {
	sf::Color col1 = sf::Color(255, 206, 158);
	sf::Color col2 = sf::Color(209, 139, 71);

	load(col1, col2);
}

void Board2View::load(sf::Color col1, sf::Color col2) {
	float xOffset = 0.0f, yOffset = 0.0f;
	sf::Vector2f size = model.getSquareSize(); // Uniform size for all squares

	for (int i = 0; i < 10; i++) {
		xOffset = 0.0f; // Reset xOffset for each new row

		for (int j = 0; j < 10; j++) {
			int index = i * 10 + j;
			m_boardSquares[index].setPosition(sf::Vector2f(xOffset, yOffset));
			m_boardSquares[index].setSize(size);
			m_boardSquares[index].setFillColor((i + j) % 2 == 0 ? col1 : col2);

			xOffset += size.x;
		}
		yOffset += size.y;
	}
}

void Board2View::draw(sf::RenderWindow& window) const {
	for (const sf::RectangleShape& square : m_boardSquares) {
		window.draw(square);
	}
}