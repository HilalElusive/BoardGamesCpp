#include "Piece1Model.h"

Piece1Model::Piece1Model() {}

Piece1Model::~Piece1Model() {}

void Piece1Model::setPiece(char color, int pos) {
	if (pos == -1) return;

	setColor(color);
	setPosition(pos);

	switch (color) {
	case 'J':
		setValue(1);
		break;
	case 'R':
		setValue(2);
		break;
	case 'N':
		setValue(3);
		break;
	default:
		break;
	}
}

void Piece1Model::setPosition(int pos) { m_position = pos; }

void Piece1Model::setColor(char cl) { m_color = cl; }

void Piece1Model::setValue(int vl) { m_value = vl; }

char Piece1Model::getColor() const{ return m_color; }

int Piece1Model::getPosition() const { return m_position; }

int Piece1Model::getValue() const { return m_value; }