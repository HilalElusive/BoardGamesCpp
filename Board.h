#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <array>

class Board : public sf::Drawable
{
public:
	Board();
	void load(sf::Color col1, sf::Color col2);
	
	int getClickedSquareIndex(const sf::Event::MouseButtonEvent& clickPosition);

	static std::array<sf::Vector2f, 225> squareSizes;
	static std::array<sf::Vector2f, 225> squarePositions;

private:
	std::array<sf::RectangleShape, 225> m_boardSquares;
	sf::Vector2f determineSquareSize(int position);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif