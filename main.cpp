#include <SFML/Window.hpp>
#include "./Controllers/GameStateManager.h"
#include "./Controllers/MenuState.h"
#include <iostream>

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 584), "SFML Games", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(20);

	GameStateManager stateManager;
	MenuState* menuState = new MenuState(&stateManager, window.getSize().x, window.getSize().y);
	stateManager.changeState(menuState);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else
				stateManager.update(window, event);
		}

		window.clear();
		stateManager.render(window);
		window.display();
	}

	return 0;
}

/*int main() {

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
}*/