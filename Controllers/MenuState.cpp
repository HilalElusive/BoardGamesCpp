#include "MenuState.h"
#include "Game3State.h"
#include <iostream>

MenuState::MenuState(GameStateManager* manager, float width, float height)
	: menuView(width, height), stateManager(manager) {}

MenuState::~MenuState() {}

void MenuState::update(sf::RenderWindow &window, sf::Event &event) {
	// Handle user input to navigate the menu
	// Example: Move up and down in the menu
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Up) {
			menuView.MoveUp();
		}
		else if (event.key.code == sf::Keyboard::Down) {
			menuView.MoveDown();
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			// Example: Change state based on selected item
			int selectedItem = menuView.GetPressedItem();
			switch (selectedItem) {
			case 2:  // Selection for Game 3
				stateManager->changeState(new Game3State(stateManager));
				break;
				// Add cases for other menu items if necessary
			}
		}
	}
}

void MenuState::render(sf::RenderWindow &window) {
	menuView.draw(window);
}