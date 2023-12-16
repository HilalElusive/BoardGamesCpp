#include "MenuView.h"
#include <iostream>

MenuView::MenuView(float width, float height) {
	if (!font.loadFromFile("Fonts/arial.ttf")) {
		std::cout << "Error loading font\n";
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Butin");
	menu[0].setPosition(sf::Vector2f(width / 2 - 50, height / (3 + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Les Dames");
	menu[1].setPosition(sf::Vector2f(width / 2 - 50, height / (3 + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("BullTricker");
	menu[2].setPosition(sf::Vector2f(width / 2 - 50, height / (3 + 1) * 3));

	selectedItemIndex = 0;
}

MenuView::~MenuView() {}

int MenuView::GetPressedItem() {
	return selectedItemIndex;
}

void MenuView::draw(sf::RenderWindow &window) {
	for (int i = 0; i < 3; i++) {
		window.draw(menu[i]);
	}
}

void MenuView::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void MenuView::MoveDown() {
	if (selectedItemIndex + 1 < 3) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}