#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "../../Models/Board/BoardModel.h"
#include <SFML/Graphics.hpp>

class BoardView {
public:
	BoardView(const BoardModel& model);
	virtual ~BoardView() = default;

	virtual void load(const std::vector<sf::Color>& colors, float outlineWeight = 0, sf::Color outline = sf::Color(0,0,0));
	virtual void draw(sf::RenderWindow& window) const;

protected:
	const BoardModel& model;
	std::vector<sf::RectangleShape> boardSquares;

};

#endif 