#include "Game2State.h"
#include "MenuState.h"

Game2State::Game2State(GameStateManager* manager) : model(), view(model), stateManager(manager) {}

Game2State::~Game2State() {
	PieceTextures::cleanup();
}

// Update the game state
void Game2State::update(sf::RenderWindow &window, sf::Event &event) {
	
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Escape) {
			stateManager->changeState(new MenuState(stateManager, window.getSize().x, window.getSize().y));
		}
	}
}

// Render the game state
void Game2State::render(sf::RenderWindow &window) {
	view.draw(window);
}