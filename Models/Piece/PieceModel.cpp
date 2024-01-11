#include "PieceModel.h"
#include <iostream>

PieceModel::PieceModel() {}

PieceModel::~PieceModel() {}

void PieceModel::setPosition(int pos) {
	m_position = pos;
	m_moved = true;
}

void PieceModel::setMoved(bool moved) {
	m_moved = moved;
}

int PieceModel::getPosition() const {
	return m_position;
}

bool PieceModel::hasMoved() const {
	return m_moved;
}
