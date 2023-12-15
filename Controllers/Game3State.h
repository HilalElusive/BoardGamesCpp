#ifndef GAME3STATE_H
#define GAME3STATE_H

#include "GameState.h"
#include "GameStateManager.h"

#include "../Models/Game3/Game3Model.h"
#include "../Views/Game3View/Game3View.h"

class Game3State : public GameState {
private:
	Game3Model model;
	Game3View view;
	GameStateManager* stateManager; // For state transitions

public:
	Game3State(GameStateManager* manager);
	~Game3State() override;
	void update(sf::RenderWindow &window, sf::Event &event) override;
	void render(sf::RenderWindow &window) override;
};

#endif