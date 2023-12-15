#ifndef GAME3VIEW_H
#define GAME3VIEW_H

#include <SFML/Graphics.hpp>
#include "../../Models/Game3/Game3Model.h" // Including the Game3Model for accessing game data
#include "../BoardView.h" 

class Game3View {
public:
	Game3View(const Game3Model& model);
	void draw(sf::RenderWindow &window);

private:
	const Game3Model& model;
	BoardView boardView;
	void createMovesSquares(std::vector<sf::RectangleShape>& squares);
};

#endif