#ifndef PIECE1VIEW_H
#define PIECE1VIEW_H

#include "../../Models/Game1/Piece1Model.h"
#include "../../Models/Game1/Board1Model.h"
#include "../../PieceTextures.h"

class Piece1View {
public:
	Piece1View(const Piece1Model& pieceModel, const Board1Model& boardModel);
	void draw(sf::RenderWindow &window);

private:
	const Piece1Model& pieceModel;
	const Board1Model& boardModel;

	int lastKnownPosition;
	sf::CircleShape texture;

	void alignTexture(); // Aligning the shape to Board
	void setPieceColor();
};

#endif