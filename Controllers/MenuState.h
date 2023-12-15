#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "../Views/MenuView/MenuView.h"
#include "GameStateManager.h"

class MenuState : public GameState {
public:
	MenuState(GameStateManager* manager, float width, float height);
	~MenuState() override;

	void update(sf::RenderWindow &window, sf::Event &event) override;
	void render(sf::RenderWindow &window) override;

private:
	MenuView menuView;
	GameStateManager* stateManager; // For state transitions
};

#endif // MENUSTATE_H