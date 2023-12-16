#ifndef PIECE2VIEW_H
#define PIECE2VIEW_H

#include "../../Models/Game2/Piece2Model.h"
#include "../../Models/Game2/Board2Model.h"
#include "../../PieceTextures.h"

class Piece2View {
public:
	Piece2View(const Piece2Model& pieceModel, const Board2Model& boardModel);
	void draw(sf::RenderWindow &window);

private:
	const Piece2Model& pieceModel;
	const Board2Model& boardModel;

	char lastKnownType; // To update texture in case of promotion
	int lastKnownPosition;

	sf::Sprite m_sprite;

	void alignTexture(); // Aligning the sprite to Board
	void setTexture();
	bool needsTextureUpdate();
};

#endif