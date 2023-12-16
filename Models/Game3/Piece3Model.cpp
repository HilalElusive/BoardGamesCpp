#include "Piece3Model.h"
#include "../Strategy/KingMovementStrategy.h"
#include "../Strategy/QueenMovementStrategy.h"
#include "../Strategy/PawnMovementStrategy.h"
#include <iostream>

Piece3Model::Piece3Model() : movementStrategy(nullptr) {}

Piece3Model::~Piece3Model() {
	delete movementStrategy;
}

void Piece3Model::setPiece(char type, bool player, int pos) {
	if (pos == -1) return;

	setPlayer(player);
	setPosition(pos);
	setMoved(false);
	setType(type);
}

void Piece3Model::setPosition(int pos) {
	m_position = pos;
	m_moved = true;
}

void Piece3Model::setType(char ty) {
	m_type = ty;

	switch (m_type) {
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

void Piece3Model::setStrategy(MovementStrategy* strategy) {
	delete movementStrategy;
	movementStrategy = strategy;
}

std::vector<int>& Piece3Model::getPossibleMoves() {
	movementStrategy->generatePossibleMoves(*this, possibleMoves);
	return possibleMoves;
}

void Piece3Model::setPlayer(bool bl) {
	m_player = bl;
}

bool Piece3Model::getPlayer() const {
	return m_player;
}

void Piece3Model::setMoved(bool moved) {
	m_moved = moved;
}

bool Piece3Model::hasMoved() const {
	return m_moved;
}

char Piece3Model::getType() const {
	return m_type;
}

int Piece3Model::getPosition() const {
	return m_position;
}