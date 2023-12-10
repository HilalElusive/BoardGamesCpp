#include "Board.h"
#include <iostream>

std::array<sf::Vector2f, 225> Board::squareSizes;
std::array<sf::Vector2f, 225> Board::squarePositions;

Board::Board()
{
	sf::Color col1 = sf::Color(239, 156, 115);
	sf::Color col2 = sf::Color(255, 206, 140);

	load(col1,col2);

	float xOffset = 0.0f, yOffset = 0.0f;

	// Pre-calculate square sizes and positions
	for (int position = 0; position < 225; position++) {
		sf::Vector2f size = determineSquareSize(position + 1);
		Board::squareSizes[position] = size;

		// Calculate and store the position
		Board::squarePositions[position] = sf::Vector2f(xOffset, yOffset);

		// Update offsets
		xOffset += size.x;
		if ((position + 1) % 15 == 0) {
			xOffset = 0.0f;
			yOffset += size.y;
		}
	}
}

sf::Vector2f Board::determineSquareSize(int position) {
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

void Board::load(sf::Color col1, sf::Color col2)
{
	float xOffset, yOffset = 2.0f;
	sf::Vector2f size;
	for (int i = 0; i < 15; i++) {
		xOffset = 2.0f; // Reset the xOffset for each new row

		for (int j = 0; j < 15; j++) {
			int position = i * 15 + j + 1;
			size = determineSquareSize(position);

			m_boardSquares[j + (i * 15)].setPosition(sf::Vector2f(xOffset, yOffset));
			m_boardSquares[j + (i * 15)].setSize(size);
			m_boardSquares[j + (i * 15)].setFillColor((i + j) % 2 == 0 ? col1 : col2);
			m_boardSquares[j + (i * 15)].setOutlineThickness(2.f);
			m_boardSquares[j + (i * 15)].setOutlineColor(sf::Color(134, 68, 2));

			xOffset += size.x; // Update the xOffset for the next square in the row
		}
		yOffset += determineSquareSize(i * 15 + 1).y; // Update the yOffset for the next row
	}
}

int Board::getClickedSquareIndex(const sf::Event::MouseButtonEvent & clickPosition)
{
	for (int i = 0; i < 225; ++i) {
		const sf::Vector2f& size = Board::squareSizes[i];
		const sf::Vector2f& position = Board::squarePositions[i];

		// Check if the click is within the square's bounds
		if (clickPosition.x >= position.x && clickPosition.x < position.x + size.x &&
			clickPosition.y >= position.y && clickPosition.y < position.y + size.y) {
			return i; // Index of the square that was clicked
		}
	}
	return -1;
}

void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < 225; i++) {
		target.draw(m_boardSquares[i]);
	}
}