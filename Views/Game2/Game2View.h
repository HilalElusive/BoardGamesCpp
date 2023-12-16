#ifndef GAME2VIEW_H
#define GAME2VIEW_H

#include "../../Models/Game2/Game2Model.h"
#include "Board2View.h"
#include "Piece2View.h"

class Game2View {
public:
	Game2View(const Game2Model& model);
	void draw(sf::RenderWindow &window);

private:
	const Game2Model& model;
	Board2View boardView;
	std::vector<Piece2View> pieceViews;

};

#endif