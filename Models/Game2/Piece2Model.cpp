#include "Piece2Model.h"

Piece2Model::Piece2Model() {}

Piece2Model::~Piece2Model() {
}

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
	// TODO: movement calculation
	return possibleMoves;
}