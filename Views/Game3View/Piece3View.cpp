#include "Piece3View.h"
#include <iostream>

Piece3View::Piece3View(const Piece3Model& pieceModel, const BoardModel& boardModel)
	: model(pieceModel), boardModel(boardModel), lastKnownType(pieceModel.getType()), lastKnownPosition(-1) {
	setTexture();
}

void Piece3View::draw(sf::RenderWindow& window){
	if (model.getPosition() != -1) {
		if (lastKnownType == 'P' && needsTextureUpdate()) setTexture();
		if (lastKnownPosition != model.getPosition()) {
			alignTexture();
			lastKnownPosition = model.getPosition(); // Update the last known position
		}
		window.draw(m_sprite);
	}
}

bool Piece3View::needsTextureUpdate() {
	char currentType = model.getType();
	if (lastKnownType != currentType) {
		lastKnownType = currentType; // Update the last known type
		return true;
	}
	return false;
}

void Piece3View::alignTexture() {
	if (model.getPosition() == -1) return;

	const sf::Vector2f& position = boardModel.getSquarePositions()[model.getPosition()];
	const sf::Vector2f& size = boardModel.getSquareSizes()[model.getPosition()];

	int rotation = static_cast<int>(m_sprite.getRotation()) % 180;
	if ((model.getPosition() % 30 < 15 && rotation == 0) || (model.getPosition() % 30 >= 15 && rotation != 0)) {
		m_sprite.rotate(90);
	}
	m_sprite.setPosition(position.x + 1 + size.x / 2, position.y + 1 + size.y / 2);
}

void Piece3View::setTexture() {
	sf::Texture* texture = nullptr;

	switch (model.getType()) {
	case 'K':
		texture = &(model.getPlayer() ? PieceTextures::loadTexture("Textures/roi_blanc.png", PieceTextures::whiteKing)
			: PieceTextures::loadTexture("Textures/roi_noir.png", PieceTextures::blackKing));
		break;
	case 'Q':
		texture = &(model.getPlayer() ? PieceTextures::loadTexture("Textures/dame_blanche.png", PieceTextures::whiteQueen)
			: PieceTextures::loadTexture("Textures/dame_noire.png", PieceTextures::blackQueen));
		break;
	case 'P':
		texture = &(model.getPlayer() ? PieceTextures::loadTexture("Textures/pion_blanc.png", PieceTextures::whitePawn)
			: PieceTextures::loadTexture("Textures/pion_noir.png", PieceTextures::blackPawn));
		break;
	default:
		std::cerr << "Error: piece type does not exist.\n";
		return;
	}

	if (texture) {
		m_sprite.setTexture(*texture);
		m_sprite.setScale(sf::Vector2f(1.05f, 1.05f));
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	}
	else {
		std::cerr << "Error: failed to load texture.\n";
	}
}