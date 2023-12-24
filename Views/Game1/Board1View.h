#ifndef BOARD1VIEW_H
#define BOARD1VIEW_H

#include "../../Models/Game1/Board1Model.h"

class Board1View {
public:
	Board1View(const Board1Model& model);
	void load(sf::Color col);
	void draw(sf::RenderWindow& window) const;

private:
	const Board1Model& model;
	std::array<sf::RectangleShape, 64> m_boardSquares;
};

#endif