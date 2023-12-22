#include "Game2State.h"
#include "MenuState.h"
#include <iostream>

Game2State::Game2State(GameStateManager* manager) : model(), view(model), stateManager(manager) {}

Game2State::~Game2State() {
	PieceTextures::cleanup();
}

// Update the game state
void Game2State::update(sf::RenderWindow &window, sf::Event &event) {
	// Initialize turn if not already done
	if (!model.isTurnInitialized()) {
		std::cout << "----------Game 2 ------------Another turn----------" << std::endl;
		model.findCapturingScenarios();
		model.setTurnInit(true);
	}
	// Process user input and update the model
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			int selectedPositionIndex = model.getBoardModel().getClickedSquareIndex(event.mouseButton);
			if (!model.isSelected())
				model.selectPiece(selectedPositionIndex);
			else
				model.moveSelected(selectedPositionIndex);
		}
	}

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

std::string Game2State::getStateName() const { return "Les Dames"; }