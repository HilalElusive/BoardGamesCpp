#include "Game1View.h"
#include <iostream>

Game1View::Game1View(const Game1Model & model) : model(model), boardView(model.getBoardModel()) {
	if (!font.loadFromFile("Fonts/arial.ttf"))
		std::cout << "Error loading font\n";
	// Initialize pieceViews
	for (const Piece1Model& piece : model.allPieces()) {
		pieceViews.emplace_back(piece, model.getBoardModel());
	}

	float horizontalPosition = 720; // Some padding from the board
	float totalHeight = 484; // Total height of the window - box height
	size_t numPlayers = model.getPlayers().size();

	// Height used by text (assuming 24px per line and a small gap between name and score)
	float textHeightPerPlayer = 24 * 2 + 10; // 24px * 2 lines + 10px gap
	float totalTextHeight = textHeightPerPlayer * numPlayers;
	float totalSpacing = totalHeight - totalTextHeight; // Remaining space for spacing
	float spaceBetweenGroups = totalSpacing / (numPlayers + 1); // Space between groups

	for (size_t i = 0; i < numPlayers; ++i) {
		float verticalPosition = spaceBetweenGroups + (textHeightPerPlayer + spaceBetweenGroups) * i;

		sf::Text nameText;
		nameText.setFont(font);
		nameText.setCharacterSize(24);
		nameText.setFillColor(sf::Color::White);
		nameText.setPosition(horizontalPosition, verticalPosition);
		playerNames.push_back(nameText);

		sf::Text scoreText;
		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(horizontalPosition, verticalPosition + 30); // Directly below name
		playerScores.push_back(scoreText);
	}
	// Initialize turn indicator box
	turnIndicatorBox.setSize(sf::Vector2f(416, 100));
	turnIndicatorBox.setPosition(584, 484); // Positioned at the bottom
	turnIndicatorBox.setFillColor(sf::Color(50, 50, 50)); 

	// Initialize turn indicator text
	turnIndicatorText.setFont(font);
	turnIndicatorText.setCharacterSize(24);
	turnIndicatorText.setFillColor(sf::Color::White);
}

void Game1View::draw(sf::RenderWindow & window) {
	window.clear(sf::Color(36, 37, 47));
	// Draw the board
	boardView.draw(window);

	// Draw the pieces
	for (Piece1View& pieceView : pieceViews) {
		pieceView.draw(window);
	}

	// Draw possible moves
	if (model.isSelected()) {
		std::vector<sf::RectangleShape> possibleMovesSquares;
		createMovesSquares(possibleMovesSquares);
		for (const sf::RectangleShape& square : possibleMovesSquares) {
			window.draw(square);
		}
	}

	const std::vector<Game1Player>& players = model.getPlayers();
	for (size_t i = 0; i < players.size(); ++i) {
		playerNames[i].setString("Player: " + players[i].getName());
		window.draw(playerNames[i]);

		playerScores[i].setString("Score: " + std::to_string(players[i].getScore()));
		window.draw(playerScores[i]);
	}
	// Update and draw turn indicator
	turnIndicatorText.setString(model.getCurrentPlayer().getName() + "'s Turn");
	// Recalculate position to center the text
	turnIndicatorText.setPosition(584 + (416 - turnIndicatorText.getLocalBounds().width) / 2, 520);

	window.draw(turnIndicatorBox);
	window.draw(turnIndicatorText);
}

void Game1View::createMovesSquares(std::vector<sf::RectangleShape>& squares) {
	for (int i : model.getValidMoves()) {
		sf::RectangleShape tmp;
		tmp.setPosition(model.getBoardModel().getSquarePositions()[i]);
		tmp.setSize(model.getBoardModel().getSquareSizes()[i]);
		tmp.setFillColor(sf::Color(0x66b4cc50));
		squares.push_back(tmp);
	}
}
