#ifndef PIECE3VIEW_H
#define PIECE3VIEW_H

#include <SFML/Graphics.hpp>
#include "../../Models/BoardModel.h"
#include "../../Models/Game3/Piece3Model.h"
#include "../../PieceTextures.h"

class Piece3View {
public:
	Piece3View(const Piece3Model& pieceModel, const BoardModel& boardModel);
	void draw(sf::RenderWindow &window);

private:
	const Piece3Model& model;
	const BoardModel& boardModel;

	char lastKnownType; // To update texture in case of promotion
	int lastKnownPosition;

	sf::Sprite m_sprite;

	void alignTexture(); // Aligning the sprite to Board
	void setTexture();
	bool needsTextureUpdate();
};

#endif