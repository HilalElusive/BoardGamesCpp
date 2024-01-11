#ifndef BOARD3MODEL_H
#define BOARD3MODEL_H

#include <array>
#include <SFML/Graphics.hpp>

class Board3Model {
public:
	Board3Model();
	int getClickedSquareIndex(const sf::Event::MouseButtonEvent& clickPosition) const;
	sf::Vector2f determineSquareSize(int position) const;

	const std::array<sf::Vector2f, 225>& getSquareSizes() const;
	const std::array<sf::Vector2f, 225>& getSquarePositions() const;

private:
	std::array<sf::Vector2f, 225> squareSizes;
	std::array<sf::Vector2f, 225> squarePositions;

};

#endif