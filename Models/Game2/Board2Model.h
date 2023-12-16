#ifndef BOARD2MODEL_H
#define BOARD2MODEL_H

#include <SFML/Graphics.hpp>
#include <array>

class Board2Model {
public:
	Board2Model();
	int getClickedSquareIndex(const sf::Event::MouseButtonEvent& clickPosition) const;
	const sf::Vector2f getSquareSize() const;
	const std::array<sf::Vector2f, 100>& getSquarePositions() const;

private:
	sf::Vector2f squareSize;
	std::array<sf::Vector2f, 100> squarePositions;

};

#endif