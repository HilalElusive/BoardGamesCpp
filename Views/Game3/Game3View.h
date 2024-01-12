#ifndef GAME3VIEW_H
#define GAME3VIEW_H

#include "../../Models/Game3/Game3Model.h"
#include "./Board3View.h" 
#include "./Piece3View.h"

class Game3View {
public:
	Game3View(const Game3Model& model);
	void draw(sf::RenderWindow &window);

private:
	const Game3Model& model;
	Board3View boardView;
	std::vector<Piece3View> pieceViews;

	void createMovesSquares(std::vector<sf::RectangleShape>& squares);

	std::vector<sf::Text> playerNames;
	std::vector<sf::Text> playerScores;
	sf::RectangleShape turnIndicatorBox;
	sf::Text turnIndicatorText;

	sf::Font font;
};

#endif