#include "Piece.h"
#include "Board.h"

void Piece::setPiece(char type, bool player, int pos) {
	if (pos == -1) return;

	setPlayer(player);
	setType(type);
	setPosition(pos);
	setMoved(false);
}

void Piece::setPosition(int pos) {
	m_position = pos;
	m_moved = true;
	move();
}

const std::vector<int>& Piece::getPossibleMoves()
{
	switch (m_type)
	{
	case 'K':
		PossibleKingMoves();
		break;
	case 'Q':
		PossibleQueenMoves();
		break;
	case 'P':
		PossiblePawnMoves();
		break;
	default:
		std::cerr << "Error: piece type does not exist.\n";
		break;
	}
	return possibleMoves;
}

void Piece::move() { //Aligns the piece texture in it's according place
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

void Piece::PossibleKingMoves() {
	possibleMoves.clear();
	int AheadOrBellow = m_player ? - 30 : 30;
	int LeftorRight = m_player ? - 2 : 2;

	if (m_position + AheadOrBellow >= 0 && m_position + AheadOrBellow < 225) possibleMoves.push_back(m_position + AheadOrBellow);
	if (m_position - AheadOrBellow >= 0 && m_position - AheadOrBellow < 225) possibleMoves.push_back(m_position - AheadOrBellow);

	if (m_position % 30 != 16) { // Not left edge for white or black
		if (m_player) {
			if (m_position + LeftorRight >= 0 && m_position + LeftorRight < 225) possibleMoves.push_back(m_position + LeftorRight);
		}
		else if (m_position - LeftorRight >= 0 && m_position - LeftorRight < 225) possibleMoves.push_back(m_position - LeftorRight);
	}
	if (m_position % 30 != 28) { // Not right edge for white or black
		if (m_player) {
			if (m_position - LeftorRight >= 0 && m_position - LeftorRight < 225) possibleMoves.push_back(m_position - LeftorRight);
		}
		else if (m_position + LeftorRight >= 0 && m_position + LeftorRight < 225) possibleMoves.push_back(m_position + LeftorRight);
	}
}

void Piece::PossibleQueenMoves() {
	possibleMoves.clear();

	int forwardRight = m_player ? m_position - 14 : m_position + 14;
	int forwardLeft = m_player ? m_position - 16 : m_position + 16;
	int BackwardLeft = m_player ? m_position + 14 : m_position - 14;
	int BackwardRight = m_player ? m_position + 16 : m_position - 16;

	int AheadOrBellow = m_player ?  - 30 : 30;
	int LeftorRight = m_player ? - 2 : 2;

	if (m_position % 30 != 15) { // Not left edge for white or black
		if (m_player) {
			if (forwardLeft >= 0 && forwardLeft < 225) possibleMoves.push_back(forwardLeft);
			if (BackwardLeft >= 0 && BackwardLeft < 225) possibleMoves.push_back(BackwardLeft);
		} 
		else {
			if (forwardRight >= 0 && forwardRight < 225) possibleMoves.push_back(forwardRight);
			if (BackwardRight >= 0 && BackwardRight < 225) possibleMoves.push_back(BackwardRight);
		}
	}
	if (m_position % 30 != 29) { // Not left edge for white or black
		if (m_player) {
			if (forwardRight >= 0 && forwardRight < 225) possibleMoves.push_back(forwardRight);
			if (BackwardRight >= 0 && BackwardRight < 225) possibleMoves.push_back(BackwardRight);
		}
		else {
			if (forwardLeft >= 0 && forwardLeft < 225) possibleMoves.push_back(forwardLeft);
			if (BackwardLeft >= 0 && BackwardLeft < 225) possibleMoves.push_back(BackwardLeft);
		}
	}

	while (m_position + AheadOrBellow >= 0 && m_position + AheadOrBellow < 225) { //Responsible for continuous foward movement for black and white
		possibleMoves.push_back(m_position + AheadOrBellow);
		m_player ? AheadOrBellow -= 30 : AheadOrBellow += 30;
	}
	AheadOrBellow = m_player ? -30 : 30; //resetting the forward movement counter
	while (m_position - AheadOrBellow >= 0 && m_position - AheadOrBellow < 225) { //Responsible for continuous backward movement for black and white
		possibleMoves.push_back(m_position - AheadOrBellow);
		m_player ? AheadOrBellow -= 30 : AheadOrBellow += 30;
	}
	while ((m_position % 30 > 14 && m_position % 30 + LeftorRight >= 15 && m_position % 30 + LeftorRight <= 29) || //Responsible for continuous left movement for black and white
			(m_position % 30 <= 14  && m_position % 30 + LeftorRight >= 0 && m_position % 30 + LeftorRight <= 14)) {
		possibleMoves.push_back(m_position + LeftorRight);
		m_player ? LeftorRight -= 2 : LeftorRight += 2;
	}
	LeftorRight = m_player ? - 2 : 2; //resetting the side movement (left/right) counter 
	while ((m_position % 30 > 14 && m_position % 30 - LeftorRight >= 15 && m_position % 30 - LeftorRight <= 29) || //Responsible for continuous right movement for black and white
			(m_position % 30 <= 14 && m_position % 30 - LeftorRight >= 0 && m_position % 30 - LeftorRight <= 14)) {
		possibleMoves.push_back(m_position - LeftorRight);
		m_player ? LeftorRight -= 2 : LeftorRight += 2;
	}
}

void Piece::PossiblePawnMoves() {
	possibleMoves.clear();

	int forwardRight = m_player ? m_position - 14 : m_position + 14;
	int forwardLeft = m_player ? m_position - 16 : m_position + 16;
	int forwardAhead = m_player ? - 30 : 30;

	if (m_position % 30 != 15) { // Not left edge for white or black
		if (m_player) {
			if (forwardLeft >= 0 && forwardLeft < 225) possibleMoves.push_back(forwardLeft);
		}
		else if (forwardRight >= 0 && forwardRight < 225) possibleMoves.push_back(forwardRight);
	}
	if (m_position % 30 != 29) { // Not right edge for white or black
		if (m_player) {
			if (forwardRight >= 0 && forwardRight < 225) possibleMoves.push_back(forwardRight);
		}
		else if (forwardLeft >= 0 && forwardLeft < 225) possibleMoves.push_back(forwardLeft);
	}
	// Long forward move (30), always an option
	if (m_position + forwardAhead >= 0 && m_position + forwardAhead < 225) possibleMoves.push_back(m_position + forwardAhead);
	//Pawn special move
	if(!m_moved && m_position % 30 < 15) possibleMoves.push_back(m_position + 2*forwardAhead);
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
	else {
		std::cerr << "Error: failed to load texture.\n";
	}
}
