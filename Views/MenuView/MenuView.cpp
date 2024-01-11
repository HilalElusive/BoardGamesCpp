#include "MenuView.h"
#include <iostream>

MenuView::MenuView(float width, float height) {
	if (!font.loadFromFile("Fonts/arial.ttf")) {
		std::cout << "Error loading font\n";
	}

	for (int i = 0; i < 3; ++i) {
		menu[i].setFont(font);
		menu[i].setCharacterSize(45);
		menu[i].setFillColor(i == 0 ? sf::Color(72, 202, 228) : sf::Color(200, 200, 200));
		menu[i].setString(i == 0 ? "Butin" : (i == 1 ? "Les Dames" : "BullTricker"));

		// Get the bounding box of the text
		sf::FloatRect textRect = menu[i].getGlobalBounds();

		// Set the origin of the text to its center
		menu[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

		// Set the position of the text
		menu[i].setPosition(sf::Vector2f(width / 2.0f, height / (3 + 1) * (i + 1)));
	}

	selectedItemIndex = 0;
}

MenuView::~MenuView() {}

int MenuView::GetPressedItem() {
	return selectedItemIndex;
}

void MenuView::draw(sf::RenderWindow &window) {
	window.clear(sf::Color(36, 37, 47));
	for (int i = 0; i < 3; i++) {
		window.draw(menu[i]);
	}
}

void MenuView::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color(200, 200, 200));
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color(72, 202, 228));
	}
}

void MenuView::MoveDown() {
	if (selectedItemIndex + 1 < 3) {
		menu[selectedItemIndex].setFillColor(sf::Color(200, 200, 200));
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color(72, 202, 228));
	}
}