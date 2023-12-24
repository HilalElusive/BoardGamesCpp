#ifndef GAME1VIEW_H
#define GAME1VIEW_H

#include "../../Models/Game1/Game1Model.h"
#include "Board1View.h"
#include "Piece1View.h"

class Game1View {
public:
	Game1View(const Game1Model& model);
	void draw(sf::RenderWindow &window);

private:
	const Game1Model& model;
	Board1View boardView;
	std::vector<Piece1View> pieceViews;

	void createMovesSquares(std::vector<sf::RectangleShape>& squares);
};

#endif