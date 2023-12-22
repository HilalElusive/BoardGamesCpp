#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "GameState.h"

class GameStateManager {
public:
	GameStateManager(sf::RenderWindow &window);
	~GameStateManager();

	void changeState(GameState* newState);
	void update(sf::RenderWindow &window, sf::Event &event);
	void render(sf::RenderWindow &window);

private:
	GameState* currentState;
	sf::RenderWindow &window;
};

#endif