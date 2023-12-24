#ifndef BOARD1MODEL_H
#define BOARD1MODEL_H

#include <SFML/Graphics.hpp>
#include <array>

class Board1Model {
public:
	Board1Model();
	int getClickedSquareIndex(const sf::Event::MouseButtonEvent& clickPosition) const;
	const sf::Vector2f getSquareSize() const;
	const std::array<sf::Vector2f, 64>& getSquarePositions() const;

private:
	sf::Vector2f squareSize;
	std::array<sf::Vector2f, 64> squarePositions;

};

#endif