#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include <SFML/Graphics.hpp>

class MenuView {
public:
	MenuView(float width, float height);
	~MenuView();

	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	void draw(sf::RenderWindow &window);

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[3];
};

#endif