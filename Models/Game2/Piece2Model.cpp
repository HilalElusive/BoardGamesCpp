#include "Piece2Model.h"
#include <iostream>

Piece2Model::Piece2Model() {}

Piece2Model::~Piece2Model() {}

void Piece2Model::setPiece(char type, bool player, int pos) {
	if (pos == -1) return;

	setPlayer(player);
	setPosition(pos);
	setType(type);
}

void Piece2Model::setPosition(int pos) {
	m_position = pos;
}

void Piece2Model::setType(char ty) {
	m_type = ty;
}

void Piece2Model::setPlayer(bool bl) {
	m_player = bl;
}

char Piece2Model::getType() const {
	return m_type;
}

bool Piece2Model::getPlayer() const {
	return m_player;
}

int Piece2Model::getPosition() const {
	return m_position;
}

std::vector<int>& Piece2Model::getPossibleMoves() {
	switch (m_type) {
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

void Piece2Model::PossibleQueenMoves() {
	possibleMoves.clear();
	// Directions: up-right, up-left, down-right, down-left
	int directions[] = { -9, -11, 11, 9 };

	// Check each direction
	for (int dir : directions) {
		int currentPos = m_position;
		// Move in the current direction until the edge of the board is reached
		while (true) {
			int nextPos = currentPos + dir;
			// Check if the next position is still on the board
			if (nextPos < 0 || nextPos >= 100) break;
			// Check for edge wrapping
			int currentColumn = currentPos % 10;
			int nextColumn = nextPos % 10;
			if (abs(currentColumn - nextColumn) > 1) break; // Prevent wrapping
			// Update position and add the move to the list of possible moves
			currentPos = nextPos;
			possibleMoves.push_back(currentPos);
		}
	}
}

void Piece2Model::PossiblePawnMoves() {
	possibleMoves.clear();

	int forwardRight = m_player ? m_position - 9 : m_position + 9;
	int forwardLeft = m_player ? m_position - 11 : m_position + 11;

	if (m_position % 10 != 0) { // Not left edge for white or black
		if (m_player) {
			if (forwardLeft >= 0 && forwardLeft < 100) possibleMoves.push_back(forwardLeft);
		}
		else if (forwardRight >= 0 && forwardRight < 100) possibleMoves.push_back(forwardRight);
	}
	if (m_position % 10 != 9) { // Not right edge for white or black
		if (m_player) {
			if (forwardRight >= 0 && forwardRight < 100) possibleMoves.push_back(forwardRight);
		}
		else if (forwardLeft >= 0 && forwardLeft < 100) possibleMoves.push_back(forwardLeft);
	}
}