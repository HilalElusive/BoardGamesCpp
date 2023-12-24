#ifndef BOARD2VIEW_H
#define BOARD2VIEW_H

#include "../../Models/Game2/Board2Model.h"

class Board2View {
public:
	Board2View(const Board2Model& model);
	void load(sf::Color col1, sf::Color col2);
	void draw(sf::RenderWindow& window) const;

private:
	const Board2Model& model;
	std::array<sf::RectangleShape, 100> m_boardSquares;
};

#endif