#include "GameStateManager.h"
#include "MenuState.h"
#include <iostream>

GameStateManager::GameStateManager(sf::RenderWindow &window) : window(window), currentState(nullptr) {
	// Initialize the MenuState as the first state
	currentState = new MenuState(this, window.getSize().x, window.getSize().y);
}

GameStateManager::~GameStateManager() {
	if (currentState) {
		delete currentState;
	}
}

void GameStateManager::changeState(GameState* newState) {
	if (currentState != nullptr)
		delete currentState;

	currentState = newState;

	if (currentState != nullptr)
		window.setTitle(currentState->getStateName()); // Update window title
}

void GameStateManager::update(sf::RenderWindow &window, sf::Event &event) {
	if (currentState != nullptr) {
		currentState->update(window, event);
	}
}

void GameStateManager::render(sf::RenderWindow &window) {
	if (currentState != nullptr) {
		currentState->render(window);
	}
}