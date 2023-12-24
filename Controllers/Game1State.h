#ifndef GAME1STATE_H
#define GAME1STATE_H

#include "GameState.h"
#include "GameStateManager.h"
#include "../Views/Game1/Game1View.h"

class Game1State : public GameState {
private:
	Game1Model model;
	Game1View view;
	GameStateManager* stateManager; // For state transitions

public:
	Game1State(GameStateManager* manager);
	~Game1State() override;
	void update(sf::RenderWindow &window, sf::Event &event) override;
	void render(sf::RenderWindow &window) override;
	std::string getStateName() const override;
};

#endif