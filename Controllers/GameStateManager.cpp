#include "GameStateManager.h"
#include <iostream>

GameStateManager::GameStateManager() : currentState(nullptr) {}

GameStateManager::~GameStateManager() {
	if (currentState) {
		delete currentState;
	}
}

void GameStateManager::changeState(GameState* newState) {
	if (currentState != nullptr) {
		delete currentState;
	}
	currentState = newState;
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