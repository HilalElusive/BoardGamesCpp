#include "Game1State.h"
#include "MenuState.h"

Game1State::Game1State(GameStateManager * manager) : model(), view(model), stateManager(manager) {}

Game1State::~Game1State() {
}

void Game1State::update(sf::RenderWindow & window, sf::Event & event) {
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

void Game1State::render(sf::RenderWindow & window) {
	view.draw(window);
}

std::string Game1State::getStateName() const { return "Butin"; }