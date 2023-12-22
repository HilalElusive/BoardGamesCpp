#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

class GameState {
public:
	virtual ~GameState() {}
	virtual void update(sf::RenderWindow &window, sf::Event &event) = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual std::string getStateName() const = 0;
};

#endif