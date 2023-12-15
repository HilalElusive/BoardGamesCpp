#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <SFML/Graphics.hpp>
#include "../Models/BoardModel.h"

class BoardView {
public:
	BoardView(const BoardModel& model);
	void load(sf::Color col1, sf::Color col2);
	void draw(sf::RenderWindow& window) const;

private:
	const BoardModel& model;
	std::array<sf::RectangleShape, 225> m_boardSquares;

};

#endif