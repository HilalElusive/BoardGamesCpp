#include "Piece2Model.h"
#include "../Strategy/Game2/Game2PawnMovementStrategy.h"
#include "../Strategy/Game2/Game2QueenMovementStrategy.h"
#include <iostream>

Piece2Model::Piece2Model() : movementStrategy(nullptr) {}

Piece2Model::~Piece2Model() {
	delete movementStrategy;
}

void Piece2Model::setPiece(char type, bool player, int pos) {
	if (pos == -1) return;

	setPlayer(player);
	setPosition(pos);
	setType(type);
}

void Piece2Model::setType(char ty) {
	m_type = ty;
	switch (m_type) {
	case 'Q':
		setStrategy(new Game2QueenMovementStrategy());
		break;
	case 'P':
		setStrategy(new Game2PawnMovementStrategy());
		break;
	default:
		std::cerr << "Error: piece type does not exist.\n";
		break;
	}
}

void Piece2Model::setPlayer(bool bl) {
	m_player = bl;
}

void Piece2Model::setStrategy(MovementStrategy* strategy) {
	delete movementStrategy;
	movementStrategy = strategy;
}

char Piece2Model::getType() const {
	return m_type;
}

bool Piece2Model::getPlayer() const {
	return m_player;
}

std::vector<int>& Piece2Model::getPossibleMoves() {
	movementStrategy->generatePossibleMoves(*this, possibleMoves);
	return possibleMoves;
}