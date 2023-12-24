#include "Piece1View.h"
#include <iostream>

Piece1View::Piece1View(const Piece1Model & pieceModel, const Board1Model & boardModel) 
	: pieceModel(pieceModel), boardModel(boardModel), lastKnownPosition(-1) {
	// Initialize the texture (sf::CircleShape)
	texture.setRadius(boardModel.getSquareSize().x / 2 - 5);
	texture.setOrigin(texture.getRadius(), texture.getRadius()); // Set origin to the center
	setPieceColor(); // Set piece color accordingly
}

void Piece1View::draw(sf::RenderWindow & window) {
	if (pieceModel.getPosition() != -1) {
		if (lastKnownPosition != pieceModel.getPosition()) {
			alignTexture();
			lastKnownPosition = pieceModel.getPosition(); // Update the last known position
		}
		window.draw(texture);
	}
}

void Piece1View::alignTexture() {
	if (pieceModel.getPosition() == -1) return;

	const sf::Vector2f& position = boardModel.getSquarePositions()[pieceModel.getPosition()];
	const sf::Vector2f& size = boardModel.getSquareSize();

	// Align the center of the texture to the center of the square
	texture.setPosition(position.x + size.x / 2, position.y + size.y / 2);
}

void Piece1View::setPieceColor() {
	switch (pieceModel.getColor()) {
	case 'J':
		texture.setFillColor(sf::Color(255, 225, 93));
		break;
	case 'N':
		texture.setFillColor(sf::Color::Black);
		break;
	case 'R':
		texture.setFillColor(sf::Color(191, 49, 49));
		break;
	default:
		std::cerr << "Error: piece type does not exist.\n";
		return;
	}
}
