#include "Piece.h"
#include "./Models/Strategy/KingMovementStrategy.h"
#include "./Models/Strategy/QueenMovementStrategy.h"
#include "./Models/Strategy/PawnMovementStrategy.h"

Piece::~Piece() {
	delete movementStrategy;
}

void Piece::setPiece(char type, bool player, int pos) {
	if (pos == -1) return;

	setPlayer(player);
	setPosition(pos);
	setMoved(false);
	setType(type);
}

void Piece::setPosition(int pos) {
	m_position = pos;
	m_moved = true;
	alignTexture();
}

void Piece::setType(char ty) { 
	m_type = ty;
	setTexture();

	switch (m_type)
	{
	case 'K':
		setStrategy(new KingMovementStrategy());
		break;
	case 'Q':
		setStrategy(new QueenMovementStrategy());
		break;
	case 'P':
		setStrategy(new PawnMovementStrategy());
		break;
	default:
		std::cerr << "Error: piece type does not exist.\n";
		break;
	}
}

void Piece::setStrategy(MovementStrategy * strategy) {
	delete movementStrategy;
	movementStrategy = strategy;
}

std::vector<int>& Piece::getPossibleMoves() {
	movementStrategy->generatePossibleMoves(*this, possibleMoves);
	return possibleMoves;
}

void Piece::alignTexture() { //Aligns the piece texture in it's according place
	if (m_position == -1) return; 
	// Use the pre-calculated positions
	sf::Vector2f position = Board::squarePositions[m_position];
	sf::Vector2f actualSquare = Board::squareSizes[m_position];

	// Position the piece, rotate it and center it
	int rotation = static_cast<int>(m_sprite.getRotation()) % 180;
	if ((m_position % 30 < 15 && rotation == 0) || (m_position % 30 >= 15 && rotation != 0)) {
		m_sprite.rotate(90);
	}
	m_sprite.setPosition(position.x + 1 + actualSquare.x / 2, position.y + 1 + actualSquare.y / 2);
	return;
}

void Piece::setTexture() {
	sf::Texture* texture = nullptr;

	switch (m_type) {
	case 'K':
		texture = &(m_player ? PieceTextures::loadTexture("Textures/roi_blanc.png", PieceTextures::whiteKing)
			: PieceTextures::loadTexture("Textures/roi_noir.png", PieceTextures::blackKing));
		break;
	case 'Q':
		texture = &(m_player ? PieceTextures::loadTexture("Textures/dame_blanche.png", PieceTextures::whiteQueen)
			: PieceTextures::loadTexture("Textures/dame_noire.png", PieceTextures::blackQueen));
		break;
	case 'P':
		texture = &(m_player ? PieceTextures::loadTexture("Textures/pion_blanc.png", PieceTextures::whitePawn)
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
	else
		std::cerr << "Error: failed to load texture.\n";
}