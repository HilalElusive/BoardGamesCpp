#ifndef GAME2STATE_H
#define GAME2STATE_H

#include "GameState.h"
#include "GameStateManager.h"
#include "../Views/Game2/Game2View.h"

class Game2State : public GameState {
private:
	Game2Model model;
	Game2View view;
	GameStateManager* stateManager; // For state transitions

public:
	Game2State(GameStateManager* manager);
	~Game2State() override;
	void update(sf::RenderWindow &window, sf::Event &event) override;
	void render(sf::RenderWindow &window) override;
};

#endif