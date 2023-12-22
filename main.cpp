#include <SFML/Window.hpp>
#include "./Controllers/GameStateManager.h"
#include "./Controllers/MenuState.h"
#include <iostream>

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 584), "SFML Games", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(20);

	GameStateManager stateManager(window);

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