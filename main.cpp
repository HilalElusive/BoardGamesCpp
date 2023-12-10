#include <SFML/Window.hpp>
#include "Game.h"
#include <iostream>

int main() {

	Game game;

	sf::RenderWindow window(sf::VideoMode(580, 584), "Projet C++", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);

	while (window.isOpen()) {
		sf::Event event;

		// Initialize turn if not already done
		if (!game.turnInitialized) {
			std::cout << "----------another turn----------" << std::endl;
			game.findCapturingScenarios();
			game.turnInitialized = true;
		}

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					
					int SelectedPositionIndex = game.getBoard().getClickedSquareIndex(event.mouseButton);
					if (!game.isSelected())
						game.selectPiece(SelectedPositionIndex);
					else
						game.moveSelected(SelectedPositionIndex);
				}
			}
		}
		
		window.draw(game);
		window.display();
	}
	return 0;
}