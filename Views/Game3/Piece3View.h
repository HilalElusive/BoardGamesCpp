#ifndef PIECE3VIEW_H
#define PIECE3VIEW_H

#include "../../Models/Game3/Board3Model.h"
#include "../../Models/Game3/Piece3Model.h"
#include "../../PieceTextures.h"

class Piece3View {
public:
	Piece3View(const Piece3Model& pieceModel, const Board3Model& Board3Model);
	void draw(sf::RenderWindow &window);

private:
	const Piece3Model& pieceModel;
	const Board3Model& boardModel;

	char lastKnownType; // To update texture in case of promotion
	int lastKnownPosition;

	sf::Sprite m_sprite;

	void alignTexture(); // Aligning the sprite to Board
	void setTexture();
	bool needsTextureUpdate();
};

#endif