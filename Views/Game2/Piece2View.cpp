#include "Piece2View.h"
#include <iostream>

Piece2View::Piece2View(const Piece2Model & pieceModel, const Board2Model& boardModel)
	: pieceModel(pieceModel), boardModel(boardModel), lastKnownType(pieceModel.getType()), lastKnownPosition(-1) {
	setTexture();
}

void Piece2View::alignTexture() {
	if (pieceModel.getPosition() == -1) return;

	const sf::Vector2f& position = boardModel.getSquarePositions()[pieceModel.getPosition()];
	const sf::Vector2f& size = boardModel.getSquareSize();

	m_sprite.setPosition(position.x + 1 + size.x / 2, position.y + 1 + size.y / 2);
}

bool Piece2View::needsTextureUpdate() {
	char currentType = pieceModel.getType();
	if (lastKnownType != currentType) {
		lastKnownType = currentType; // Update the last known type
		return true;
	}
	return false;
}

void Piece2View::draw(sf::RenderWindow & window) {
	if (pieceModel.getPosition() != -1) {
		if (lastKnownType == 'P' && needsTextureUpdate()) setTexture();
		if (lastKnownPosition != pieceModel.getPosition()) {
			alignTexture();
			lastKnownPosition = pieceModel.getPosition(); // Update the last known position
		}
		window.draw(m_sprite);
	}
}

void Piece2View::setTexture() {
	sf::Texture* texture = nullptr;

	switch (pieceModel.getType()) {
	case 'Q':
		texture = &(pieceModel.getPlayer() ? PieceTextures::loadTexture("Textures/dame_blanche_2.png", PieceTextures::whiteQueen3)
			: PieceTextures::loadTexture("Textures/dame_noire_2.png", PieceTextures::blackQueen3));
		break;
	case 'P':
		texture = &(pieceModel.getPlayer() ? PieceTextures::loadTexture("Textures/pion_blanc_2.png", PieceTextures::whitePawn3)
			: PieceTextures::loadTexture("Textures/pion_noir_2.png", PieceTextures::blackPawn3));
		break;
	default:
		std::cerr << "Error: piece type does not exist.\n";
		return;
	}

	if (texture) {
		m_sprite.setTexture(*texture);
		m_sprite.setScale(sf::Vector2f(1.1f, 1.1f));
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	}
	else {
		std::cerr << "Error: failed to load texture.\n";
	}
}