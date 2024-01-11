#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <SFML/Graphics.hpp>
#include "../Models/Game3/Board3Model.h"

class BoardView {
public:
	BoardView(const Board3Model& model);
	void load(sf::Color col1, sf::Color col2);
	void draw(sf::RenderWindow& window) const;

private:
	const Board3Model& model;
	std::array<sf::RectangleShape, 225> m_boardSquares;

};

#endif