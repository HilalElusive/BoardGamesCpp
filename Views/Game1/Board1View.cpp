#include "Board1View.h"

Board1View::Board1View(const Board1Model & model) : model(model) {
	sf::Color col = sf::Color(255, 255, 255);
	load(col);
}

void Board1View::load(sf::Color col) {
	float xOffset, yOffset = 2.0f;
	sf::Vector2f size = model.getSquareSize(); // Uniform size for all squares

	for (int i = 0; i < 8; i++) {
		xOffset = 2.0f; // Reset xOffset for each new row

		for (int j = 0; j < 8; j++) {
			int index = i * 8 + j;
			m_boardSquares[index].setPosition(sf::Vector2f(xOffset, yOffset));
			m_boardSquares[index].setSize(size);
			m_boardSquares[index].setFillColor(col);
			m_boardSquares[index].setOutlineThickness(2.f);
			m_boardSquares[index].setOutlineColor(sf::Color(0, 0, 0));

			xOffset += size.x;
		}
		yOffset += size.y;
	}
}

void Board1View::draw(sf::RenderWindow & window) const {
	for (const sf::RectangleShape& square : m_boardSquares) {
		window.draw(square);
	}
}
