#ifndef PIECE_VIEW_H
#define PIECE_VIEW_H

#include <SFML/Graphics.hpp>

class PieceModel; // Forward declaration

class PieceView {
protected:
	const PieceModel& pieceModel;

	sf::Sprite m_sprite;
	int lastKnownPosition;

	virtual void setTexture() = 0;

public:
	PieceView(const PieceModel& model, sf::RenderWindow& window);
	virtual ~PieceView() {}

	virtual void draw() = 0;
};

#endif