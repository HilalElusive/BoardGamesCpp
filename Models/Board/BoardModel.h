#ifndef BOARD_MODEL_H
#define BOARD_MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>

class BoardModel {
public:
	virtual ~BoardModel() = default;
	virtual int getClickedSquareIndex(const sf::Event::MouseButtonEvent& clickPosition) const;
	virtual const std::vector<sf::Vector2f>& getSquarePositions() const;
	virtual const std::vector<sf::Vector2f>& getSquareSizes() const;

protected:
	std::vector<sf::Vector2f> squarePositions;
	std::vector<sf::Vector2f> squareSizes;
	virtual void initializeSquares(int boardSize, const sf::Vector2f& uniformSize);
};

#endif