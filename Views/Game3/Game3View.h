#ifndef GAME3VIEW_H
#define GAME3VIEW_H

#include "../../Models/Game3/Game3Model.h"
#include "./Piece3View.h"
#include "../BoardView.h" 

class Game3View {
public:
	Game3View(const Game3Model& model);
	void draw(sf::RenderWindow &window);

private:
	const Game3Model& model;
	BoardView boardView;
	std::vector<Piece3View> pieceViews;

	void createMovesSquares(std::vector<sf::RectangleShape>& squares);
};

#endif