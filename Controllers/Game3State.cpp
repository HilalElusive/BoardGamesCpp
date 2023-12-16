#include "Game3State.h"
#include "MenuState.h"
#include <iostream>

Game3State::Game3State(GameStateManager* manager) : model(), view(model), stateManager(manager) {}

Game3State::~Game3State() {
	PieceTextures::cleanup();
}

// Update the game state
void Game3State::update(sf::RenderWindow &window, sf::Event &event) {
	// Initialize turn if not already done
	if (!model.turnInitialized) {
		std::cout << "----------another turn----------" << std::endl;
		model.findCapturingScenarios();
		model.turnInitialized = true;
	}
	// Process user input and update the model
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			int selectedPositionIndex = model.getBoardModel().getClickedSquareIndex(event.mouseButton);
			if (!model.isSelected())
				model.selectPiece(selectedPositionIndex);
			else {
				model.moveSelected(selectedPositionIndex);
			}
		}
	}
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Escape) {
			stateManager->changeState(new MenuState(stateManager, window.getSize().x, window.getSize().y));
		}
	}
}

// Render the game state
void Game3State::render(sf::RenderWindow &window) {
	// Draw the game using the view
	view.draw(window);
}