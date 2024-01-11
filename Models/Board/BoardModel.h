#ifndef BOARD_MODEL_H
#define BOARD_MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>

class BoardModel {
public:
	virtual ~BoardModel() = default;
	virtual int getClickedSquareIndex(const sf::Event::MouseButtonEvent& clickPosition) const = 0;
	virtual const std::vector<sf::Vector2f>& getSquarePositions() const = 0;
protected:
	std::vector<sf::Vector2f> squarePositions;
};

#endif